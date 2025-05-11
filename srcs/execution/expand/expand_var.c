/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/11 17:12:45 by abnsila          ###   ########.fr       */
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
		return (ft_strdup(var));
	return (ft_strdup(value));
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
				value = ft_charjoin(value, get_exit_code());
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
			value = ft_conststrjoin(value, extarct_var_value(arg, i));
		// Do not expand simple char
		else
			value = ft_charjoin(value, arg[*i]);
		(*i)++;
	}
}

char	*expand_var_to_str(char *arg)
{
	int		i;
	int		j;
	char	*value = ft_calloc(1, 1);
	t_quote_mode	mode = EXPAND;

	i = 0;
	
	while (arg[i])
	{
		// TODO: The default is (DEFAULT OR NONE ????)
		if (mode == NONE)
		{
			if (which_quote(arg[i] == SINGLE_Q))
				mode = LITERAL;
			else if (which_quote(arg[i] == DOUBLE_Q))
				mode = EXPAND;
		}
		if (mode == EXPAND || mode == DEFAULT)
		{
			j = i;
			while (arg[i] && which_quote(arg[i + 1]) == DOUBLE_Q)
			{
				
				if (arg[i] != '$' || ((arg[i] == '$' && which_quote(arg[i + 1]) != DOUBLE_Q)
					&& mode != DEFAULT))
					value = ft_charjoin(value, arg[i]);
				else if (arg[i] == '$' && which_quote(arg[i + 1]) == NONE)
					value = ft_conststrjoin(value, extarct_var_value(arg, &i));
				i++;
			}
		}
		if (arg[i] == '\'' || arg[i] == '"')
		i++;
	}
	return (NULL);
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