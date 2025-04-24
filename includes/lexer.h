/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:09:24 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/24 16:26:01 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# include "typedef.h"

t_token	*ft_new_token(const char *value, t_token_type type);
void	ft_add_token(t_token **list, t_token *new_token);
void	ft_clear_tokens(t_token **list);
t_token	*ft_lexer(const char *input);

#endif
