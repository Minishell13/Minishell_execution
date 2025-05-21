/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:57:30 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 16:58:00 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
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

void	append_args(char ***arr, char **value, t_q_mode mode)
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

t_bool	process_mode(char *arg, t_q_mode mode, char ***arr, char **value, int *i)
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
