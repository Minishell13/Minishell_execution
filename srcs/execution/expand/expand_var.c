/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 17:13:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_minishell	sh;


char	**process_arg(char *arg)
{
	int				i;
	char			*value;
	char			**arr;
	t_q_mode	mode;
	
	i = 0;
	mode = DEFAULT;
	arr = (char **) ft_calloc(1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (arg[i])
	{
		if (is_quote(arg[i]) == SINGLE_Q)
			mode = LITERAL;
		else if (is_quote(arg[i]) == DOUBLE_Q)
			mode = EXPAND;
		else
			mode = DEFAULT;
		value = ft_strdup("");
		if (process_mode(arg, mode, &arr, &value, &i))
			continue ;
		i++;
	}
	return (arr);
}

void	expand_node_args(t_ast *ast)
{
	int		i;
	char	**args;
	char	**new_args = (char **) ft_calloc(1, sizeof(char *));
	new_args[0] = NULL;

	i = 0;
	args = ast->data.args;
	if (!args)
		return ;
	while (args[i])
	{
		new_args = merge_arr(new_args, process_arg(args[i]));
		i++;
	}
	clear_arr(ast->data.args);
	ast->data.args = new_args;
}

// TODO: Need To expand just to (&&) (||), then execute, after that expand again
// TODO: expand before expand wildrad to the previous condition then repeat again
// TODO: Maybe i need to test this in bash

void	expand_tree(t_ast *node)
{
	if (!node)
		return;

	// First recurse into children
	expand_tree(node->left);
	expand_tree(node->right);

	if (node->type == GRAM_SIMPLE_COMMAND)
	{
		expand_node_args(node);
		printf("---------------------- Printing [ node->data.args ] ----------------------\n");
		print_arr(node->data.args);
		printf("----------------------      END [ node->data.args ] ----------------------\n");
	}
	else if (node->type == GRAM_IO_REDIRECT)
	{
		
	}
	
}
