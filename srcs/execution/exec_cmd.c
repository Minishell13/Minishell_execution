/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/06 14:35:42 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* --------------------------------SIMPLE_COMMAND --------------------------------
t_error	ft_execute_simple_cmd(t_ast *root, t_ast *node, char **envp)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = ft_get_path(node->data.args[0], envp);
	if (!path)
		return (EXECVE_ERROR);

	pid = fork();
	if (pid < 0)
		return (FORK_ERROR);
	if (pid == 0)
	{
		execve(path, node->data.args, envp);

		// TODO: Maybe use a custom put error function instead perror
		// perror("sh");
		ft_put_error(path);
		free(path);
		ft_destroy_ast(root);
		if (errno == ENOENT) exit(NO_FILE_OR_DIR);
		if (errno == EACCES) exit(PERMISSION_DENIED);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	free(path);
	return (WEXITSTATUS(status) ? EXECVE_ERROR : SUCCESS);
}
