/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_examples.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:49:24 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/30 15:45:37 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//? Command: < infile cat | wc > outfile
// Builds: input redirection, pipeline, output redirection
t_ast *ft_get_ast1(void)
{
    // Simple command: ls -l
    t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd1->data.args = ft_create_args(1, "cat");

    // Simple command: wc -l
    t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd2->data.args = ft_create_args(1, "wc");

    // Pipeline: cmd1 | cmd2
    t_ast *pipe = ft_new_ast_node(GRAM_PIPELINE);
    pipe->left  = cmd1;
    pipe->right = cmd2;

    // Output redirection: > outfile
    t_ast *redir_out = ft_new_ast_node(GRAM_IO_REDIRECT);
    redir_out->data.redir.file   = strdup("outfile");
    redir_out->data.redir.type   = GRAM_REDIR_OUT;
    redir_out->left              = pipe;

    // Input redirection: < infile
    t_ast *redir_in = ft_new_ast_node(GRAM_IO_REDIRECT);
    redir_in->data.redir.file    = strdup("infile");
    redir_in->data.redir.type    = GRAM_REDIR_IN;
    redir_in->left               = redir_out;

    // Complete command wrapper
    t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
    root->left = redir_in;
    return root;
}

//? Command: make && make clean && clear
// Builds: chained && operators
t_ast *ft_get_ast2(void)
{
    t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd1->data.args = ft_create_args(1, "make");

    t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd2->data.args = ft_create_args(2, "make", "clean");

    t_ast *cmd3 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd3->data.args = ft_create_args(1, "clear");

    // First AND: make && make clean
    t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
    and1->left  = cmd1;
    and1->right = cmd2;

    // Second AND: (and1) && clear
    t_ast *and2 = ft_new_ast_node(GRAM_OPERATOR_AND);
    and2->left  = and1;
    and2->right = cmd3;

    t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
    root->left = and2;
    return root;
}

//? Command: << "END" grep "gg" | wc -l >> outfile
// Builds: here-doc, pipeline, append redirection
t_ast *ft_get_ast3(void)
{
    // Simple command: grep "gg"
    t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd1->data.args = ft_create_args(2, "grep", "gg");
	
    // Here-doc limiter
    t_ast *heredoc = ft_new_ast_node(GRAM_IO_REDIRECT);
    ft_generate_tmpfile(&(heredoc->data.redir));
    heredoc->data.redir.type = GRAM_HEREDOC;
    heredoc->data.redir.limiter = strdup("END");
    heredoc->left = cmd1;

    // Simple command: wc -l
    t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd2->data.args = ft_create_args(2, "wc", "-l");

    // Pipeline: heredoc(cmd1) | cmd2
    t_ast *pipe = ft_new_ast_node(GRAM_PIPELINE);
    pipe->left  = heredoc;
    pipe->right = cmd2;

    // Append redirection: >> outfile
    t_ast *redir_app = ft_new_ast_node(GRAM_IO_REDIRECT);
    redir_app->data.redir.file = strdup("outfile");
    redir_app->data.redir.type = GRAM_REDIR_APPEND;
    redir_app->left           = pipe;

    t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
    root->left = redir_app;
    return root;
}

//? Command: << "END" grep "gg" | wc -l && (ls -l | wc > out) >> outfile
// Builds: here-doc, pipeline, AND, subshell, redirections, append
t_ast *ft_get_ast4(void)
{
    // Here-doc limiter
    t_ast *heredoc = ft_new_ast_node(GRAM_IO_REDIRECT);
    heredoc->data.redir.file    = strdup("END");
    heredoc->data.redir.type    = GRAM_HEREDOC;
    heredoc->data.redir.limiter = strdup("END");

    // Simple command: grep "gg"
    t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd1->data.args = ft_create_args(2, "grep", "gg");
    heredoc->left = cmd1;

    // Simple command: wc -l
    t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd2->data.args = ft_create_args(2, "wc", "-l");

    // Pipeline left: heredoc(cmd1) | cmd2
    t_ast *pipe1 = ft_new_ast_node(GRAM_PIPELINE);
    pipe1->left  = heredoc;
    pipe1->right = cmd2;

    // Subshell: ls -l | wc > out
    t_ast *cmd3 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd3->data.args = ft_create_args(2, "ls", "-l");
    t_ast *cmd4 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd4->data.args = ft_create_args(1, "wc");
    t_ast *pipe2 = ft_new_ast_node(GRAM_PIPELINE);
    pipe2->left  = cmd3;
    pipe2->right = cmd4;
    t_ast *redir_sub = ft_new_ast_node(GRAM_IO_REDIRECT);
    redir_sub->data.redir.file = strdup("out");
    redir_sub->data.redir.type = GRAM_REDIR_OUT;
    redir_sub->left = pipe2;
    t_ast *subshell = ft_new_ast_node(GRAM_SUBSHELL);
    subshell->left = redir_sub;

    // AND: pipe1 && subshell
    t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
    and1->left  = pipe1;
    and1->right = subshell;

    // Append redirection: >> outfile
    t_ast *redir_app = ft_new_ast_node(GRAM_IO_REDIRECT);
    redir_app->data.redir.file = strdup("outfile");
    redir_app->data.redir.type = GRAM_REDIR_APPEND;
    redir_app->left           = and1;

    t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
    root->left = redir_app;
    return root;
}

//? Command: cat file.txt | grep foo > out.txt
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

//? Command: (head -n1 && head -n2 | cat -e || ls) < infile | cat -n && echo hello > outfile
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
	redir2->data.redir.type = GRAM_REDIR_OUT;
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

