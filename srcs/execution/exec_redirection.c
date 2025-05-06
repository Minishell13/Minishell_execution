/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:33:12 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/06 14:08:03 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- IO_REDIRECTION --------------------------------
void	ft_generate_tmpfile(t_redir *redir)
{
	char	*temp;

	temp = ft_itoa(getpid());
	if (!temp)
	{
		redir->file = ft_strdup("/tmp/heredoc");
		return ;
	}
	redir->file = ft_strjoin("/tmp/heredoc_", temp);
	free(temp);
}

// TODO: Chose between readline or get_next_line
void	ft_fill_here_doc(t_redir *redir, int fd)
{
	char	*line;
	size_t	line_size;

	while (1)
	{
		ft_putstr_fd("here_doc> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		line_size = ft_strlen(line) - 1;
		if (ft_strncmp(line, redir->limiter,
				ft_strlen(redir->limiter)) == 0
			&& line_size == ft_strlen(redir->limiter))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	
	// while (1)
	// {
	// 	line = readline("here_doc> ");
	// 	if (!line)
	// 		break ;
	// 	line_size = ft_strlen(line);
	// 	if (ft_strncmp(line, redir->limiter, ft_strlen(redir->limiter)) == 0
	// 		&& line_size == ft_strlen(redir->limiter))
	// 	{
	// 		break ;
	// 	}
	// 	ft_putstr_fd(line, fd);
	// 	ft_putstr_fd("\n", fd);
	// 	free(line);
	// }
	free(line);
	close(fd);
}

void	ft_here_doc(t_redir *redir)
{
	int		fd;

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

int ft_exec_redir(t_ast *root, t_ast *node, t_redir *r, char **envp)
{
	pid_t pid;
	int   status;
	int   fd;

	pid = fork();
	if (pid < 0)
		return (FORK_ERROR);
	if (pid == 0)
	{
		// 1) Handle input redirection: '<' or '<<'
		if (r->type == GRAM_REDIR_IN || r->type == GRAM_HEREDOC)
		{
			fd = ft_parse_infile(r);
			if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
			{
				if (fd >= 0)
					close(fd);
				return (REDIR_ERROR);
			}
			close(fd);
		}
		// 2) Handle output redirection: '>' or '>>'
		else
		{
			fd = ft_parse_outfile(r);
			if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
			{
				if (fd >= 0)
					close(fd);
				return (REDIR_ERROR);
			}
			close(fd);
		}

		// then execute the inner command
		ft_executor(root, node->left, envp);
		ft_destroy_ast(root);
		exit(EXIT_FAILURE);
	}
	// parent waits; its stdin/stdout unchanged
	waitpid(pid, &status, 0);
	return WIFEXITED(status) ? WEXITSTATUS(status) : EXIT_FAILURE;
}

t_error	ft_execute_redirection(t_ast *root, t_ast *node, char **envp)
{
	t_redir	*r;

	r = &node->data.redir;
	// 3) Now execute the command that’s been wrapped by this redirection
	return (ft_exec_redir(root, node, r, envp));
}





