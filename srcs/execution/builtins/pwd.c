/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:21 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/27 18:07:04 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	exec_pwd(t_ast *node)
{
	char *pwd;

	if (check_input(node->data.args))
	{
		ft_putendl_fd("sh: pwd: no options allowed", STDERR_FILENO);
		sh.exit_code = EXIT_FAILURE;
		return (ERROR);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd) 
	{
		pwd = get_value("PWD");
		if (!pwd)
		{
			perror("sh");
			sh.exit_code = EXIT_FAILURE;
			return (ERROR);
		}
		printf("%s\n", pwd);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (SUCCESS);
}
