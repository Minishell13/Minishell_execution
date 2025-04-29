/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/29 15:42:54 by abnsila          ###   ########.fr       */
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

//? Example: cat file.txt | grep foo > out.txt
t_ast	*ft_get_short_ast(void)
{
	// Simple command: cat file.txt
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(2, "cat", "file.txt");

	// Simple command: grep foo
	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd2->data.args = ft_create_args(2, "grep", "foo");

	// I/O redirect: > out.txt
	t_ast *redir = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir->data.redir.file = strdup("out.txt");
	redir->data.redir.type = GRAM_REDIR_OUT;
	redir->left = cmd2;

	// Pipeline: cmd1 | redir(cmd2)
	t_ast *pipe = ft_new_ast_node(GRAM_PIPELINE);
	pipe->left = cmd1;
	pipe->right = redir;

	// Complete command wrapper
	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = pipe;
	return root;
}

//? Example: (head -n1 && head -n2 | cat -e || ls) < infile | cat -n && echo hello > outfile
t_ast	*ft_get_long_ast(void)
{
	//* ------------- (head -n1 && head -n2 | cat -e || ls) -------------
	// Simple command: head -n1
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(2, "head", "-n1");

	// Simple command: head -n2
	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd2->data.args = ft_create_args(2, "head", "-n2");
	// Simple command: cat -e
	t_ast *cmd3 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd3->data.args = ft_create_args(2, "cat", "-e");
	// Pipeline: cmd1 | cmd2
	t_ast *pipe1 = ft_new_ast_node(GRAM_PIPELINE);
	pipe1->left = cmd2;
	pipe1->right = cmd3;

	// Simple command: ls
	t_ast *cmd4 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd4->data.args = ft_create_args(1, "ls");

	// AND: cmd1 | pipe1
	t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and1->left = cmd1;
	and1->right = pipe1;

	// OR: and1 || cmd4
	t_ast *or1 = ft_new_ast_node(GRAM_OPERATOR_OR);
	or1->left = and1;
	or1->right = cmd4;

	t_ast *subshell1 = ft_new_ast_node(GRAM_SUBSHELL);
	subshell1->left = or1;
	subshell1->right = NULL;

	//* ------------- subshell1 < infile -------------
	// I/O redirect: < infile
	t_ast *redir1 = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir1->data.redir.file = strdup("infile");
	redir1->data.redir.type = GRAM_REDIR_IN;
	redir1->left = subshell1;

	//* ------------- redir1 | cat -n -------------
	// Simple command: cat -e
	t_ast *cmd5 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd5->data.args = ft_create_args(2, "cat", "-n");
	// Pipeline: redir1 | cmd5
	t_ast *pipe2 = ft_new_ast_node(GRAM_PIPELINE);
	pipe2->left = redir1;
	pipe2->right = cmd5;

	//* ------------- echo hello > outfile -------------
	// Simple command: echo hello
	t_ast *cmd6 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd6->data.args = ft_create_args(2, "echo", "hello");
	// I/O redirect: > outfile
	t_ast *redir2 = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir2->data.redir.file = strdup("outfile");
	redir1->data.redir.type = GRAM_REDIR_OUT;
	redir2->left = cmd6;

	//* ------------- pipe2 && redir2 -------------
	// AND: pipe2 && redir2
	t_ast *and2 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and2->left = pipe2;
	and2->right = redir2;

	// Complete command wrapper
	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = and2;
	return root;
}



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
	root = ft_get_short_ast();
	ft_print_ast(root, 0);
	ft_executor(root->left, ev);
	ft_destroy_ast(root);
	return (EXIT_SUCCESS);
	// exit(EXIT_SUCCESS);
}
