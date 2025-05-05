/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:59 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/05 14:36:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- AND_OR --------------------------------
t_error	ft_execute_and_or(t_ast *root, t_ast *node, char **envp)
{
	int left_status = ft_executor(root, node->left, envp);
	// &&: right only if left succeeded
	if (node->type == GRAM_OPERATOR_AND && left_status == 0)
		return ft_executor(root, node->right, envp);
	// ||: right only if left failed
	if (node->type == GRAM_OPERATOR_OR && left_status != 0)
		return ft_executor(root, node->right, envp);
	return left_status;
}

