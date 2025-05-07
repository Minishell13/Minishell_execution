/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:59 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/08 00:06:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_and_with_heredoc_first(t_ast *root, t_ast *node, char **envp)
{
	t_ast *lhs = node->left;
	t_ast *rhs = node->right;

	// If pattern is: SIMPLE_COMMAND && HEREDOC
	if (lhs->type == GRAM_SIMPLE_COMMAND
	&& rhs && rhs->type == GRAM_IO_REDIRECT
	&& rhs->data.redir.type == GRAM_HEREDOC)
	{
		// 1) collect heredoc
		int fd = ft_parse_infile(&rhs->data.redir);
		if (fd >= 0) close(fd);

		// 2) then execute the left command
		return ft_executor(root, lhs, envp);
	}

	// Fallback to normal semantics
	return -1;
}

t_error	ft_execute_cmd_and(t_ast *root, char **envp)
{
	char	*line;
	int		i;
	t_bool	exit;

	exit = false;
	while (1)
	{
		i = 0;
		line = readline("cmdand> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		while (line[i])
		{
			if (!ft_isspace(line[i]))
			exit = true;
			i++;
		}
		if (exit)
			break ;
	}
	// TODO: The cmd can contain args, you must split it -> ft_split(line)
	t_ast *cmd_and = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd_and->data.args = ft_create_args(1, ft_strdup(line));
	free(line);
	return ft_executor(root, cmd_and, envp);
}

//* -------------------------------- AND_OR --------------------------------

t_error	ft_execute_and_or(t_ast *root, t_ast *node, char **envp)
{
	int left_status = ft_executor(root, node->left, envp);
	
	if (node->type == GRAM_OPERATOR_AND && node->right == NULL)
		return ft_execute_cmd_and(root, envp);

	// &&: right only if left succeeded
	if (node->type == GRAM_OPERATOR_AND && left_status == 0)
		return ft_executor(root, node->right, envp);
	// ||: right only if left failed
	if (node->type == GRAM_OPERATOR_OR && left_status != 0)
		return ft_executor(root, node->right, envp);
	return left_status;
}

