/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:58:05 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 19:27:00 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	if (ac != 2)
		return (EXIT_FAILURE);
	t_ast* root = ft_get_ast_example(ft_atoi(av[1]));
	
	ft_executor(root, root, env);

	// ast_print(root, 0);
	
	ast_destroy(root);

	return (EXIT_SUCCESS);
}

