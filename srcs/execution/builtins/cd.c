/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:05 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 16:05:06 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(t_ast *node)
{
	char	*path;
	int		len;

	len = len_arr(node->data.args);
	if (len == 1)
	{
		fdprintf(STDERR_FILENO,
				"minishell: cd: no relative or absolute path\n");
		return (EXIT_FAILURE);
	}
	if (len > 2)
	{
		fdprintf(STDERR_FILENO,
				"minishell: cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	path = node->data.args[1];
	if (chdir(path) != 0)
	{
		fdprintf(STDERR_FILENO,
				"minishell: cd: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
