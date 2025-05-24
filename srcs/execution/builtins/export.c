/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:30 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 16:23:34 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_key(char *arg)
{
	int	i;

	i = 0;
	if (!ft_strchr(arg, '='))
		return (-1);
	while (arg[i] && arg[i] != '=')
	{
		if (i == 0 && !(ft_isalpha(arg[i]) || arg[i] == '_'))
			return (-1);
		else if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (-1);
		i++;
	}
	return (i);
}

char	*extract_key(char *arg, int end)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_strdup("");
	while (arg[i] && i < end)
	{
		key = ft_charjoin(key, arg[i]);
		i++;
	}
	return (key);
}

char	*extract_value(char *arg, int end)
{
	char	*value;

	value = ft_strdup("");
	while (arg[end])
	{
		value = ft_charjoin(value, arg[end]);
		end++;
	}
	return (value);
}

int	parse_input(char *arg)
{
	int		end;

	end = valid_key(arg);
	return (end);
}

t_error	exec_export(t_ast *node)
{
	int		i;
	int		end;
	char	*key;
	char	*value;
	char	**args;

	i = 1;
	args = node->data.args;
	while (args[i])
	{
		end = parse_input(args[i]);
		if (end != -1)
		{
			key = extract_key(args[i], end);
			value = extract_value(args[i], end + 1);
			add_var(key, value);
			free(key);
			free(value);
		}
		else
		{
			ft_putendl_fd("sh: export: not a valid identifier", STDERR_FILENO);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
