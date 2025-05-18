/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:59:25 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/18 20:04:32 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	(void)ev;

	char *line;
	char *expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}

		if (*line)
			add_history(line);


		t_error code = cd(line, ev);
		if (code != SUCCESS)
		{
			return (EXIT_FAILURE);
		}

		free(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
		
}