/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:45:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/28 17:45:14 by abnsila          ###   ########.fr       */
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
t_error	ft_execute_simple_cmd(t_ast *node, char **envp)
{
	int		pid;
	char	*path;

	pid = fork();
	if (pid != 0)
		return (FORK_ERROR);
	if (pid == 0)
	{
		if (execve(path, node->data.args, envp))
		{
			perror("sh");
			if (errno == ENOENT)
				exit(127);
			else if (errno == EACCES)
				exit(126);
			exit(EXIT_FAILURE);
		}
	}
	wait(NULL);
	return (SUCCESS_ERROR);
}

//* -------------------------------- PIPLINE --------------------------------
t_error	ft_execute_pipe(t_ast *node, char **envp)
{
	int		fds[2];
	if (pipe(fds) == -1)
	return (PIPE_ERROR);
	
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		return (DUP2_ERROR);
		
	ft_execute_simple_cmd(node->left, envp);
	
	if (dup2(fds[0], STDIN_FILENO) == -1)
		return (DUP2_ERROR);
	
	ft_execute_simple_cmd(node->right, envp);
	return (SUCCESS_ERROR);
}










// TODO: You must use the redir struct for IO redirection logic
//* -------------------------------- IO_REDIRECTION --------------------------------
int	ft_parse_infile(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0 || ft_check_access(infile, (R_OK | F_OK)) == false)
		perror("sh");
	return (fd);
}

t_error	ft_parse_outfile(char *outfile)
{
	int	flags;
	int	fd;

	if (pipex->here_doc)
		flags = (O_WRONLY | O_CREAT | O_APPEND);
	else
		flags = (O_WRONLY | O_CREAT | O_TRUNC);
	fd = open(pipex->outfile, flags, 0644);
	if (fd < 0 || ft_check_access(pipex->outfile, W_OK) == false)
		ft_format_error(pipex, "%s: %s: %s", strerror(errno), pipex->outfile);
	pipex->outfile_fd = fd;
	return (true);
}



t_error	ft_execute_rdirection(t_ast *node)
{
	int	fd;
	
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (DUP2_ERROR);
}

// TODO: You need first to know the exact struct of AST tree
// TODO: The representation each node with his type and args
// TODO: How to parcoure throw this three and get nodes in the correct order
// TODO: Create functions for execution (per node type)
// TODO: Focus on execution flow, (memory, fds, error) management
// TODO: ...

void	ft_executor()
{
	return ;
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
