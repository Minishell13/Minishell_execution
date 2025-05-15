/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/15 16:58:25 by abnsila          ###   ########.fr       */
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

int main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	(void)ev;
	// char *line;
	// char *expanded;

	// while (1)
	// {
	// 	line = readline("> ");
	// 	if (!line)
	// 	{
	// 		printf("exit\n");
	// 		break;
	// 	}

	// 	if (*line)
	// 		add_history(line);

	// 	expanded = process_arg(line);
	// 	printf("%s\n", expanded);
	// 	free(expanded);

	// 	free(line);
	// }
	// rl_clear_history();

	//! Test Append an element to an array
	// printf("len: %d\n", arr_len(av));
	// char **arr = dup_arr(av);
	// char *str = ft_strdup("END");
	// char **new_arr = arr_append(arr, str);
	// if (!new_arr)
	// {
	// 	clear_arr(arr);
	// 	free(str);
	// 	return (EXIT_FAILURE);
	// }
	// clear_arr(arr);

	//! Test Merge two arrays
	char **arr1 = dup_arr(av);
	char **arr2 = dup_arr(av);
	char **new_arr = merge_arr(arr1, arr2);
	if (!new_arr)
	{
		clear_arr(arr1);	
		clear_arr(arr2);	
		return (EXIT_FAILURE);
	}
	
	print_arr(new_arr);
	clear_arr(new_arr);
	return (EXIT_SUCCESS);
}

