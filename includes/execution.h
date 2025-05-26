/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:39:44 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/26 18:13:02 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

# include "typedef.h"

// Utils
t_bool	check_access(char *file, int permission);
char	*parse_path(char **all_path, char *cmd);
char	*get_path(char *cmd, char **envp);

// Redirection Utils
void	generate_tmpfile(t_redir *redir);
void	fill_here_doc(t_redir *redir, int fd);
void	here_doc(t_redir *redir);
int		parse_infile(t_redir *redir);
int		parse_outfile(t_redir *redir);

// Helper
void	execve_helper(t_ast *root, t_ast *cmd, char **envp);

// Execution
t_error	execute_simple_cmd(t_ast *root, t_ast *node, char **envp, t_bool no_fork);
t_error execute_pipeline(t_ast *root, t_ast *node, char **envp);
t_error	execute_redirection(t_ast *root, t_ast *node, char **envp);
t_error	execute_subshell(t_ast *root, t_ast *node, char **envp);
t_error	execute_and_or(t_ast *root, t_ast *node, char **envp);
t_error	executor(t_ast *root, t_ast *node, char **envp);

#endif