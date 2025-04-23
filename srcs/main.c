/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/23 16:48:10 by abnsila          ###   ########.fr       */
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

void	ft_get_tokens(t_token **list)
{
	t_token	*t1;
	t_token	*t2;
	t_token	*t3;
	t_token	*t4;
	t_token	*t5;
	t_token	*t6;
	t_token	*t7;

	t1 = ft_new_token("cat", TOK_WORD);
	t2 = ft_new_token("file.txt", TOK_WORD);
	t3 = ft_new_token("|", TOK_PIPE);
	t4 = ft_new_token("grep", TOK_WORD);
	t5 = ft_new_token("foo", TOK_WORD);
	t6 = ft_new_token(">", TOK_REDIR_OUT);
	t7 = ft_new_token("out.txt", TOK_WORD);
	
	ft_add_token(list, t1);
	ft_add_token(list, t2);
	ft_add_token(list, t3);
	ft_add_token(list, t4);
	ft_add_token(list, t5);
	ft_add_token(list, t6);
	ft_add_token(list, t7);
}

int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	(void)ev;
	t_token *list;

	list = NULL;
	// char *rl;
	// rl = readline("Prompt > ");
	// printf("%s\n", rl);
	ft_get_tokens(&list);
	ft_print_tokens(list);
	ft_clear_tokens(&list);
	return (EXIT_SUCCESS);
	// exit(EXIT_SUCCESS);
}
