/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:37 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/30 19:48:16 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- SUBSHELL --------------------------------
void	execute_subshell(t_ast *root, t_ast *node, t_bool no_fork)
{
	pid_t pid;
	int   status;

	// TODO: Global redir node
	if (node->child && node->child->type == GRAM_IO_REDIRECT)
		execute_redirection(node->child);
	if (no_fork)
		executor(root, node->child);
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
