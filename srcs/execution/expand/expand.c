/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:51:59 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/12 21:38:41 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	expand_tree(t_ast *node)
// {
// 	if (!node)
// 		return;

// 	// First recurse into children
// 	expand_tree(node->left);
// 	expand_tree(node->right);

// 	switch (node->type)
// 	{
// 		case GRAM_SIMPLE_COMMAND:
// 			// node->data.args is a NULL‐terminated char**
// 			expand_var_in_argv(node);
// 			expand_globbing_in_argv(node);
// 			break;

// 		case GRAM_IO_REDIRECT:
// 			// node->data.redir.file is a char*
// 			node->data.redir.file = expand_var_in_str(node->data.redir.file);
// 			node->data.redir.file = expand_globbing_in_str(node->data.redir.file);
// 			break;

// 		// for pipelines, AND, OR, COMPLETE, SUBSHELL, etc.
// 		default:
// 			break;
// 	}
// }

