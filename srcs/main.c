/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/30 18:00:57 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	sh;



int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	(void)ev;
	t_ast *root;

	if (ac != 2)
		return (EXIT_FAILURE);
	//? Display All ast examples
	// for (int i = 0; i < 15; i++)
	// {
	// 	printf("\n\nAST Example: %d\n", i);
	// 	root = ft_get_ast_example(i);
	// 	ft_print_ast(root, 0);
	// 	ft_destroy_ast(root);
	// }
	root = ft_get_ast_example(ft_atoi(av[1]));
	ft_print_ast(root, 0);
	ft_executor(root, root, ev);
	ft_destroy_ast(root);
	return (EXIT_SUCCESS);
}
