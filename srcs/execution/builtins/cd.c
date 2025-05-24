/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:05 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 16:20:23 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	exec_cd(t_ast *node)
{
	char	*path;

	if (check_input(node->data.args))
	{
		ft_putendl_fd("sh: cd: no options allowed", STDERR_FILENO);
		return (ERROR);
	}
	path = node->data.args[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (ERROR);
	}
	return (SUCCESS);
}
