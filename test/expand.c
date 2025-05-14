/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/14 19:48:07 by abnsila          ###   ########.fr       */
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

int main(void)
{
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

		expanded = process_arg(line);
		printf("%s\n", expanded);
		free(expanded);

		free(line);
	}

	// arg = ft_strdup("\"OK$SHELL'$SHELL$\"'$PATH$'$SHELL$");
	// value = process_arg(arg);
	// printf("%s\n", value);
	// free(arg);
	// free(value);

	rl_clear_history();

	return 0;
}

