/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/23 15:26:21 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// ┌───────────────┬────────────────┐
// │ Token Type    │ Lexeme         │
// ├───────────────┼────────────────┤
// │ WORD          │ "cat"          │
// │ WORD          │ "file.txt"     │
// │ PIPE          │ "|"            │
// │ WORD          │ "grep"         │
// │ WORD          │ "foo"          │
// │ REDIR_OUT     │ ">"            │
// │ WORD          │ "out.txt"      │
// │ END_OF_INPUT  │ NULL           │
// └───────────────┴────────────────┘

void	ft_get_token_arry(t_token_type *arr)
{
	
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char *rl;
	rl = readline("Prompt > ");
	printf("%s\n", rl);
	return (0);
	// exit(EXIT_SUCCESS);
}
