/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 15:02:32 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Look at those case with wildcard, to know about wildrad and VAR expansion bahavioure
// abnsila@c3r4p10:~/Desktop/ms2$ ls
// config	includes  libft  Makefile  minishell  README.md  srcs
// abnsila@c3r4p10:~/Desktop/ms2$ export a="m"
// abnsila@c3r4p10:~/Desktop/ms2$ echo "$a"*
// minishell
// abnsila@c3r4p10:~/Desktop/ms2$ echo $a
// m
// abnsila@c3r4p10:~/Desktop/ms2$ echo "$a"
// m
// abnsila@c3r4p10:~/Desktop/ms2$ echo $a*
// minishell
// abnsila@c3r4p10:~/Desktop/ms2$ echo "$a"*
// minishell
// abnsila@c3r4p10:~/Desktop/ms2$ echo "$a""*"
// m*



int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	setup_env(env);
	char *line;

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

		// Array of expanded args
		char **new_arr = process_arg(line);
		if (!new_arr)
		{
			clear_arr(new_arr);	
			return (EXIT_FAILURE);
		}
		
		print_arr(new_arr);
		clear_arr(new_arr);

		free(line);
	}
	rl_clear_history();
	
	// // char **new_arr = process_arg("*$a$USER*\"gg\"\"$SHELL\"\"$a\"");
	// // char **new_arr = process_arg("$?\"$SHELL\"$a*_?'$?$?'$_\"$USER\"");
	// // TODO : Leak fixed, you can continue in this logic (but keep in mind this solution must be compatible with * wildcard)
	// char **new_arr = process_arg("'LIT'$a\"EXP\"plain$?''\"$PWD\"LIT2");;
	// if (!new_arr)
	// {
	// 	clear_arr(new_arr);	
	// 	return (EXIT_FAILURE);
	// }
	
	// print_arr(new_arr);
	// clear_arr(new_arr);
	
	// clear_arr(sh.my_env);
	// return (EXIT_SUCCESS);
}



// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)env;

// 	if (ac != 2)
// 		return (EXIT_FAILURE);
// 	t_ast* root = ft_get_ast_example(ft_atoi(av[1]));

// 	expand_tree(root);
	
// 	ft_destroy_ast(root);

// 	return (EXIT_SUCCESS);
// }
