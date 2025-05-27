/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:30:18 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/27 06:56:14 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//* -------------------------------- PIPELINE --------------------------------
t_error	redirect_fds(int fds[2], int fd)
{
	if (fd == STDOUT_FILENO)
	{	
		close(fds[0]);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (close(fds[1]), DUP2_ERROR);
		close(fds[1]);
	}
	else if (fd == STDIN_FILENO)
	{	
		close(fds[1]);
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (close(fds[0]), DUP2_ERROR);
		close(fds[0]);
	}
	return (SUCCESS);
}

void	clear_pipeline(pid_t stages[2], int fds[2], int *status)
{
	// parent
	close(fds[0]);
	close(fds[1]);
	waitpid(stages[0], status, 0);
	waitpid(stages[1], status, 0);
}

// t_error	exec_left(t_ast *root, t_ast *node, char **envp, int fds[2])
// {
// 	if (redirect_fds(fds, STDOUT_FILENO) != SUCCESS)
// 		return (DUP2_ERROR);
// 	if (node->child->type == GRAM_SIMPLE_COMMAND)
// 		execute_simple_cmd(root, node->child, envp, true);
// 	else
// 		executor(root, node->child, envp);
// 	return (SUCCESS);
// }

// t_error	exec_right(t_ast *root, t_ast *node, char **envp, int fds[2])
// {
// 	if (redirect_fds(fds, STDIN_FILENO) != SUCCESS)
// 		return (DUP2_ERROR);
// 	if (node->child->sibling->type == GRAM_SIMPLE_COMMAND)
// 		execute_simple_cmd(root, node->child->sibling, envp, true);
// 	else
// 		executor(root, node->child, envp);
// 	return (SUCCESS);
// }

// t_error execute_pipeline(t_ast *root, t_ast *node, char **envp)
// {
// 	int		fds[2];
// 	pid_t	stages[2];
// 	int		status;

// 	if (!node->child || !node->child->sibling)
// 		return PIPE_ERROR;
// 	if (pipe(fds) < 0)
// 		return PIPE_ERROR;
// 	// left child
// 	stages[0] = fork();
// 	if (stages[0] < 0)
// 		return FORK_ERROR;
// 	if (stages[0] == 0)
// 		if (exec_left(root, node, envp, fds) != SUCCESS)
// 			return (DUP2_ERROR);
// 	// right child
// 	stages[1] = fork();
// 	if (stages[1] < 0)
// 		return FORK_ERROR;
// 	if (stages[1] == 0)
// 		if (exec_right(root, node, envp, fds) != SUCCESS)
// 			return (DUP2_ERROR);
// 	clear_pipeline(stages, fds, &status);
// 	return SUCCESS;
// }








// t_error	exec_left(t_ast *root, t_ast *node, char **envp, int fds[2])
// {
// 	if (redirect_fds(fds, STDOUT_FILENO) != SUCCESS)
// 		return (DUP2_ERROR);
// 	execute_simple_cmd(root, node->child, envp, true);
// 	return (SUCCESS);
// }

// t_error	exec_right(t_ast *root, t_ast *node, char **envp, int fds[2])
// {
// 	if (redirect_fds(fds, STDIN_FILENO) != SUCCESS)
// 		return (DUP2_ERROR);
// 	execute_simple_cmd(root, node->child->sibling, envp, true);
// 	return (SUCCESS);
// }


// t_error execute_pipeline(t_ast *root, t_ast *node, char **envp)
// {
// 	int		fds[2];
// 	pid_t	stages[2];
// 	int		status;

// 	if (!node->child || !node->child->sibling)
// 		return PIPE_ERROR;

// 	if (pipe(fds) < 0)
// 		return PIPE_ERROR;
// 	if (node->child->type != GRAM_SIMPLE_COMMAND)
// 		executor(root, node->child, envp);
// 	else
// 	{
// 		// left child
// 		stages[0] = fork();
// 		if (stages[0] < 0)
// 			return FORK_ERROR;
// 		if (stages[0] == 0)
// 			if (exec_left(root, node, envp, fds) != SUCCESS)
// 			return (DUP2_ERROR);
// 	}

// 	if (node->child->sibling->type != GRAM_SIMPLE_COMMAND)
// 		executor(root, node->child->sibling, envp);
// 	else
// 	{
// 		// right child
// 		stages[1] = fork();
// 		if (stages[1] < 0)
// 			return FORK_ERROR;
// 		if (stages[1] == 0)
// 			if (exec_right(root, node, envp, fds) != SUCCESS)
// 				return (DUP2_ERROR);
// 	}

// 	// clear_pipeline(stages, fds, &status);
// 	close(fds[0]);
// 	close(fds[1]);
// 	waitpid(-1, &status, 0);
// 	// waitpid(stages[0], &status, 0);
// 	// waitpid(stages[1], &status, 0);
// 	return SUCCESS;
// }












// // This helper never returns: it wires up sh.pipe → stdin/stdout and execs one node.
// void run_one_stage(t_ast *root, t_ast *node, char **envp)
// {
// 	// 1) unwrap any top‐level PIPE or COMPLETE_COMMAND
// 	while (node &&
// 		  (node->type == GRAM_PIPELINE ||
// 		   node->type == GRAM_COMPLETE_COMMAND))
// 	{
// 		node = node->child;
// 	}
// 	if (!node)
// 		exit(EXIT_FAILURE);

// 	// 2) dup the global pipe ends into stdin/stdout
// 	//    assume sh.pipe[0] = read end, sh.pipe[1] = write end
// 	if (sh.pipe[1] != STDOUT_FILENO)
// 	{
// 		dup2(sh.pipe[1], STDOUT_FILENO);
// 		close(sh.pipe[1]);
// 	}
// 	if (sh.pipe[0] != STDIN_FILENO)
// 	{
// 		dup2(sh.pipe[0], STDIN_FILENO);
// 		close(sh.pipe[0]);
// 	}

// 	// 3) dispatch on the real node
// 	switch (node->type)
// 	{
// 		case GRAM_SIMPLE_COMMAND:
// 			expand_cmd_node(node, process_mode_1);    // your expansion
// 			execute_simple_cmd(root, node, envp, true);  
// 			break;

// 		case GRAM_SUBSHELL:
// 			execute_subshell(root, node, envp);
// 			break;

// 		default:
// 			write(2, "minishell: invalid pipeline stage\n", 34);
// 			exit(EXIT_FAILURE);
// 	}

// 	// If exec returns, something went wrong
// 	exit(EXIT_FAILURE);
// }


// t_error execute_pipeline(t_ast *root, t_ast *node, char **envp)
// {
// 	pid_t left, right;
// 	int   status;

// 	if (!node->child || !node->child->sibling)
// 		return PIPE_ERROR;

// 	// Create the global pipe:
// 	if (pipe(sh.pipe) < 0)
// 		return PIPE_ERROR;

// 	// Fork the left stage
// 	left = fork();
// 	if (left < 0) return FORK_ERROR;
// 	if (left == 0)
// 		run_one_stage(root, node->child, envp);

// 	// Fork the right stage
// 	right = fork();
// 	if (right < 0) return FORK_ERROR;
// 	if (right == 0)
// 		// the sibling (which may itself be another PIPE node):
// 		run_one_stage(root, node->child->sibling, envp);

// 	// Parent closes both ends and waits
// 	close(sh.pipe[0]);
// 	close(sh.pipe[1]);
// 	waitpid(left,  &status, 0);
// 	waitpid(right, &status, 0);

// 	// return the right‐hand exit code
// 	return WEXITSTATUS(status);
// }




// t_error	exec_left(t_ast *root, t_ast *node, char **envp, int fds[2], int pid)
// {

// 	pid = fork();
// 	if (pid == -1) {
// 		perror("fork");
// 		return FORK_ERROR;
// 	}

// 	if (pid == 0) {
// 		// Child process for the left command
// 		close(fds[0]); // Close unused read end
// 		dup2(fds[1], STDOUT_FILENO);
// 		close(fds[1]);

// 		execute_simple_cmd(root, node, envp, true);
// 		exit(EXIT_FAILURE); // Should not reach here
// 	}
// 	return (SUCCESS);
// }

// t_error	exec_right(t_ast *root, t_ast *node, char **envp, int fds[2], int pid)
// {

// 	pid = fork();
// 	if (pid == -1) {
// 		perror("fork");
// 		return FORK_ERROR;
// 	}

// 	if (pid == 0) {
// 		// Child process for the left command
// 		close(fds[1]); // Close unused read end
// 		dup2(fds[0], STDIN_FILENO);
// 		close(fds[0]);
		
// 		execute_simple_cmd(root, node, envp, true);
// 		exit(EXIT_FAILURE); // Should not reach here
// 	}
// 	return (SUCCESS);
// }

// t_error	execute_pipeline(t_ast *root, t_ast *node, char **envp)
// {
// 	int		fds[2];
// 	pid_t	pids[2];
// 	int		status;

// 	if (node->type != GRAM_PIPELINE)
// 		return (SUCCESS);
// 	else
// 		execute_pipeline(root, node->child, envp);
// 	printf("Deep\n");

// 	if (pipe(fds) == -1)
// 	{
// 		perror("pipe");
// 		return PIPE_ERROR;
// 	}

// 	exec_left(root, node->child, envp, fds, pids[0]);

// 	exec_right(root, node->child->sibling, envp, fds, pids[1]);

// 	// Parent process closes both ends and waits
// 	close(fds[0]);
// 	close(fds[1]);
// 	waitpid(pids[0], &status, 0);
// 	waitpid(pids[1], &status, 0);
// 	return (SUCCESS);
// }






t_error execute_pipeline_node(t_ast *root, t_ast *node, char **envp, t_bool is_last)
{
	if (node->child && node->child->type == GRAM_PIPELINE)
	{
		printf("Deep pipeline: %s\n",gram_name(node->child->type));
		execute_pipeline_node(root, node->child, envp, false);
	}

	if (!node->child || node->child->type != GRAM_PIPELINE)
	{
		//! First pipeline
		if (pipe(sh.pipefd) == -1)
		return (PIPE_ERROR);
		
		printf("First cmd 1 pipeline: %s, cmd: %s\n",gram_name(node->child->type), node->child->data.args[0]);
		sh.in = STDIN_FILENO;
		sh.out = sh.pipefd[1];
		execute_simple_cmd(root, node->child, envp, false);
		
		printf("First cmd 2 pipeline: %s, cmd: %s\n",gram_name(node->child->sibling->type), node->child->sibling->data.args[0]);
		sh.in = sh.pipefd[0];
		sh.out = sh.pipefd[1];
		execute_simple_cmd(root, node->child->sibling, envp, false);
		return SUCCESS;
	}

	if (is_last)
	{
		printf("Last cmd 2 pipeline: %s, cmd: %s\n",gram_name(node->child->sibling->type), node->child->sibling->data.args[0]);
		sh.in = sh.pipefd[0];
		sh.out = STDOUT_FILENO;
		execute_simple_cmd(root, node->child->sibling, envp, false);
		close(sh.in);
		close(sh.out);
	}
	else
	{
		//! Midlle pipeline
		printf("Middle cmd 2 pipeline: %s, cmd: %s\n",gram_name(node->child->sibling->type), node->child->sibling->data.args[0]);
		sh.in = sh.pipefd[0];
		sh.out = sh.pipefd[1];
		execute_simple_cmd(root, node->child->sibling, envp, false);
	}

	// Only the parent process continues
	return SUCCESS;
}


// t_error execute_pipeline(t_ast *root, t_ast *node, char **envp)
// {
// 	(void)root;
// 	int status;

// 	printf("Entry pipeline: %s\n",gram_name(node->type));
// 	t_error err = execute_pipeline_node(root, node, envp, true);
// 	if (err != SUCCESS)
// 		return err;
	
	

// 	// Wait for all children
// 	while (wait(&status) > 0)
// 		;

// 	return SUCCESS;
// }

















// ------------------------------------------------------------------
// run_one_stage(): unwraps any COMPLETE_COMMAND/PIPELINE layers, then
// wires up the inherited stdin/stdout and execs exactly one simple
// command or subshell.
// This function never returns—it's meant to be called in a forked child.
// ------------------------------------------------------------------
void run_one_stage(t_ast *root, t_ast *node, char **envp)
{
	if (!node)
	{
		clear_sh(root);
		exit(EXIT_FAILURE);
	}

	// 2) STDIN/STDOUT are already dup'ed by the parent; just close excess fds
	//    (we assume the parent has done dup2(pipefd[x], STDIN/STDOUT)).
	//    No need to close anything else here.

	// 3) Dispatch on the real leaf
	switch (node->type)
	{
		case GRAM_SIMPLE_COMMAND:
			execute_simple_cmd(root, node, envp, true);
			break;

		case GRAM_SUBSHELL:
			execute_subshell(root, node, envp);
			break;

		default:
			ft_putstr_fd("minishell: invalid pipeline stage\n", STDERR_FILENO);
			clear_sh(root);
			exit(EXIT_FAILURE);
	}

	// Should never reach here
	ast_destroy(root);
	clear_arr(sh.my_env);
	exit(EXIT_FAILURE);
}

t_error	exec_left(t_ast *root, t_ast *left, char **envp)
{
	sh.pids[0] = fork();
	if (sh.pids[0] < 0)
		return (FORK_ERROR);
	if (sh.pids[0] == 0)
	{
		close(sh.pipefd[0]);
		dup2(sh.pipefd[1], STDOUT_FILENO);
		close(sh.pipefd[1]);

		if (left->type == GRAM_PIPELINE)
			execute_pipeline(root, left, envp);
		else
			run_one_stage(root, left, envp);

		// Should never return
		clear_sh(root);
		exit(EXIT_FAILURE);
	}
	return (SUCCESS);
}

t_error	exec_right(t_ast *root, t_ast *right, char **envp)
{
	sh.pids[1] = fork();
	if (sh.pids[1] < 0)
		return (FORK_ERROR);
	if (sh.pids[1] == 0)
	{
		close(sh.pipefd[1]);
		dup2(sh.pipefd[0], STDIN_FILENO);
		close(sh.pipefd[0]);

		if (right->type == GRAM_PIPELINE)
			execute_pipeline(root, right, envp);
		else
			run_one_stage(root, right, envp);
		// Should never return
		clear_sh(root);
		exit(EXIT_FAILURE);
	}
	return (SUCCESS);
}

t_error execute_pipeline(t_ast *root, t_ast *node, char **envp)
{
	int    status;

	if (!node->child || !node->child->sibling)
		return (PIPE_ERROR);

	if (pipe(sh.pipefd) < 0)
		return (PIPE_ERROR);
	
	if (exec_left(root, node->child, envp) != SUCCESS)
	{		
		return (close(sh.pipefd[0]), close(sh.pipefd[1]), ERROR);
	}
	if (exec_right(root, node->child->sibling, envp) != SUCCESS)
	{		
		return (close(sh.pipefd[0]), close(sh.pipefd[1]), ERROR);
	}
	//
	// 3) PARENT: clean up and wait
	//
	close(sh.pipefd[0]);
	close(sh.pipefd[1]);
	waitpid(sh.pids[0],  &status, 0);
	sh.exit_code = WEXITSTATUS(status);
	waitpid(sh.pids[1], &status, 0);
	sh.exit_code = WEXITSTATUS(status);

	// return the exit status of the rightmost stage
	sh.exit_code = WEXITSTATUS(status);
	return (WEXITSTATUS(status));
}


