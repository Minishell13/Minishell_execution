/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_examples.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:49:24 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 17:04:43 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//? cat << A > "''\"$f1\"''"
t_ast *ft_get_ast0(void)
{
    // 1) Simple command: cat
    t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
    cmd->data.args = ast_create_args(1, "cat");

    // 2) Redirect out to literal "''\"$f1\"''"
    t_ast *redir_out = ast_new_node(GRAM_IO_REDIRECT);
    redir_out->data.redir.type = GRAM_REDIR_OUT;
    redir_out->data.redir.file = strdup("''\"$f1\"''");
    ast_add_child(redir_out, cmd);

    // 3) Here‐doc <<A on top of that
    t_ast *heredoc = ast_new_node(GRAM_IO_REDIRECT);
    ft_generate_tmpfile(&heredoc->data.redir);
    heredoc->data.redir.type    = GRAM_HEREDOC;
    heredoc->data.redir.limiter = strdup("A");
    ast_add_child(heredoc, redir_out);

    // 4) Wrap in COMPLETE_COMMAND
    t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
    ast_add_child(root, heredoc);
    return root;
}

//? echo X && echo Y && echo Z && echo W
t_ast *ft_get_ast1(void)
{
    t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
    
    // Build each echo… as a simple command node
    t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c1->data.args = ast_create_args(2, "echo", "'\"$PATH\"'");
    t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c2->data.args = ast_create_args(2, "echo", "\"\"$SHELL\"\"");
    t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c3->data.args = ast_create_args(2, "echo", "\"\"$PWD\"\"");
    t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c4->data.args = ast_create_args(2, "echo", "'\"$CC\"'");
    
    // Chain them all under one big AND node
    t_ast *all_and = ast_new_node(GRAM_OPERATOR_AND);
    ast_add_child(all_and, c1);
    ast_add_child(all_and, c2);
    ast_add_child(all_and, c3);
    ast_add_child(all_and, c4);
    
    ast_add_child(root, all_and);
    return root;
}

//? cat | ls > out
t_ast *ft_get_ast2(void)
{
    t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
    
    t_ast *cat = ast_new_node(GRAM_SIMPLE_COMMAND);
    cat->data.args = ast_create_args(1, "cat");
    
    t_ast *ls = ast_new_node(GRAM_SIMPLE_COMMAND);
    ls->data.args = ast_create_args(1, "ls");
    t_ast *redir = ast_new_node(GRAM_REDIR_OUT);
    redir->data.redir.type = GRAM_REDIR_OUT;
    redir->data.redir.file = strdup("./temp/out");
    ast_add_child(redir, ls);
    
    t_ast *pipe = ast_new_node(GRAM_PIPELINE);
    ast_add_child(pipe, cat);
    ast_add_child(pipe, redir);
    
    ast_add_child(root, pipe);
    return root;
}

//? echo 1 && echo 2 && echo 3 && echo 4
t_ast *ft_get_ast3(void)
{
    t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);

    // Build each echo… as a simple command node
    t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c1->data.args = ast_create_args(2, "echo", "1");
    t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c2->data.args = ast_create_args(2, "echo", "2");
    t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c3->data.args = ast_create_args(2, "echo", "3");
    t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c4->data.args = ast_create_args(2, "echo", "4");

    // Chain them all under one big AND node
    t_ast *and_3 = ast_new_node(GRAM_OPERATOR_AND);
    ast_add_child(and_3, c1);
    ast_add_child(and_3, c2);
    
    
    t_ast *and_2 = ast_new_node(GRAM_OPERATOR_AND);
    ast_add_child(and_2, and_3);
    ast_add_child(and_2, c3);
    
    t_ast *and_1 = ast_new_node(GRAM_OPERATOR_AND);
    ast_add_child(and_1, and_2);
    ast_add_child(and_1, c4);

    ast_add_child(root, and_1);
    return root;
}

//? ls | grep "M" | wc -l && echo OK || echo "ERROR"
t_ast *ft_get_ast4(void)
{
    t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
    
    // cmd | cmd
    t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c1->data.args = ast_create_args(2, "ls");
    t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c2->data.args = ast_create_args(2, "grep", "M");
    t_ast *p1 = ast_new_node(GRAM_PIPELINE);
    ast_add_child(p1, c1);
    ast_add_child(p1, c2);
    
    // pipe1 | cmd
    t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c3->data.args = ast_create_args(2, "wc", "-l");
    t_ast *p2 = ast_new_node(GRAM_PIPELINE);
    ast_add_child(p2, p1);
    ast_add_child(p2, c3);

    // pipe2 && cmd
    t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c4->data.args = ast_create_args(2, "echo", "OK");
    t_ast *and_2 = ast_new_node(GRAM_OPERATOR_AND);
    ast_add_child(and_2, p2);
    ast_add_child(and_2, c4);
    

    t_ast *c5 = ast_new_node(GRAM_SIMPLE_COMMAND);
    c5->data.args = ast_create_args(2, "echo", "ERROR");
    t_ast *or = ast_new_node(GRAM_OPERATOR_OR);
    ast_add_child(or, and_2);
    ast_add_child(or, c5);

    ast_add_child(root, or);
    return root;
}

t_ast	*ft_get_ast_example(int n)
{
	static t_ast *(*examples[])(void) = {
		ft_get_ast0,
		ft_get_ast1,
		ft_get_ast2,
		ft_get_ast3,
		ft_get_ast4,
	};
	int max = sizeof(examples) / sizeof(examples[0]);
	if (n < 0 || n >= max)
	{
		ft_putstr_fd("Error on get_ast_example\n", STDERR_FILENO);	
		return (NULL);
	}
	return (examples[n]());
}
