/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:37 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/26 17:00:46 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- SUBSHELL --------------------------------
t_error	execute_subshell(t_ast *root, t_ast *node, char **envp)
{
	pid_t pid;
	int   status;

	pid = fork();
	if (pid < 0)
		return FORK_ERROR;
	if (pid == 0)
	{
		executor(root, node->child, envp);
		ast_destroy(root);
		exit(EXIT_FAILURE);  // in case executor didn't exit
	}
	waitpid(pid, &status, 0);
	sh.exit_code = WEXITSTATUS(status);
	return (WEXITSTATUS(status));
}

