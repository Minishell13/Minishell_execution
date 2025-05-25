/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_examples.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:49:24 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/25 18:53:13 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cat << A > "''\"$f1\"''"
t_ast	*ft_get_ast0(void)
{
	t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
	cmd->data.args = ast_create_args("cat");

	t_ast *redir_out = ast_new_node(GRAM_IO_REDIRECT);
	redir_out->data.redir.type = GRAM_REDIR_OUT;
	redir_out->data.redir.file = strdup("''\"$f1\"''");
	ast_add_child(redir_out, cmd);

	t_ast *heredoc = ast_new_node(GRAM_IO_REDIRECT);
	generate_tmpfile(&heredoc->data.redir);
	heredoc->data.redir.type = GRAM_HEREDOC;
	heredoc->data.redir.limiter = strdup("\"\"$a");
	ast_add_child(heredoc, redir_out);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, heredoc);
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

// ls | grep "M" | wc -l && echo OK || echo "ERROR"
t_ast	*ft_get_ast4(void)
{
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->data.args = ast_create_args("ls");
	
	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->data.args = ast_create_args("grep M");
	
	t_ast *p1 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p1, c1);
	ast_add_child(p1, c2);
	
	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->data.args = ast_create_args("wc -l");
	
	t_ast *p2 = ast_new_node(GRAM_PIPELINE);
	ast_add_child(p2, p1);
	ast_add_child(p2, c3);
	
	// t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
	// c4->data.args = ast_create_args("echo OK");
	
	// t_ast *and_2 = ast_new_node(GRAM_OPERATOR_AND);
	// ast_add_child(and_2, p2);
	// ast_add_child(and_2, c4);
	
	// t_ast *c5 = ast_new_node(GRAM_SIMPLE_COMMAND);
	// c5->data.args = ast_create_args("echo ERROR");
	
	// t_ast *or = ast_new_node(GRAM_OPERATOR_OR);
	// ast_add_child(or, and_2);
	// ast_add_child(or, c5);
	
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, p2);
	// ast_add_child(root, or);
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

t_ast	*ft_get_ast_example(int n)
{
	static t_ast *(*examples[])(void) = {
		ft_get_ast0,
		ft_get_ast1,
		ft_get_ast2,
		ft_get_ast3,
		ft_get_ast4,
		ft_get_ast5,
	};
	int max = sizeof(examples) / sizeof(examples[0]);
	if (n < 0 || n >= max)
	{
		ft_putstr_fd("Error on get_ast_example\n", STDERR_FILENO);	
		return (NULL);
	}
	return (examples[n]());
}
