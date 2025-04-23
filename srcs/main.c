/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/23 16:13:37 by abnsila          ###   ########.fr       */
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

void	ft_get_token_arry(t_token **list)
{
	t_token	*t1;
	t_token	*t2;
	t_token	*t3;
	t_token	*t4;
	t_token	*t5;

	t1 = new("cat", TOK_WORD);
	t2 = new("file.txt", TOK_WORD);
	t3 = new("|", TOK_PIPE);
	t4 = new("grep", TOK_WORD);
	t5 = new("foo", TOK_WORD);
	
	add(list, t1);
	add(list, t2);
	add(list, t3);
	add(list, t4);
	add(list, t5);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_token *list;

	list = NULL;
	// char *rl;
	// rl = readline("Prompt > ");
	// printf("%s\n", rl);
	ft_get_token_arry(&list);
	print_token(list);
	ft_clear(&list);
	return (EXIT_SUCCESS);
	// exit(EXIT_SUCCESS);
}
