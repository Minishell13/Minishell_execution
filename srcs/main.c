/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/30 14:59:15 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	sh;

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

// Example: cat file.txt | grep foo > out.txt

t_error	ft_init_minishell(char **ev)
{
	sh.envp = ev;
	sh.exit_code = SUCCESS;
	sh.shell = "sh";
	return (SUCCESS_ERROR);
}

// void	ft_get_tokens(t_token **list)
// {
// 	t_token	*t1;
// 	t_token	*t2;
// 	t_token	*t3;
// 	t_token	*t4;
// 	t_token	*t5;
// 	t_token	*t6;
// 	t_token	*t7;

// 	t1 = ft_new_token("cat", TOKEN_WORD);
// 	t2 = ft_new_token("file.txt", TOKEN_WORD);
// 	t3 = ft_new_token("|", TOKEN_PIPE);
// 	t4 = ft_new_token("grep", TOKEN_WORD);
// 	t5 = ft_new_token("foo", TOKEN_WORD);
// 	t6 = ft_new_token(">", TOKEN_REDIR_OUT);
// 	t7 = ft_new_token("out.txt", TOKEN_WORD);
	
// 	ft_add_token(list, t1);
// 	ft_add_token(list, t2);
// 	ft_add_token(list, t3);
// 	ft_add_token(list, t4);
// 	ft_add_token(list, t5);
// 	ft_add_token(list, t6);
// 	ft_add_token(list, t7);
// }


int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	(void)ev;
	t_token *list;
	t_ast *root;

	list = NULL;
	// char *rl;
	// rl = readline("Prompt > ");
	// printf("%s\n", rl);
	// ft_init_minishell(ev);
	// ft_get_tokens(&list);
	// ft_print_tokens(list);
	// ft_clear_tokens(&list);
	// root = ft_get_long_ast();
	// root = ft_get_short_ast();
	// root = ft_get_ast1();
	// root = ft_get_ast2();
	root = ft_get_ast3();
	// root = ft_get_ast4();
	ft_print_ast(root, 0);
	ft_executor(root, root, ev);
	ft_destroy_ast(root);
	return (EXIT_SUCCESS);
	// exit(EXIT_SUCCESS);
}
