/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:49:26 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/24 18:24:43 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "typedef.h"

// static t_ast *parse_complete_command(t_token **);
t_ast	*parse_command_list     (t_token **toks);
t_ast	*parse_compound_command (t_token **toks);
t_ast	*parse_pipeline         (t_token **toks);
t_ast	*parse_command          (t_token **toks);
t_ast	*parse_subshell         (t_token **toks);
t_ast	*parse_simple_command   (t_token **toks);
t_ast	*ft_parser(t_token **toks);

t_ast	*ft_new_ast_node(t_gram type);
char	**ft_create_argv(t_token *tokens, int count);
void	ft_print_ast(const t_ast *node, int indent);
void	ft_clear_ast(t_ast *ast);

#endif
