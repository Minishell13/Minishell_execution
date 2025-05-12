/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/12 21:34:33 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: First test => "OK$SHELL'$SHELL$"'$PATH$'$SHELL$
// arg = ft_strdup("\"OK$SHELL'$SHELL$\"'$PATH$'$SHELL$");
int	main2()
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
