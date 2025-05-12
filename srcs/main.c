/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/12 15:18:37 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	sh;

// TODO: Bro test in bash !!!!!!!!!!!!!!!!
int	main0(int ac, char **av, char **ev)
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


int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	(void)ev;
	int i = 0;
	char  *line;
	char *value;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}

		printf("line: %s\n", line);
		i = 0;
		// value = extarct_var_value(ft_strdup(line), &i);
		// TODO: First test => "OK$SHELL"'$PATH'$SHELL
		value = expand_var_to_str(ft_strdup(line));
		printf("value: %s\n", value);
		free(value);

		free(line);
	}

	return (EXIT_SUCCESS);
}
