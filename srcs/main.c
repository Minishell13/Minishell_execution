/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/24 19:06:23 by abnsila          ###   ########.fr       */
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

// t_error	ft_init_minishell(char **ev)
// {
// 	sh.envp = ev;
// 	sh.exit_code = SUCCESS;
// 	sh.shell = "sh";
// 	return (SUCCESS_ERROR);
// }

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

// // Example: manual AST creation for "cat file.txt | grep foo > out.txt"
// t_ast	*ft_get_ast(void)
// {
// 	// Simple command: cat file.txt
// 	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
// 	cmd1->data.argv = ft_create_argv(2, "cat", "file.txt");

// 	// Simple command: grep foo
// 	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
// 	cmd2->data.argv = ft_create_argv(2, "grep", "foo");

// 	// I/O redirect: > out.txt
// 	t_ast *redir = ft_new_ast_node(GRAM_IO_REDIRECT);
// 	redir->data.redir.file = strdup("out.txt");
// 	redir->data.redir.append = false;
// 	redir->left = cmd2;

// 	// Pipeline: cmd1 | redir(cmd2)
// 	t_ast *pipe = ft_new_ast_node(GRAM_PIPELINE);
// 	pipe->left = cmd1;
// 	pipe->right = redir;

// 	// Complete command wrapper
// 	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
// 	root->left = pipe;
// 	return root;
// }


// int	main(int ac, char **av, char **ev)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)ev;
// 	t_token *list;
// 	t_ast *root;

// 	list = NULL;
// 	// char *rl;
// 	// rl = readline("Prompt > ");
// 	// printf("%s\n", rl);
// 	ft_init_minishell(ev);
// 	// ft_get_tokens(&list);
// 	// ft_print_tokens(list);
// 	// ft_clear_tokens(&list);
// 	root = ft_get_ast();
// 	ft_print_ast(root, 0);
// 	return (EXIT_SUCCESS);
// 	// exit(EXIT_SUCCESS);
// }


int main(int argc, char **argv, char **envp) {
    (void)argc; (void)argv; (void)envp;
    char  *line;
    t_token *tokens;
    t_ast   *root;

    while (1) {
        line = readline("Prompt > ");
        if (!line) { printf("exit\n"); break; }
        if (*line) add_history(line);

        tokens = ft_lexer(line);
        if (!tokens) { free(line); continue; }

        root = ft_parser(&tokens);
        ft_clear_tokens(&tokens);

        if (root) {
            ft_print_ast(root, 0);
            ft_clear_ast(root);
        } else {
            fprintf(stderr, "parse error\n");
        }

        free(line);
    }
    return 0;
}
