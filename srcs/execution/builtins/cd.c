/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:05 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/28 16:53:40 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(t_ast *node)
{
	char	*path;
	int		len;

	len = len_arr(node->data.args);
	if (len == 1)
		return (builtins_error("cd", NULL, ": no relative or absolute path"));
	if (len > 2)
		return (builtins_error("cd", NULL, ": too many arguments"));
	path = node->data.args[1];
	if (chdir(path) != 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
