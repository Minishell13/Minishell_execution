/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:39:44 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/05 14:51:15 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

# include "typedef.h"

// Utils
t_bool	ft_check_access(char *file, int permission);
char	*ft_parse_path(char **all_path, char *command);
char	*ft_get_path(char *command, char **envp);

// Redirection Utils
void	ft_generate_tmpfile(t_redir *redir);
void	ft_fill_here_doc(t_redir *redir, int fd);
void	ft_here_doc(t_redir *redir);
int		ft_parse_infile(t_redir *redir);
int		ft_parse_outfile(t_redir *redir);

// Execution
t_error	ft_execute_simple_cmd(t_ast *root, t_ast *node, char **envp);
t_error	ft_execute_pipe(t_ast *root, t_ast *node, char **envp);
t_error	ft_execute_redirection(t_ast *root, t_ast *node, char **envp);
t_error	ft_execute_subshell(t_ast *root, t_ast *node, char **envp);
t_error	ft_execute_and_or(t_ast *root, t_ast *node, char **envp);
t_error	ft_executor(t_ast *root, t_ast *node, char **envp);

#endif