/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 17:14:17 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Need To expand just to (&&) (||), then execute, after that expand again
// TODO: expand before expand wildrad to the previous condition then repeat again
// TODO: Maybe i need to test this in bash

extern	t_minishell	sh;

char	**process_arg(char *arg, t_bool(*f)(char *, t_qmode, char ***, char **, int *))
{
	int				i;
	char			*value;
	char			**arr;
	t_qmode	mode;
	
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
		if (f(arg, mode, &arr, &value, &i))
			continue ;
		i++;
	}
	return (arr);
}

void	expand_redir(t_ast *node)
{
	// heredoc first
	if (node->data.redir.type == GRAM_HEREDOC)
		remove_quotes(&(node->data.redir));
	else
	{
		char **arr = process_arg(node->data.redir.file, process_mode_1);
		int	len = len_arr(arr);
		if (len != 1)
		{
			perror("sh");
			clear_arr(arr);
		}
		else
		{
			free(node->data.redir.file);
			node->data.redir.file = ft_strdup(arr[0]);
			clear_arr(arr);	
		}
	}
	ast_print(node, 0);
}

//TODO:  $ + *
// void expand_cmd_node(t_ast *cmd)
// {
//     // args: char ** before expansion
//     char **new_args = NULL;
//     for (int i = 0; cmd->data.args[i]; i++)
//     {
//         char **parts    = process_arg(cmd->data.args[i]);
//         char **with_glob = wildcard_expand_arr(parts);
//         clear_arr(parts);

//         new_args = merge_arr(new_args ? new_args : dup_arr(cmd->data.args), 
//                              with_glob);
//         clear_arr(with_glob);
//     }
//     clear_arr(cmd->data.args);
//     cmd->data.args = new_args;
// }

void	expand_cmd_node(t_ast *node, t_bool(*f)(char *, t_qmode, char ***, char **, int *))
{
	// args: char ** before expansion
	char	**new_args = init_arr();

	for (int i = 0; node->data.args[i]; i++)
	{
		char **parts = process_arg(node->data.args[i], f);

		new_args = merge_arr(new_args, parts);
	}
	clear_arr(node->data.args);
	node->data.args = new_args;
}



// void	expand_tree(t_ast *node, int indent)
// {
// 	if (!node)
// 		return;

// 	// First recurse into children
// 	expand_tree(node->left, indent + 2);
// 	expand_tree(node->right, indent + 2);
		
// 	if (node->type == GRAM_SIMPLE_COMMAND)
// 	{
// 		expand_node_args(node);
// 		// printf("---------------------- Printing [ node->data.args ] ----------------------\n");
// 		ft_print_ast_node(node, indent);
// 		// printf("----------------------      END [ node->data.args ] ----------------------\n");
// 	}
// 	else if (node->type == GRAM_IO_REDIRECT)
// 	{
// 		expand_redir(node);
// 	}
// }
