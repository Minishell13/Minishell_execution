/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_V0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/15 17:08:09 by abnsila          ###   ########.fr       */
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
			&& arg[*i] != '$' && ft_isspace(arg[*i]) == 0)
	{
		var = ft_charjoin(var, arg[*i]);
		if (!var)
			return (NULL);
		(*i)++;
	}
	value = getenv(var);
	free(var);
	// printf("[End of extract]     arg[%d]: %c\n", *i, arg[*i]);
	// printf("value: %s\n", value);
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
	(void)value;
	while (arg[*i] && is_quote(arg[*i]) == NONE)
	{
		// printf("[Default]     arg[%d] : %c\n", *i, arg[*i]);
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
		// printf("[Expand]     arg[%d]: %c\n", *i, arg[*i]);
		if (try_expand_dollar(arg, value, i))
			continue ;
		// Do not expand simple char
		else
			*value = ft_charjoin(*value, arg[*i]);
		(*i)++;
	}
	// printf("End value: %s\n", *value);
	//TODO: return an array with one element not splited by space
}

void	literal_mode(char *arg, char **value, int *i)
{
	while (arg[*i] && is_quote(arg[*i]) != SINGLE_Q)
	{
		// printf("[Literal]     arg[%d]: %c\n", *i, arg[*i]);
		*value = ft_charjoin(*value, arg[*i]);
		(*i)++;
	}
	// printf("End value: %s\n", *value);
}

char	*process_arg(char *arg)
{
	//TODO: Change the return from char * to char ** (array of string)
	//TODO:  expand a=".md i"
	//TODO:  echo *$a* = ["*.md", "i*"]  but  echo *"$a"* = [".md", "i"]
	int				i;
	char			*value;
	t_quote_mode	mode;

	value = ft_strdup("");
	if (!value)
		return (NULL);
	i = 0;
	mode = DEFAULT;
	while (arg[i])
	{
		// printf("[[Begin mode]]    arg[%d]: %c\n", i, arg[i]);
		// Set Process mode
		if (is_quote(arg[i]) == SINGLE_Q)
			mode = LITERAL;
		else if (is_quote(arg[i]) == DOUBLE_Q)
			mode = EXPAND;
		else
			mode = DEFAULT;
		// printf("mode: %d\n", mode);
		// Process arg
		if (mode == DEFAULT)
		{
			// printf("-------------- Default ---------------\n");
			default_mode(arg, &value, &i);
			continue ;
			// printf("[[End mode]]    arg[%d]: %c\n", i, arg[i]);
		}
		else if (mode == EXPAND)
		{
			i++;
			// printf("-------------- Expand ---------------\n");
			expand_mode(arg, &value, &i);
			// printf("[[End mode]]    arg[%d]: %c\n", i, arg[i]);
		}
		else if (mode == LITERAL)
		{
			i++;
			// printf("-------------- Literal ---------------\n");
			literal_mode(arg, &value, &i);
			// printf("[[End mode]]    arg[%d]: %c\n", i, arg[i]);
		}
		i++;
	}
	return (value);
}

void	expand_node_args(t_ast *ast)
{
	int		i;
	char	**args;
	char	*new_arg;

	i = 0;
	args = ast->data.args;
	if (!args)
		return ;
	// TODO: new args = [...]          arg => [*.md, *i]
	while (args[i])
	{
		new_arg = process_arg(args[i]);
		free(args[i]);
		args[i] = NULL;
		args[i] = new_arg;
		i++;
	}
}

// TODO: Need To expand just to (&&) (||), then execute, after that expand again
// TODO: expand before expand wildrad to the previous condition then repeat again
// TODO: Maybe i need to test this in bash

void	expand_tree(t_ast *node)
{
	if (!node)
		return;

	expand_node_args(node);

	// First recurse into children
	expand_tree(node->left);
	expand_tree(node->right);

}
