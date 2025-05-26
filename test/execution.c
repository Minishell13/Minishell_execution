/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:58:05 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/26 18:48:17 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	setup_env(env);
	if (ac != 2)
		return (EXIT_FAILURE);
	t_ast* root = ft_get_ast_example(ft_atoi(av[1]));
	
	// ast_print(root, 0);
	executor(root, root, env);


	printf("exit code: %d\n", sh.exit_code);
	ast_destroy(root);
	clear_arr(sh.my_env);

	return (EXIT_SUCCESS);
}

