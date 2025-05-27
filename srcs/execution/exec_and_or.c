/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:59 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/27 17:45:01 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- AND_OR --------------------------------
void	execute_and_or(t_ast *root, t_ast *node)
{
	executor(root, node->child);
	if (node->type == GRAM_OPERATOR_AND && sh.exit_code == 0)
		executor(root, node->child->sibling);
	else if (node->type == GRAM_OPERATOR_OR && sh.exit_code != 0)
		executor(root, node->child->sibling);
}
