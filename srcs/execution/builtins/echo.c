/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:46:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 17:12:05 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_flag(char *arg)
{
	size_t  len;

	len = ft_strlen(arg);
	if (len == 2 && arg[0] == '-' && arg[1] == 'n')
		return (true);
	return (false);
}

t_error	exec_echo(t_ast *node)
{
	int		i;
	char	**args;

	i = 1;
	args = node->data.args;
	while (args[i])
	{
		if (i != 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
	}
	if (!check_flag(node->data.args[1]))
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
