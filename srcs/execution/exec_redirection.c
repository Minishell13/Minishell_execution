/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:33:12 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/25 13:11:37 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// //* -------------------------------- IO_REDIRECTION --------------------------------
void	generate_tmpfile(t_redir *redir)
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
void	fill_here_doc(t_redir *redir, int fd)
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
		if (redir->expanded)
			expand_herdoc(redir, &line);
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

void	here_doc(t_redir *redir)
{
	int		fd;

	fd = open(redir->file, (O_WRONLY | O_CREAT | O_TRUNC), 0600);
	if (fd < 0)
		perror("sh");
	else
		fill_here_doc(redir, fd);
}

int	parse_infile(t_redir *redir)
{
	int	fd;

	if (redir->type == GRAM_HEREDOC)
		here_doc(redir);
	fd = open(redir->file, O_RDONLY);
	if (fd < 0 || check_access(redir->file, (R_OK | F_OK)) == false)
		perror("sh");
	return (fd);
}

int	parse_outfile(t_redir *redir)
{
	int	flags;
	int	fd;

	if (redir->type == GRAM_REDIR_APPEND)
		flags = (O_WRONLY | O_CREAT | O_APPEND);
	else
		flags = (O_WRONLY | O_CREAT | O_TRUNC);
	fd = open(redir->file, flags, 0644);
	if (fd < 0 || check_access(redir->file, W_OK) == false)
		perror("sh");
	return (fd);
}

t_error	redir(int fd, t_redir *r)
{
	// 1) Handle input redirection: '<' or '<<'
	if (r->type == GRAM_REDIR_IN || r->type == GRAM_HEREDOC)
	{
		fd = parse_infile(r);
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
		fd = parse_outfile(r);
		if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		{
			if (fd >= 0)
				close(fd);
			return (REDIR_ERROR);
		}
		close(fd);
	}	
	return (SUCCESS);
}

t_error	execute_redirection(t_ast *root, t_ast *node, char **envp)
{
	int		fd = -1;
	t_redir	*r;
	t_error ret;
	// int saved_stdin = dup(STDIN_FILENO);

	r = &node->data.redir;
	// 3) Now execute the command that’s been wrapped by this redirection
	if (redir(fd, r) != SUCCESS)
		return (REDIR_ERROR);
		
	ret = executor(root, node->child, envp);

	// Restore original stdin
	// dup2(saved_stdin, STDIN_FILENO);
	// close(saved_stdin);
	
	return (ret);
}
