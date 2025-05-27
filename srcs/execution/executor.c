/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:45:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/27 08:53:21 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: You need first to know the exact struct of AST tree
// TODO: The representation each node with his type and args
// TODO: How to parcoure throw this three and get nodes in the correct order
// TODO: Create functions for execution (per node type)
// TODO: Focus on execution flow, (memory, fds, error) management
// TODO: The leaks is fixed, now go and make behavioure like shell
// TODO: ...

t_error executor(t_ast *root, t_ast *node, char **envp)
{
	if (!node) return SUCCESS;

	switch (node->type)
	{
	case GRAM_COMPLETE_COMMAND:
		return executor(root, node->child, envp);

	case GRAM_OPERATOR_AND:
	case GRAM_OPERATOR_OR:
		return execute_and_or(root, node, envp);

	case GRAM_PIPELINE:
		return execute_pipeline(root, node, envp);

	case GRAM_IO_REDIRECT:
		return execute_redirection(root, node, envp);

	case GRAM_SIMPLE_COMMAND:
		return execute_simple_cmd(root, node, envp, false);

	case GRAM_SUBSHELL:
		return execute_subshell(root, node, envp);

	default:
		return SUCCESS;
	}
}
