/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/12 15:17:57 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: i must expand var inside neested quotes

t_quote	which_quote(char c)
{
	if (c == '\'')
		return (SINGLE_Q);
	else if (c == '"')
		return (DOUBLE_Q);
	else
		return (NONE);
}

char	*extarct_var_value(char *arg, int *i)
{
	char	*var;
	char	*value;

	var = ft_calloc(1, 1);
	while (arg[*i] && which_quote(arg[*i]) == NONE)
	{
		var = ft_charjoin(var, arg[*i]);
		if (!var)
			return (NULL);
		(*i)++;
	}
	value = getenv(var);
	if (!value)
		return (NULL);
	return (ft_strdup(value));
}

//* -------------------------- Process modes --------------------------
void	default_mode(char *arg, char *value, int *i)
{
	while (arg[*i] && which_quote(arg[*i + 1]) == NONE)
	{
		// Do not expand ($' and $")
		if ((arg[*i] == '$' && which_quote(arg[*i + 1]) != NONE))
			break ;
		// Do not expand special char exept for $?
		else if (arg[*i] == '$' && ft_isalnum(arg[*i + 1]) == 0)
		{
			// Expand to exit code
			if (arg[*i + 1] == '?')
				value = ft_conststrjoin(value, ft_strdup("1337"));
			// Default action
			value = ft_charjoin(value, arg[*i]);
			(*i)++;
			value = ft_charjoin(value, arg[*i]);
		}
		// Expand var to value
		else if (arg[*i] == '$' && which_quote(arg[*i + 1]) == NONE)
		{
			(*i)++;
			value = ft_conststrjoin(value, extarct_var_value(arg, i));
		}
		// Do not expand simple char
		else
			value = ft_charjoin(value, arg[*i]);
		(*i)++;
	}
}

void	expand_mode(char *arg, char *value, int *i)
{
	while (arg[*i] && which_quote(arg[*i + 1]) == DOUBLE_Q)
	{
		// Reach the end of expansion
		if (which_quote(arg[*i + 1]) == DOUBLE_Q)
			break ;
		// Do not expand special char exept for $?
		else if (arg[*i] == '$' && ft_isalnum(arg[*i + 1]) == 0)
		{
			// Expand to exit code
			if (arg[*i + 1] == '?')
				value = ft_conststrjoin(value, ft_strdup("1337"));
			// Default action
			value = ft_charjoin(value, arg[*i]);
			(*i)++;
			value = ft_charjoin(value, arg[*i]);
		}
		// Do not expand ($' and $")
		else if ((arg[*i] == '$' && which_quote(arg[*i + 1]) != NONE))
			value = ft_charjoin(value, arg[*i]);
			// Expand var to value
		else if (arg[*i] == '$' && which_quote(arg[*i + 1]) == NONE)
		{
			(*i)++;	
			value = ft_conststrjoin(value, extarct_var_value(arg, i));
		}
		// Do not expand simple char
		else
			value = ft_charjoin(value, arg[*i]);
		(*i)++;
	}
}

void	literal_mode(char *arg, char *value, int *i)
{
	while (arg[*i] && which_quote(arg[*i + 1]) != SINGLE_Q)
	{
		value = ft_charjoin(value, arg[*i]);
		(*i)++;
	}
}

char	*expand_var_to_str(char *arg)
{
	int				i;
	char			*value;
	t_quote_mode	mode;

	value = ft_calloc(1, 1);
	if (!value)
		return (NULL);
	i = 0;
	mode = DEFAULT;
	while (arg[i])
	{
		printf("arg[%d]: %c\n", i, arg[i]);
		// Set Process mode
		if (which_quote(arg[i]) == SINGLE_Q)
			mode = LITERAL;
		else if (which_quote(arg[i]) == DOUBLE_Q)
			mode = EXPAND;
		else
			mode = DEFAULT;
		printf("mode: %d\n", mode);
		i++;
		// Process arg
		if (mode == DEFAULT)
		{
			printf("-------------- Default ---------------\n");
			default_mode(arg, value, &i);
		}
		else if (mode == EXPAND)
		{
			printf("-------------- Expand ---------------\n");
			expand_mode(arg, value, &i);
		}
		else if (mode == LITERAL)
		{
			printf("-------------- Literal ---------------\n");
			literal_mode(arg, value, &i);
		}
		i++;
	}
	return (value);
}

void	expand_var_in_argv(t_ast *ast)
{
	int		i;
	char	**args;

	i = 0;
	args = ast->data.args;
	while (args[i])
	{
		if (args[i][0] == '$')
		i++;
	}
}