/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/14 14:10:07 by abnsila          ###   ########.fr       */
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
int	main()
{
	char	*line;
	char	*value;
	char	*arg;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (EXIT_FAILURE);

		arg = ft_strdup(line);
		value = process_arg(arg);
		printf("%s\n", value);
		free(arg);
		free(value);
		free(line);
	}

	// arg = ft_strdup("\"OK$SHELL'$SHELL$\"'$PATH$'$SHELL$");
	// value = process_arg(arg);
	// printf("%s\n", value);
	// free(arg);
	// free(value);

	return (EXIT_SUCCESS);
}
