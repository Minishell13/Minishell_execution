/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/18 20:01:25 by abnsila          ###   ########.fr       */
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


// TODO: First test => "OK$SHELL'$SHELL$"'$PATH$'$SHELL$
// arg = ft_strdup("\"OK$SHELL'$SHELL$\"'$PATH$'$SHELL$");
// value = process_arg(arg);
// printf("%s\n", value);
// free(arg);
// free(value);

// int main(int ac, char **av, char **ev)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)ev;
// 	// char *line;
// 	// char *expanded;

// 	// while (1)
// 	// {
// 	// 	line = readline("> ");
// 	// 	if (!line)
// 	// 	{
// 	// 		printf("exit\n");
// 	// 		break;
// 	// 	}

// 	// 	if (*line)
// 	// 		add_history(line);

// 	// 	// expanded = process_arg(line);
// 	// 	// printf("%s\n", expanded);
// 	// 	// free(expanded);


// 	// 	char **new_arr = _process_arg(line);
// 	// 	if (!new_arr)
// 	// 	{
// 	// 		clear_arr(new_arr);	
// 	// 		return (EXIT_FAILURE);
// 	// 	}
		
// 	// 	print_arr(new_arr);
// 	// 	clear_arr(new_arr);

// 	// 	free(line);
// 	// }
// 	// rl_clear_history();
	
	
// 	// char **new_arr = _process_arg("*$a$USER*\"gg\"\"$SHELL\"\"$a\"");
// 	// char **new_arr = _process_arg("$?\"$SHELL\"$a*_?'$?$?'$_\"$USER\"");
// 	//TODO : fix the leak
// 	char **new_arr = _process_arg("\"$SHELL\"$a");
// 	if (!new_arr)
// 	{
// 		clear_arr(new_arr);	
// 		return (EXIT_FAILURE);
// 	}
	
// 	print_arr(new_arr);
// 	clear_arr(new_arr);
	
// 	return (EXIT_SUCCESS);
// }

