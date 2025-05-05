/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:18 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/05 14:34:47 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- PIPELINE --------------------------------
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

t_error	ft_execute_pipe(t_ast *root, t_ast *node, char **envp)
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
		ft_executor(root, node->left, envp);
		ft_destroy_ast(root);
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
		ft_executor(root, node->right, envp);
		ft_destroy_ast(root);
		exit(EXIT_FAILURE);
	}

	// Parent
	close(fds[0]);
	close(fds[1]);
	waitpid(lc, &status, 0);
	waitpid(rc, &status, 0);
	return (SUCCESS_ERROR);
}

