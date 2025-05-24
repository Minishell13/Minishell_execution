/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:21 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 15:45:17 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	exec_pwd()
{
	char *pwd;

	pwd = getcwed(NULL, 0);
	if (!pwd) 
	{
		pwd = get_value("PWD");
		if (!pwd)
		{
			perror("sh");
			return (ERROR);
		}
		printf("%s\n", pwd);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}
