/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/28 16:53:58 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_ast *node)
{
	int	i;

	if (!no_args(node->data.args))
		return (builtins_error("env", NULL, ": no options allowed"));
	i = 0;
	if (!sh.my_env)
		return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}
