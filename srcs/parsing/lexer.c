/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:08:24 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/05 14:33:28 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

t_token *ft_new_token(const char *value, t_token_type type)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token) return NULL;
    token->value = strdup(value);
    token->type = type;
    token->next = NULL;
    return token;
}

void ft_add_token(t_token **list, t_token *new_token) {
    if (!*list) {
        *list = new_token;
    } else {
        t_token *temp = *list;
        while (temp->next)
            temp = temp->next;
        temp->next = new_token;
    }
}

t_token_type identify_token_type(const char *str) {
    if (strcmp(str, "|") == 0) return TOKEN_PIPE;
    if (strcmp(str, "<") == 0) return TOKEN_REDIR_IN;
    if (strcmp(str, ">") == 0) return TOKEN_REDIR_OUT;
    if (strcmp(str, ">>") == 0) return TOKEN_REDIR_APPEND;
    if (strcmp(str, "<<") == 0) return TOKEN_HEREDOC;
    if (strcmp(str, "&&") == 0) return TOKEN_AND;
    if (strcmp(str, "||") == 0) return TOKEN_OR;
    if (strcmp(str, "(") == 0) return TOKEN_OPARENTHES;
    if (strcmp(str, ")") == 0) return TOKEN_CPARENTHES;
    return TOKEN_WORD;
}

t_token	*ft_lexer(const char *input)
{
    t_token *tokens = NULL;
    const char *start = input;
    while (*start) {
        while (isspace(*start)) start++;
        if (*start == '\0') break;

        const char *end = start;
        if (strchr("|&<>()", *start)) {
            if ((start[0] == '>' && start[1] == '>') || (start[0] == '<' && start[1] == '<') ||
                (start[0] == '&' && start[1] == '&') || (start[0] == '|' && start[1] == '|')) {
                end = start + 2;
            } else {
                end = start + 1;
            }
        } else {
            while (*end && !isspace(*end) && !strchr("|&<>()", *end))
                end++;
        }

        size_t len = end - start;
        char *token_str = strndup(start, len);
        t_token_type type = identify_token_type(token_str);
        ft_add_token(&tokens, ft_new_token(token_str, type));
        free(token_str);
        start = end;
    }
    return tokens;
}

void	ft_clear_tokens(t_token **list)
{
    t_token *temp;
    while (*list) {
        temp = (*list)->next;
        free((*list)->value);
        free(*list);
        *list = temp;
    }
}
