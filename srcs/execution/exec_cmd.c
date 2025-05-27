/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/27 17:49:43 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_helper(t_ast *root, t_ast *cmd)
{
	char	*path;

	path = get_path(cmd->data.args[0]);
	execve(path, cmd->data.args, sh.my_env);
	put_error(cmd->data.args[0]);
	get_error(path);
	free(path);
	clear_sh(root);
	exit(sh.exit_code);
}

void	call_redir(t_ast *node)
{
	t_ast 	*c;
	int		heredoc_total = 0;

	// 0. Count heredoc redirs
	c = node->child;
	heredoc_total = 0;
	while (c)
	{
		if (c->data.redir.type == GRAM_HEREDOC)
			heredoc_total++;
		c = c->sibling;
	}
	// 1. Do heredocs first
	if (heredoc_total > 0)
		heredoc_first(node, heredoc_total);
	// 2. Do all other redirs (saving last in/out)
	c = node->child;
	while (c)
	{
		if (c->data.redir.type != GRAM_HEREDOC)
			execute_redirection(c);
		c = c->sibling;
	}
}

void	execute_simple_cmd(t_ast *root, t_ast *node, t_bool no_fork)
{
	pid_t	pid;
	int		status;

	//! I need to confirm that [cmd node] can only contain [redir nodes list]
	call_redir(node);
	// Execute Builtins
	if (is_builtins(node))
	{
		exec_builtins(root, node);
		return ;
	}
	// Execute Simple Command
	expand_cmd_node(node, process_mode_1);
	if (no_fork)
	{
		// printf("Already Fork\n");
		execve_helper(root, node);
	}
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		execve_helper(root, node);
	waitpid(pid, &status, 0);
	sh.exit_code = WEXITSTATUS(status);
	clear_sh(root);
	exit(sh.exit_code);
}


// //* --------------------------------SIMPLE_COMMAND --------------------------------
// t_error	execute_simple_cmd(t_ast *root, t_ast *node)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	*path;

// 	path = get_path(node->data.args[0]);
// 	if (!path)
// 		return (EXECVE_ERROR);

// 	pid = fork();
// 	if (pid < 0)
// 		return (FORK_ERROR);
// 	if (pid == 0)
// 	{
// 		execve(path, node->data.args);

// 		// TODO: Maybe use a custom put error function instead perror
// 		// perror("sh");
// 		put_error(path);
// 		free(path);
// 		ast_destroy(root);
// 		if (errno == ENOENT) exit(NO_FILE_OR_DIR);
// 		if (errno == EACCES) exit(PERMISSION_DENIED);
// 		exit(EXIT_FAILURE);
// 	}
// 	waitpid(pid, &status, 0);
// 	free(path);
// 	return (WEXITSTATUS(status) ? EXECVE_ERROR : SUCCESS);
// }
