/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 16:12:48 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_minishell	sh;

char	*get_exit_code()
{
	char	*value;

	value = ft_itoa(sh.exit_code);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

int	is_valid(char c)
{
	return (ft_isalnum(c) || c == '_');
}

t_quote	is_quote(char c)
{
	if (c == '\'')
		return (SINGLE_Q);
	else if (c == '"')
		return (DOUBLE_Q);
	else
		return (NONE);
}

char	*extract_var_value(char *arg, int *i)
{
	char	*var;
	char	*value;

	var = ft_strdup("");
	while (arg[*i] && (is_quote(arg[*i]) == NONE)
		&& is_valid(arg[*i]) && ft_isspace(arg[*i]) == 0)
	{
		var = ft_charjoin(var, arg[*i]);
		if (!var)
			return (NULL);
		(*i)++;
	}
	value = getenv(var);
	free(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

t_bool	try_expand_dollar(char *arg, char **value, int *i)
{
	if (arg[*i] != '$')
		return (false);
	// Do not expand ($' and $")
	else if (arg[*i + 1] && is_quote(arg[*i + 1]))
		return (false);
	// Expand to exit code
	else if (arg[*i + 1] == '?')
	{	
		*value = ft_conststrjoin(*value, get_exit_code());
		*i += 2;
	}
	// Do not expand special char exept for ($?) ($_...)
	else if (arg[*i + 1] && ft_isalnum(arg[*i + 1]) == 0
		&& arg[*i + 1] != '_' && is_quote(arg[*i + 1]) == NONE)
	{
		*value = ft_charjoin(*value, arg[*i]);
		(*i)++;
		*value = ft_charjoin(*value, arg[*i]);
		(*i)++;
	}
	// Expand var to *value
	else
	{
		(*i)++;
		*value = ft_conststrjoin(*value, extract_var_value(arg, i));
	}
	return (true);
}
	
//* -------------------------- Process modes --------------------------
void	default_mode(char *arg, char **value, int *i)
{
	while (arg[*i] && is_quote(arg[*i]) == NONE)
	{
		// Keep the ($) at the end
		if (arg[*i] == '$' && arg[*i + 1] == '\0')
			*value = ft_charjoin(*value, arg[*i]);
		// Skip the ($) if quote comes after
		else if (arg[*i] == '$' && arg[*i + 1] && is_quote(arg[*i + 1]))
		{
			(*i)++;
			break ;
		}
		else if (try_expand_dollar(arg, value, i))
			continue ;
		// Do not expand simple char
		else
			*value = ft_charjoin(*value, arg[*i]);
		(*i)++;
	}
	//TODO: return a splited array by space
}

void	expand_mode(char *arg, char **value, int *i)
{
	while (arg[*i] && is_quote(arg[*i]) != DOUBLE_Q)
	{
		if (try_expand_dollar(arg, value, i))
			continue ;
		// Do not expand simple char
		else
			*value = ft_charjoin(*value, arg[*i]);
		(*i)++;
	}
}

void	literal_mode(char *arg, char **value, int *i)
{
	while (arg[*i] && is_quote(arg[*i]) != SINGLE_Q)
	{
		*value = ft_charjoin(*value, arg[*i]);
		(*i)++;
	}
}

void	append_args(char ***arr, char **value, t_quote_mode mode)
{
	if (mode == DEFAULT)
	{
		*arr = inner_merge_arr(*arr, ft_split(*value, ' '));
		free(*value);
	}
	else
	{
		if (arr_len(*arr) == 0)
		{	
			*arr = arr_append(*arr, ft_strdup(*value));
			free(*value);
		}
		else
		*last_item_ptr(*arr) = ft_conststrjoin(*last_item_ptr(*arr), *value);
	}
}

t_bool	process_mode(char *arg, t_quote_mode mode, char ***arr, char **value, int *i)
{
		if (mode == DEFAULT)
		{
			printf("-------------- Default ---------------\n");
			default_mode(arg, value, i);
			append_args(arr, value, mode);
			return (true);
		}
		else if (mode == EXPAND)
		{
			(*i)++;
			printf("-------------- Expand ---------------\n");
			expand_mode(arg, value, i);
			append_args(arr, value, mode);
		}
		else if (mode == LITERAL)
		{
			(*i)++;
			printf("-------------- Literal ---------------\n");
			literal_mode(arg, value, i);
			append_args(arr, value, mode);
		}
		return (false);
}

char	**process_arg(char *arg)
{
	int				i;
	char			*value;
	char			**arr;
	t_quote_mode	mode;
	
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
	
}












//? Main expand Logic (from char	**process_arg(char *arg)) i replace it with a short version
// if (mode == DEFAULT)
// {
// 	printf("-------------- Default ---------------\n");
// 	default_mode(arg, &value, &i);
// 	arr = inner_merge_arr(arr, ft_split(value, ' '));
// 	free(value);
// 	continue ;
// }
// else if (mode == EXPAND)
// {
// 	i++;
// 	printf("-------------- Expand ---------------\n");
// 	expand_mode(arg, &value, &i);
	
// 	if (arr_len(arr) == 0)
// 	{	
// 		arr = arr_append(arr, ft_strdup(value));
// 		free(value);
// 	}
// 	else
// 		*last_item_ptr(arr) = ft_conststrjoin(*last_item_ptr(arr), value);
// }
// else if (mode == LITERAL)
// {
// 	i++;
// 	printf("-------------- Literal ---------------\n");
// 	literal_mode(arg, &value, &i);
	
// 	if (arr_len(arr) == 0)
// 	{	
// 		arr = arr_append(arr, ft_strdup(value));
// 		free(value);
// 	}
// 	else
// 		*last_item_ptr(arr) = ft_conststrjoin(*last_item_ptr(arr), value);
// }
