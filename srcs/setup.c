/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:49:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/19 12:02:49 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
