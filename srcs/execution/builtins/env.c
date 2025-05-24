/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 09:45:21 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	exec_env()
{
	int	i;

	i = 0;
	if (!sh.my_env)
		return (ERROR);
	while (sh.my_env[i])
	{
		if (!sh.my_env[i])
		{
			i++;
			continue ;
		}
		printf("%s\n", sh.my_env[i]);
		i++;
	}
	return (SUCCESS);
}
