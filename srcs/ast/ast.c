/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:13:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 17:54:35 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create a new AST node with no children and cleared union
t_ast	*ast_new_node(t_gram type)
{
    t_ast *node = ft_calloc(1, sizeof *node);
    if (!node) return NULL;
    node->type     = type;
    node->children = ft_calloc(1, sizeof(t_ast *)); // just the NULL terminator
    if (!node->children)
    {
        free(node);
        return NULL;
    }
    // initialize union fields
    node->data.args           = NULL;
    node->data.redir.type     = UNKNOWN;
    node->data.redir.file     = NULL;
    node->data.redir.limiter  = NULL;
    node->data.redir.expanded = false;
    return node;
}

// Append `child` to `parent->children[]`
int	ast_add_child(t_ast *parent, t_ast *child)
{
    int n = 0;
    while (parent->children[n]) n++;

    // resize to hold one more + NULL
    t_ast **tmp = realloc(parent->children,
                         sizeof(t_ast *) * (n + 2));
    if (!tmp) return -1;
    parent->children = tmp;
    parent->children[n]     = child;
    parent->children[n+1]   = NULL;
    return 0;
}

char	**ast_create_args(int count, ...)
{
    if (count < 0) return NULL;
    char **args = calloc(count + 1, sizeof *args);
    if (!args) return NULL;

    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; i++)
    {
        const char *s = va_arg(ap, const char *);
        args[i] = s ? strdup(s) : NULL;
        if (s && !args[i])
        {
            // cleanup on failure
            while (i-- > 0) free(args[i]);
            free(args);
            va_end(ap);
            return NULL;
        }
    }
    va_end(ap);
    args[count] = NULL;
    return args;
}

void ast_destroy(t_ast *node)
{
    if (!node) return;

    // free union
    if (node->type == GRAM_SIMPLE_COMMAND && node->data.args)
        clear_arr(node->data.args);
    else if (node->type == GRAM_IO_REDIRECT && node->data.redir.file)
    {
        if (node->type == GRAM_HEREDOC)
            unlink(node->data.redir.file);
        free(node->data.redir.file);
        if (node->data.redir.limiter)
            free(node->data.redir.limiter);
    }

    // destroy children
    for (int i = 0; node->children && node->children[i]; i++)
        ast_destroy(node->children[i]);

    free(node->children);
    free(node);
}
