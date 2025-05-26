/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/26 18:56:05 by abnsila          ###   ########.fr       */
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

t_error	execute_simple_cmd(t_ast *root, t_ast *node, char **envp, t_bool no_fork)
{
	pid_t	pid;

	executor(root, node->child, envp);
	if (is_builtins(node))
	{
		executor(root, node->child, envp);
		return (exec_builtins(root, node));
	}
	printf("NOOOOOOOOOOOOOOOO\n");
	expand_cmd_node(node, process_mode_1);
	if (no_fork)
		execve_helper(root, node, envp);
	pid = fork();
	if (pid < 0)
		return FORK_ERROR;
	if (pid == 0)
	{
		printf("%s Foked\n", node->data.args[0]);
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
