/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:39:44 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/30 20:04:05 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

# include "typedef.h"

// Utils
t_bool	check_access(char *file, int permission);
char	*parse_path(char **all_path, char *cmd);
char	*get_path(char *cmd);

// Heredoc utils
void	generate_tmpfile(t_redir *redir);
void	fill_here_doc(t_redir *redir, int fd);
void	here_doc(t_redir *redir);
void	heredoc_first(t_ast *node, int heredoc_total);
// File utils
int		parse_infile(t_redir *redir, t_gram type);
int		parse_outfile(t_redir *redir, t_gram type);
void	redir(t_redir *r, t_gram type);
// Redirection Utils
void	expand_and_redir(t_ast *node);

// Cmd Helper
void	execve_helper(t_ast *root, t_ast *cmd);

// Signals For cmd
void	setup_cmd_signal(void);
void	signals_notif(pid_t pid, int *status);

// Execution
void	execute_simple_cmd(t_ast *root, t_ast *node, t_bool no_fork);
void    execute_pipeline(t_ast *root, t_ast *node);
void	execute_redirection(t_ast *node);
void	execute_subshell(t_ast *root, t_ast *node, t_bool no_fork);
void	execute_and_or(t_ast *root, t_ast *node);
void	executor(t_ast *root, t_ast *node);

#endif