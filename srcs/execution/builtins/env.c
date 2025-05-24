/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 16:21:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	exec_env(t_ast *node)
{
	int	i;

	if (check_input(node->data.args))
	{
		ft_putendl_fd("sh: env: no options allowed", STDERR_FILENO);
		return (ERROR);
	}
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
		ft_putendl_fd(sh.my_env[i], STDOUT_FILENO);
		i++;
	}
	return (SUCCESS);
}
