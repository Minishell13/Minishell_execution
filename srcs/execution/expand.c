/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:51:59 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/09 16:57:59 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var(t_ast *ast)
{
	expand_var(ast->left);
	expand_var(ast->right);
}

void	expand_wildcard(t_ast *ast)
{
	expand_wildcard(ast->left);
	expand_wildcard(ast->right);
}

void	expansions(t_ast *ast)
{
	
    expansions(ast->left);
    expansions(ast->right);
}
