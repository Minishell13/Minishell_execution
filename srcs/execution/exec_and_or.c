/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:59 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/26 16:47:30 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//* -------------------------------- AND_OR --------------------------------
t_error	execute_and_or(t_ast *root, t_ast *node, char **envp)
{
	int	st;

	st = executor(root, node->child, envp);
	
	if (node->type == GRAM_OPERATOR_AND && st == 0)
		return executor(root, node->child->sibling, envp);
	if (node->type == GRAM_OPERATOR_OR && st != 0)
		return executor(root, node->child->sibling, envp);
	return (st);
}
