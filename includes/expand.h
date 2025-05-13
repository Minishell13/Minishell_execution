/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:31:02 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/13 18:15:58 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
#define EXPAND_H

# include "typedef.h"

// Expand Var
t_quote	is_quote(char c);
char	*extract_var_value(char *arg, int *i);
char	*process_arg(char *arg);
void	expand_node_args(t_ast *ast);
void	expand_tree(t_ast *node);

// Expand Wildcard

#endif
