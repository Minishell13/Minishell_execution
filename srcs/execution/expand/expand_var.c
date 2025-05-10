/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/10 17:56:48 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: i must expand var inside neested quotes

t_quote	is_quote(char c)
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
	(void)arg;
	(void)i;
	char	*var = ft_calloc(1, 1);

	while (arg[*i] && is_quote(arg[*i]) == NONE)
	{
		var = ft_charjoin(var, arg[*i]);
		if (!var)
			return (NULL);
		(*i)++;
	}
	return (ft_strdup(getenv(var)));
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
		if (mode == NONE)
		{
			if (is_quote(arg[i] == SINGLE_Q))
				mode = LITERAL;
			else if (is_quote(arg[i] == DOUBLE_Q))
				mode = EXPAND;
		}
		if (mode == EXPAND)
		{
			j = i;
			while (arg[i] && is_quote(arg[i + 1]) == DOUBLE_Q)
			{
				
				if (arg[i] != '$' || (arg[i] == '$' && is_quote(arg[i + 1]) != DOUBLE_Q))
					value = ft_charjoin(value, arg[i]);
				else if (arg[i] == '$' && is_quote(arg[i + 1]) == NONE)
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