/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:37 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/06 14:35:58 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- SUBSHELL --------------------------------
t_error	ft_execute_subshell(t_ast *root, t_ast *node, char **envp)
{
	pid_t pid;
	int   status;

	pid = fork();
	if (pid < 0)
		return FORK_ERROR;
	if (pid == 0)
	{
		ft_executor(root, node->left, envp);
		ft_destroy_ast(root);
		exit(EXIT_FAILURE);  // in case executor didn't exit
	}
	waitpid(pid, &status, 0);
	return WEXITSTATUS(status) ? EXECVE_ERROR : SUCCESS;
}

