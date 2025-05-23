/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:49:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 20:00:04 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: The anv of your shell must be setuped correctly
//TODO: Create those utils: add_var, get_var, pop_var, 
//TODO: also:

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

void	set_var(char *key, char *value)
{
	
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
