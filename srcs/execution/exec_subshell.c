/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:37 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/27 16:38:42 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- SUBSHELL --------------------------------
void	execute_subshell(t_ast *root, t_ast *node)
{
	pid_t pid;
	int   status;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		// printf("Subshell Fork\n");
		executor(root, node->child);
		clear_sh(root);
		exit(sh.exit_code);
	}
	waitpid(pid, &status, 0);
	sh.exit_code = WEXITSTATUS(status);
}
