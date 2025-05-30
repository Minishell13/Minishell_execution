/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:18 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/30 19:18:12 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- PIPELINE --------------------------------
void	redirect_fds(t_ast *root, int fd)
{
	if (fd == STDOUT_FILENO)
	{	
		close(sh.pipefd[0]);
		if (dup2(sh.pipefd[1], STDOUT_FILENO) == -1)
		{
			clear_sh(root);
			close(sh.pipefd[1]);
			exit(EXIT_FAILURE);
		}
		close(sh.pipefd[1]);
	}
	else if (fd == STDIN_FILENO)
	{	
		close(sh.pipefd[1]);
		if (dup2(sh.pipefd[0], STDIN_FILENO) == -1)
		{
			clear_sh(root);
			close(sh.pipefd[0]);
			exit(EXIT_FAILURE);
		}
		close(sh.pipefd[0]);
	}
}

void run_one_stage(t_ast *root, t_ast *node)
{
	if (!node)
	{
		clear_sh(root);
		exit(EXIT_FAILURE);
	}
	switch (node->type)
	{
		case GRAM_SIMPLE_COMMAND:
			execute_simple_cmd(root, node, true);
			break;

		case GRAM_SUBSHELL:
			execute_subshell(root, node, true);
			clear_sh(root);
			exit(sh.exit_code);
			break;

		default:
			ft_putstr_fd("minishell: invalid pipeline stage\n", STDERR_FILENO);
			clear_sh(root);
			exit(EXIT_FAILURE);
	}
}

void	exec_left(t_ast *root, t_ast *left)
{
	sh.pids[0] = fork();
	if (sh.pids[0] < 0)
		return ;
	if (sh.pids[0] == 0)
	{
		redirect_fds(root, STDOUT_FILENO);
		if (left->type == GRAM_PIPELINE)
			execute_pipeline(root, left);
		else
			run_one_stage(root, left);
	}
}

void	exec_right(t_ast *root, t_ast *right)
{
	sh.pids[1] = fork();
	if (sh.pids[1] < 0)
		return ;
	if (sh.pids[1] == 0)
	{
		redirect_fds(root, STDIN_FILENO);
		if (right->type == GRAM_PIPELINE)
			execute_pipeline(root, right);
		else
			run_one_stage(root, right);
	}
}

void	execute_pipeline(t_ast *root, t_ast *node)
{
	int    status;

	if (!node->child || !node->child->sibling)
		return ;
	if (pipe(sh.pipefd) < 0)
		return ;
	exec_left(root, node->child);
	exec_right(root, node->child->sibling);
	//
	// 3) PARENT: clean up and wait
	//
	close(sh.pipefd[0]);
	close(sh.pipefd[1]);
	signals_notif(sh.pids[0], &status);
	signals_notif(sh.pids[1], &status);

	// return the exit status of the rightmost stage
	sh.exit_code = WEXITSTATUS(status);
}
