/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/27 13:02:36 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_helper(t_ast *root, t_ast *cmd, char **envp)
{
	char	*path;

	path = get_path(cmd->data.args[0], envp);
	execve(path, cmd->data.args, envp);
	put_error(cmd->data.args[0]);
	get_error(path);
	free(path);
	clear_sh(root);
	exit(sh.exit_code);
}

void	heredoc_first(t_ast *root, t_ast *node, char **envp, int heredoc_total)
{
	t_ast	*c;
	int		heredoc_index;
	int		backup_fd;

	c = node->child;
	heredoc_index = 1;
	while (c)
	{
		if (c->data.redir.type == GRAM_HEREDOC)
		{
			//! Restore prev heredoc
			if (heredoc_index < heredoc_total)
			{
				backup_fd = dup(STDIN_FILENO);
				execute_redirection(root, c, envp);
				dup2(backup_fd, STDIN_FILENO);
				close(backup_fd);
			}
			//! Do not restore last heredoc
			else
				execute_redirection(root, c, envp);
			heredoc_index++;
		}
		c = c->sibling;
	}
}

void	exec_redir(t_ast *root, t_ast *node, char **envp)
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
	heredoc_first(root, node, envp, heredoc_total);
	// 2. Do all other redirs (saving last in/out)
	c = node->child;
	while (c)
	{
		if (c->data.redir.type != GRAM_HEREDOC)
		{
			execute_redirection(root, c, envp);
		}
		c = c->sibling;
	}
}


t_error	execute_simple_cmd(t_ast *root, t_ast *node, char **envp, t_bool no_fork)
{
	pid_t	pid;
	
	//! I need to confirm that [cmd node] can only contain [redir nodes list]
	exec_redir(root, node, envp);
	// Execute Builtins
	if (is_builtins(node))
	{
		return (exec_builtins(root, node));
	}
	// Execute Simple Command
	expand_cmd_node(node, process_mode_1);
	if (no_fork)
		execve_helper(root, node, envp);
	pid = fork();
	if (pid < 0)
		return FORK_ERROR;
	if (pid == 0)
	{
		execve_helper(root, node, envp);
	}
	int status;
	waitpid(pid, &status, 0);
	sh.exit_code = WEXITSTATUS(status);
	return (WEXITSTATUS(status));
}


// //* --------------------------------SIMPLE_COMMAND --------------------------------
// t_error	execute_simple_cmd(t_ast *root, t_ast *node, char **envp)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	*path;

// 	path = get_path(node->data.args[0], envp);
// 	if (!path)
// 		return (EXECVE_ERROR);

// 	pid = fork();
// 	if (pid < 0)
// 		return (FORK_ERROR);
// 	if (pid == 0)
// 	{
// 		execve(path, node->data.args, envp);

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
