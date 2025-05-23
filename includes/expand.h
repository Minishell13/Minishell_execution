/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:31:02 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 17:56:51 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
#define EXPAND_H

# include "typedef.h"

// Expand node
void	expand_cmd_node(t_ast *cmd);

// Expand Heredoc
t_bool	containe_quotes(char *s);
t_error remove_quotes(t_redir *r);
t_error	expand_herdoc(t_redir *r, char **line);

// Expand Redirection
void	expand_redir(t_ast *node);

// Expand Var
t_quote	is_quote(char c);
int	is_valid(char c);
char	*extract_var_value(char *arg, int *i);
t_bool	try_expand_dollar(char *arg, char **value, int *i);
void	default_mode(char *arg, char **value, int *i);
void	expand_mode(char *arg, char **value, int *i);
void	literal_mode(char *arg, char **value, int *i);
void	append_args(char ***arr, char **value, t_q_mode mode);
t_bool	process_mode(char *arg, t_q_mode mode, char ***arr, char **value, int *i);
char	**process_arg(char *arg);
void	expand_tree(t_ast *node, int indent);

char    **wildcard_expand_arr(char **in_arr);

#endif
