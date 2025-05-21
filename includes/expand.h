/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:31:02 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 15:30:59 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
#define EXPAND_H

# include "typedef.h"



// Expand Var
t_quote	is_quote(char c);
char	*extract_var_value(char *arg, int *i);
char	**process_arg(char *arg);
void	expand_node_args(t_ast *ast);
void	expand_tree(t_ast *node);



// Expand Wildcard

// Utils
int		arr_len(char **arr);
char	**copy_arr(char **new_arr, char **arr);
char	**dup_arr(char **arr);
char	**arr_append(char **arr, char *str);
char	**merge_arr(char **arr1, char **arr2);
//TODO: Must review this
char	**inner_merge_arr(char **arr1, char **arr2);
char	**last_item_ptr(char **arr);
void	print_arr(char **arr);
void	clear_arr(char **arr);


#endif
