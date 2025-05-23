/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:49:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 20:31:07 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: The anv of your shell must be setuped correctly
//TODO: Create those utils: add_var, get_var, pop_var, 
//TODO: also:

t_bool	var_exist(char *key)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(key);
	while (sh.env[i])
	{
		if (ft_strncmp(sh.env[i], key, len) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

void	unset_var(char *key)
{
	int		i;
	int		len;
	char	new_env = ft_calloc(1, sizeof(char *));

	i = 0;
	len = ft_strlen(key);
	while (sh.env[i])
	{
		if (ft_strncmp(sh.env[i], key, len) == 0)
		{
			return (true);
		}
		i++;
	}
}

char	*get_value(char *key)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	len = ft_strlen(key);
	while (sh.env[i])
	{
		if (ft_strncmp(sh.env[i], key, len) == 0)
		{
			value = sh.env[i] + len;
			value = ft_strdup(value + 1);
			return (value);
		}
		i++;
	}
}

void	add_var(char *key, char *value)
{
	if (var_exist(key))
		unset_var(key)
	// You nust unset then add
}

void	setup_env(char **env)
{
	int	i;

	i = 0;
	sh.env = env;
	sh.my_env = ft_calloc(1, sizeof(char *));
	if (!sh.my_env)
		return ;
	while (sh.env[i])
	{
		sh.my_env = arr_append(sh.my_env, ft_strdup(sh.env[i]));
		i++;
	}
}
