/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:26:10 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/30 20:00:53 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putendl_fd(line, STDERR_FILENO);
		if (!line)
		{
			ft_putstr_fd("\nminishell: warning: here-document delimited by \
end-of-file (wanted `Limiter')\n", STDERR_FILENO);
			break ;
		}
		
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
		perror("sh_heredoc");
	else
		fill_here_doc(redir, fd);
}

void	heredoc_first(t_ast *node, int heredoc_total)
{
	t_ast	*c;
	int		heredoc_index;
	int		backup_fd;

	c = node->child;
	heredoc_index = 1;
	while (c)
	{
		if (c->type == GRAM_HEREDOC)
		{
			//! Restore prev heredoc
			if (heredoc_index < heredoc_total)
			{
				backup_fd = dup(STDIN_FILENO);
				expand_and_redir(c);
				dup2(backup_fd, STDIN_FILENO);
				close(backup_fd);
			}
			//! Do not restore last heredoc
			else
				expand_and_redir(c);
			heredoc_index++;
		}
		c = c->sibling;
	}
}
