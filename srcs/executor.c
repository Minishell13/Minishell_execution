/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:45:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/29 16:34:49 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_bool	ft_check_access(char *file, int permission)
{
	if (access(file, permission) == -1)
		return (false);
	return (true);
}

char	*ft_parse_path(char **all_path, char *command)
{
	int		i;
	char	*temp;
	char	*path;
	char	*result;

	i = 0;
	result = NULL;
	while (all_path[i] && !result)
	{
		temp = ft_strjoin("/", command);
		if (!temp)
			break ;
		path = ft_strjoin(all_path[i], temp);
		free(temp);
		if (path && ft_check_access(path, X_OK))
			result = path;
		else
			free(path);
		i++;
	}
	ft_free_array(all_path);
	if (!result)
		result = ft_strdup(command);
	return (result);
}

char	*ft_get_path(char *command, char **envp)
{
	int		i;
	char	**all_path;
	char	*path;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	}
	// TODO: Maybe you need to work with the static envp here
	if (!envp[i])
		return (ft_strdup(command));
	all_path = ft_split(envp[i] + 5, ':');
	if (!all_path)
		return (ft_strdup(command));
	path = ft_parse_path(all_path, command);
	return (path);
}

//* --------------------------------SIMPLE_COMMAND --------------------------------
t_error ft_execute_simple_cmd(t_ast *node, char **envp)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = ft_get_path(node->data.args[0], envp);
	if (!path)
		return (EXECVE_ERROR);

	pid = fork();
	if (pid < 0)
		return (FORK_ERROR);
	if (pid == 0)
	{
		execve(path, node->data.args, envp);
		perror("sh");
		free(path);
		if (errno == ENOENT) exit(127);
		if (errno == EACCES) exit(126);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	free(path);
	return (WEXITSTATUS(status) ? EXECVE_ERROR : SUCCESS_ERROR);
}


//* -------------------------------- PIPLINE --------------------------------

t_error	ft_redirect_fds(int fds[2], int fd)
{
	if (fd == STDOUT_FILENO)
	{	
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (DUP2_ERROR);
		close(fds[0]);
		close(fds[1]);
	}
	else if (fd == STDIN_FILENO)
	{	
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (DUP2_ERROR);
		close(fds[0]);
		close(fds[1]);
	}
	return (SUCCESS_ERROR);
}

t_error ft_execute_pipe(t_ast *node, char **envp)
{
	int		fds[2];
	pid_t	lc,	rc;
	int		status;

	if (pipe(fds) < 0)
		return (PIPE_ERROR);

	// Left stage
	lc = fork();
	if (lc < 0)
		return (FORK_ERROR);
	if (lc == 0)
	{
		if (ft_redirect_fds(fds, STDOUT_FILENO) != SUCCESS_ERROR)
			return (DUP2_ERROR);
		ft_executor(node->left, envp);
		exit(EXIT_FAILURE);
	}

	// Right stage
	rc = fork();
	if (rc < 0)
		return (FORK_ERROR);
	if (rc == 0)
	{
		if (ft_redirect_fds(fds, STDIN_FILENO) != SUCCESS_ERROR)
			return (DUP2_ERROR);
		ft_executor(node->right, envp);
		exit(EXIT_FAILURE);
	}

	// Parent
	close(fds[0]);
	close(fds[1]);
	waitpid(lc, &status, 0);
	waitpid(rc, &status, 0);
	return (SUCCESS_ERROR);
}





// TODO: You must use the redir struct for IO redirection logic
//* -------------------------------- IO_REDIRECTION --------------------------------


void	ft_generate_tmpfile(t_redir *redir)
{
	char	*temp;

	temp = ft_itoa(getpid());
	if (!temp)
	{
		redir->file = ft_strdup("/tmp/pipex_heredoc");
		return ;
	}
	redir->file = ft_strjoin("/tmp/pipex_heredoc_", temp);
	free(temp);
}

void	ft_fill_here_doc(t_redir *redir, int fd)
{
	char	*line;
	size_t	line_size;

	while (1)
	{
		ft_printf("here_doc> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_printf("\n");
			break ;
		}
		line_size = ft_strlen(line) - 1;
		if (ft_strncmp(line, redir->limiter,
				ft_strlen(redir->limiter)) == 0
			&& line_size == ft_strlen(redir->limiter))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
}

void	ft_here_doc(t_redir *redir)
{
	int		fd;

	ft_generate_tmpfile(redir);
	fd = open(redir->file, (O_WRONLY | O_CREAT | O_TRUNC), 0777);
	if (fd < 0)
		perror("sh");
	else
		ft_fill_here_doc(redir, fd);
}

int	ft_parse_infile(t_redir *redir)
{
	int	fd;

	if (redir->type == GRAM_HEREDOC)
		ft_here_doc(redir);
	fd = open(redir->file, O_RDONLY);
	if (fd < 0 || ft_check_access(redir->file, (R_OK | F_OK)) == false)
		perror("sh");
	return (fd);
}

int	ft_parse_outfile(t_redir *redir)
{
	int	flags;
	int	fd;

	if (redir->type == GRAM_REDIR_APPEND)
		flags = (O_WRONLY | O_CREAT | O_APPEND);
	else
		flags = (O_WRONLY | O_CREAT | O_TRUNC);
	fd = open(redir->file, flags, 0644);
	if (fd < 0 || ft_check_access(redir->file, W_OK) == false)
		perror("sh");
	return (fd);
}

t_error	ft_execute_redirection(t_ast *node, char **envp)
{
	int		fd;
	t_redir	*r;

	r = &node->data.redir;
	// 1) Handle input redirection: '<' or '<<'
	if (r->type == GRAM_REDIR_IN || r->type == GRAM_HEREDOC)
	{
		// ft_parse_infile will do here-doc if needed, then open for read
		fd = ft_parse_infile(r);
		if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
		{
			perror("sh");
			if (fd >= 0)
				close(fd);
			return (REDIR_ERROR);
		}
		close(fd);
	}
	// 2) Handle output redirection: '>' or '>>'
	else if (r->type == GRAM_REDIR_OUT || r->type == GRAM_REDIR_APPEND)
	{
		fd = ft_parse_outfile(r);
		if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("sh");
			if (fd >= 0)
				close(fd);
			return (REDIR_ERROR);
		}
		close(fd);
	}
	// 3) Now execute the command that’s been wrapped by this redirection
	return (ft_executor(node->left, envp));
}



// TODO: You need first to know the exact struct of AST tree
// TODO: The representation each node with his type and args
// TODO: How to parcoure throw this three and get nodes in the correct order
// TODO: Create functions for execution (per node type)
// TODO: Focus on execution flow, (memory, fds, error) management
// TODO: ...

t_error ft_executor(t_ast *node, char **envp)
{
	if (!node) return 0;

	switch (node->type)
	{
		case GRAM_SIMPLE_COMMAND:
			return ft_execute_simple_cmd(node, envp);

		case GRAM_PIPELINE:
			return ft_execute_pipe(node, envp);

		case GRAM_IO_REDIRECT:
			return ft_execute_redirection(node, envp);

		// case GRAM_SUBSHELL:
		// 	return ft_execute_subshell(node, envp);

		// case GRAM_OPERATOR_AND:
		// case GRAM_OPERATOR_OR:
		// 	return ft_execute_and_or(node, envp);

		default:
			return 0;
	}
	return (SUCCESS_ERROR);
}


// Example: cat file.txt | grep foo > out.txt

// GRAM_COMPLETE_COMMAND
// └── left → GRAM_PIPELINE
//       ├── left → GRAM_SIMPLE_COMMAND
//       │      └ data.argv = ["cat","file.txt",NULL]
//       └── right → GRAM_REDIR_OUT
//                  ├ data.redir.file   = "out.txt"
//                  ├ data.redir.append = false
//                  └ left → GRAM_SIMPLE_COMMAND
//                           └ data.argv = ["grep","foo",NULL]
