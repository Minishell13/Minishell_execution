/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:45:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 15:56:21 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: You need first to know the exact struct of AST tree
// TODO: The representation each node with his type and args
// TODO: How to parcoure throw this three and get nodes in the correct order
// TODO: Create functions for execution (per node type)
// TODO: Focus on execution flow, (memory, fds, error) management
// TODO: The leaks is fixed, now go and make behavioure like shell
// TODO: ...

typedef struct	s_ast
{
	t_gram			type;	 // node kind
	struct s_ast	*left;	 // left child / first element
	struct s_ast	*right;	// right child / next element
	
	union
	{
		char		**args;       // for AST_CMD: NULL‑terminated argv
		t_redir		redir;
		
	}	data;
}				t_ast;

//! The tree structure must:
	// redirection go first
t_error ft_executor(t_ast *root, t_ast *node, char **envp)
{
	if (!node) return 0;

	switch (node->type)
	{
		case GRAM_COMPLETE_COMMAND:
			return ft_executor(root, node->left, envp);
			
		case GRAM_SIMPLE_COMMAND:
			return ft_execute_simple_cmd(root, node, envp);

		case GRAM_PIPELINE:
			return ft_execute_pipe(root, node, envp);

		case GRAM_IO_REDIRECT:
			return ft_execute_redirection(root, node, envp);

		case GRAM_SUBSHELL:
			return ft_execute_subshell(root, node, envp);

		case GRAM_OPERATOR_AND:
		case GRAM_OPERATOR_OR:
			return ft_execute_and_or(root, node, envp);

		default:
			return 0;
	}
	return (SUCCESS);
}
