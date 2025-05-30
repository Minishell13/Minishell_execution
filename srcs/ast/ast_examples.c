/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_examples.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:49:24 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/30 16:37:12 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cat << A > "''\"$f1\"''"
t_ast	*ft_get_ast0(void)
{
	
	// heredoc << A
	t_ast *hd = ast_new_node(GRAM_IO_REDIRECT);
	generate_tmpfile(&hd->data.redir);
	hd->data.redir.type    = GRAM_HEREDOC;
	hd->data.redir.limiter = strdup("A");
	
	// then > a
	t_ast *ro = ast_new_node(GRAM_IO_REDIRECT);
	ro->data.redir.type = GRAM_REDIR_OUT;
	ro->data.redir.file = strdup("./temp/out");
	
	// attach in encounter order
	t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
	cmd->data.args = ast_create_args("cat");
	ast_add_child(cmd, hd);
	ast_add_child(cmd, ro);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, cmd);
	return root;
}

// echo X && echo Y && echo Z && echo W
t_ast	*ft_get_ast1(void)
{
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);

	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->data.args = ast_create_args("echo '\"$PATH\"'");

	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->data.args = ast_create_args("echo \"\"$SHELL\"\"");

	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->data.args = ast_create_args("echo \"\"$PWD\"\"");

	t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c4->data.args = ast_create_args("echo '\"$CC\"'");

	
	t_ast *and1 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and1, c1);
	ast_add_child(and1, c2);
	
	t_ast *and2 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and2, and1);
	ast_add_child(and2, c3);
	
	
	t_ast *and3 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and3, and2);
	ast_add_child(and3, c4);


	ast_add_child(root, and3);
	return root;
}

// cat | ls > out
t_ast	*ft_get_ast2(void)
{
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);

	t_ast *redir = ast_new_node(GRAM_IO_REDIRECT);
	redir->data.redir.type = GRAM_REDIR_OUT;
	redir->data.redir.file = strdup("./temp/out");
	
	t_ast *ls = ast_new_node(GRAM_SIMPLE_COMMAND);
	ls->data.args = ast_create_args("ls");
	ast_add_child(ls, redir);
	
	t_ast *cat = ast_new_node(GRAM_SIMPLE_COMMAND);
	cat->data.args = ast_create_args("cat");

	t_ast *pipe = ast_new_node(GRAM_PIPELINE);
	ast_add_child(pipe, cat);
	ast_add_child(pipe, ls);

	ast_add_child(root, pipe);
	return root;
}

// echo 1 && echo 2 && echo 3 && echo 4
t_ast	*ft_get_ast3(void)
{
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);

	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->data.args = ast_create_args("echo 1");

	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->data.args = ast_create_args("echo 2");

	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->data.args = ast_create_args("echo 3");

	t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c4->data.args = ast_create_args("echo 4");

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

// ls | grep "M" | wc -l | cat -e > ./temp/out && echo OK || echo "ERROR"
t_ast	*ft_get_ast4(void)
{
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->data.args = ast_create_args("ls");
	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->data.args = ast_create_args("cat -n");
	t_ast *p1 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p1, c1);
	ast_add_child(p1, c2);
	
	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->data.args = ast_create_args("grep M");
	t_ast *p2 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p2, p1);
	ast_add_child(p2, c3);

	t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c4->data.args = ast_create_args("wc -l");
	t_ast *p3 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p3, p2);
	ast_add_child(p3, c4);
	
	t_ast *r1 = ast_new_node(GRAM_IO_REDIRECT);
	r1->data.redir.type = GRAM_REDIR_OUT;
	r1->data.redir.file = ft_strdup("./temp/out");
	t_ast *c5 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c5->data.args = ast_create_args("cat -e");
	ast_add_child(c5, r1);
	
	t_ast *p4 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p4, p3);
	ast_add_child(p4, c5);
	
	t_ast *c6 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c6->data.args = ast_create_args("echo OK");
	
	t_ast *and_2 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and_2, p4);
	ast_add_child(and_2, c6);
	
	t_ast *c7 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c7->data.args = ast_create_args("echo ERROR");
	
	t_ast *or = ast_new_node(GRAM_OPERATOR_OR);
	ast_add_child(or, and_2);
	ast_add_child(or, c7);
	
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	// ast_add_child(root, p4);
	ast_add_child(root, or);
	return root;
}

// echo "echo", "$USER", "$SHELL", "'$PWD'"
t_ast	*ft_get_ast5(void)
{
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);

	t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
	cmd->data.args = ast_create_args("echo echo $USER $SHELL '$PWD'");

	ast_add_child(root, cmd);
	return root;
}

t_ast	*ft_get_ast6(void)
{
	t_ast *r1 = ast_new_node(GRAM_IO_REDIRECT);
	r1->data.redir.type = GRAM_REDIR_OUT;
	r1->data.redir.file = strdup("./temp/a");

	t_ast *r2 = ast_new_node(GRAM_IO_REDIRECT);
	r2->data.redir.type = GRAM_REDIR_OUT;
	r2->data.redir.file = strdup("./temp/b");

	t_ast *r3 = ast_new_node(GRAM_IO_REDIRECT);
	r3->data.redir.type = GRAM_REDIR_OUT;
	r3->data.redir.file = strdup("./temp/c");

	t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
	cmd->data.args = ast_create_args("cat Makefilee");
	ast_add_child(cmd, r1);
	ast_add_child(cmd, r2);
	ast_add_child(cmd, r3);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, cmd);
	return root;
}

// cat Makefile > ./temp/out << A
//! The heredoc run first
t_ast	*ft_get_ast7(void)
{	
	
	// > ./temp/out
	t_ast *ro = ast_new_node(GRAM_IO_REDIRECT);
	ro->data.redir.type = GRAM_REDIR_OUT;
	ro->data.redir.file = strdup("./temp/out");
	
	// << A
	t_ast *hd = ast_new_node(GRAM_IO_REDIRECT);
	generate_tmpfile(&hd->data.redir);
	hd->data.redir.type    = GRAM_HEREDOC;
	hd->data.redir.limiter = strdup("A");
	
	t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
	cmd->data.args = ast_create_args("cat Makefile");
	ast_add_child(cmd, ro);
	ast_add_child(cmd, hd);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, cmd);
	return root;
}

//! (ls | cat -n) | (wc -l | cat -e)
t_ast	*ft_get_ast8(void)
{	
	t_ast *r1 = ast_new_node(GRAM_IO_REDIRECT);
	r1->data.redir.type = GRAM_REDIR_OUT;
	r1->data.redir.file = strdup("./temp/a");

	t_ast *r2 = ast_new_node(GRAM_IO_REDIRECT);
	r2->data.redir.type = GRAM_REDIR_OUT;
	r2->data.redir.file = strdup("./temp/b");

	t_ast *r3 = ast_new_node(GRAM_IO_REDIRECT);
	r3->data.redir.type = GRAM_REDIR_OUT;
	r3->data.redir.file = strdup("./temp/c");

	// << A
	t_ast *h1 = ast_new_node(GRAM_IO_REDIRECT);
	generate_tmpfile(&h1->data.redir);
	h1->data.redir.type    = GRAM_HEREDOC;
	h1->data.redir.limiter = strdup("A");

	// << B
	t_ast *h2 = ast_new_node(GRAM_IO_REDIRECT);
	generate_tmpfile(&h2->data.redir);
	h2->data.redir.type    = GRAM_HEREDOC;
	h2->data.redir.limiter = strdup("B");

	// << C
	t_ast *h3 = ast_new_node(GRAM_IO_REDIRECT);
	generate_tmpfile(&h3->data.redir);
	h3->data.redir.type    = GRAM_HEREDOC;
	h3->data.redir.limiter = strdup("C");

	// t_ast *rr3 = ast_new_node(GRAM_IO_REDIRECT);
	// rr3->data.redir.type = GRAM_REDIR_IN;
	// rr3->data.redir.file = strdup("Todo.md");

	t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
	cmd->data.args = ast_create_args("cat Makefile");
	ast_add_child(cmd, h1);
	ast_add_child(cmd, r1);
	ast_add_child(cmd, h2);
	ast_add_child(cmd, r2);
	ast_add_child(cmd, h3);
	// ast_add_child(cmd, rr3);
	ast_add_child(cmd, r3);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, cmd);
	return root;
}

t_ast	*ft_get_ast9(void)
{
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->data.args = ast_create_args("/bin/ls");
	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->data.args = ast_create_args("cat -n");
	t_ast *p1 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p1, c1);
	ast_add_child(p1, c2);

	t_ast *s1 = ast_new_node(GRAM_SUBSHELL);
	ast_add_child(s1, p1);
	
	
	
	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->data.args = ast_create_args("wc -l");
	t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c4->data.args = ast_create_args("cat -e");
	t_ast *p2 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p2, c3);
	ast_add_child(p2, c4);
	
	t_ast *s2 = ast_new_node(GRAM_SUBSHELL);
	ast_add_child(s2, p2);


	
	t_ast *p3 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p3, s1);
	ast_add_child(p3, s2);

	t_ast *c5 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c5->data.args = ast_create_args("echo ERROR: $?");
	
	t_ast *or = ast_new_node(GRAM_OPERATOR_OR);
	ast_add_child(or, p3);
	ast_add_child(or, c5);
	
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, or);
	return root;
}

// cat | cat | wc -l | cat -e
t_ast	*ft_get_ast10(void)
{
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->data.args = ast_create_args("cat");
	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->data.args = ast_create_args("cat");
	t_ast *p1 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p1, c1);
	ast_add_child(p1, c2);

	
	
	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->data.args = ast_create_args("wc -l");
	t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c4->data.args = ast_create_args("cat -e");
	t_ast *p2 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p2, c3);
	ast_add_child(p2, c4);

	t_ast *p3 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p3, p1);
	ast_add_child(p3, p2);


	 t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, p3);
	return root;
}

t_ast	*ft_get_ast11(void)
{
	// attach in encounter order
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	//? Option: -n , and args as literal text
	c1->data.args = ast_create_args("exit gdf");
	//? No optoins allowed
	// c1->data.args = ast_create_args("echo -nn -n gg --");
	// c1->data.args = ast_create_args("export j=jj");
	// c1->data.args = ast_create_args("env -");
	// c1->data.args = ast_create_args("pwd -v");
	// c1->data.args = ast_create_args("unset -- n jyj");
	// c1->data.args = ast_create_args("unset @hrthrth");

	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->data.args = ast_create_args("echo code: $?");

	t_ast *and1 = ast_new_node(GRAM_OPERATOR_OR);
	ast_add_child(and1, c1);
	ast_add_child(and1, c2);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, and1);
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
		ft_get_ast5,
		ft_get_ast6,
		ft_get_ast7,
		ft_get_ast8,
		ft_get_ast9,
		ft_get_ast10,
		ft_get_ast11,
	};
	int max = sizeof(examples) / sizeof(examples[0]);
	if (n < 0 || n >= max)
	{
		ft_putstr_fd("Error on get_ast_example\n", STDERR_FILENO);	
		return (NULL);
	}
	return (examples[n]());
}
