/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:49:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 22:04:38 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: The anv of your shell must be setuped correctly
//TODO: Create those utils: add_var, get_var, pop_var, 
//TODO: also:

t_bool	var_exist(char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (sh.env[i])
	{
		if (ft_strncmp(sh.env[i], key, key_len) == 0
			&& key_len == ft_strlen(sh.env[i]))
		{
			return (true);
		}
		i++;
	}
	return (false);
}

int	get_var_index(char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (sh.my_env[i])
	{
		if (ft_strncmp(sh.my_env[i], key, key_len) == 0
			&& sh.my_env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	unset_var(char *key)
{
	int		i;
	size_t	key_len;
	char	**new_env = ft_calloc(1, sizeof(char *));

	i = 0;
	key_len = ft_strlen(key);
	while (sh.my_env[i])
	{
		if (ft_strncmp(sh.my_env[i], key, key_len) == 0
			&& sh.my_env[i][key_len] == '=')
		{
			i++;
			continue ;
		}
		new_env = arr_append(new_env, ft_strdup(sh.my_env[i]));
		i++;
	}
	clear_arr(sh.my_env);
	sh.my_env = new_env;
}

char	*get_value(char *key)
{
	int		i;
	size_t	key_len;
	char	*value;

	i = 0;
	key_len = ft_strlen(key);
	while (sh.my_env[i])
	{
		if (ft_strncmp(sh.my_env[i], key, key_len) == 0
			&& sh.my_env[i][key_len] == '=')
		{
			value = sh.my_env[i] + key_len;
			value = ft_strdup(value + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

void	add_var(char *key, char *value)
{
	char	*tmp;
	char	*new_var;
	int		var_index;

	var_index = get_var_index(key);
	tmp = ft_strjoin(key, "=");
	new_var = ft_strjoin(tmp, value);
	// printf("joined: %s\n", new_var);
	free(tmp);
	if (var_index != -1)
		sh.my_env[var_index] = new_var;
	else
		sh.my_env = arr_append(sh.my_env, new_var);
}

void	setup_env(char **env)
{
	int	i;

	i = 0;
	sh.my_env = ft_calloc(1, sizeof(char *));
	if (!sh.my_env)
		return ;
	while (env[i])
	{
		sh.my_env = arr_append(sh.my_env, ft_strdup(env[i]));
		i++;
	}
}

