/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:46:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/27 18:04:09 by abnsila          ###   ########.fr       */
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
	t_bool	flag;

	if (write(STDOUT_FILENO, "", 0) == -1)
	{	
		sh.exit_code = EXIT_FAILURE;
		return (ERROR);
	}
	args = node->data.args;
	flag = check_flag(node->data.args[1]);
	if (flag)
		i = 2;
	else
		i = 1;
	while (args[i])
	{
		if ((!flag && i > 1) || (flag && i > 2))
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
