/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:30 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/19 12:35:39 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int valid_identifier(char c)
{
	return (ft_isalnum(c) || ft_strchr("_", c));
}

int extract_var_and_value(char *arg)
{
	int i = 0;
	char	*var = ft_strdup("");
	char	*value = ft_strdup("");
	// TODO: I need to expand First
	if (!(ft_isalpha(arg[i]) || ft_strchr("_", arg[i])))
		return (0);
	var = ft_charjoin(var, arg[i]);
	while (arg[i] && arg[i] != '=' && valid_identifier(arg[i]))
	{
		var = ft_charjoin(var, arg[i]);
		i++;
	}
}

char    **parse_input(char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		i++;
	}
}

t_error	exec_export(char *arg)
{
	
	return (SUCCESS);
}
