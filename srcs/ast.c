/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:13:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/29 15:12:02 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create a new AST node: initializes all fields and sets up self-linked next/prev
t_ast *ft_new_ast_node(t_gram type)
{
	t_ast *node = malloc(sizeof(t_ast));
	if (!node)
		return NULL;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	// initialize union
	node->data.args = NULL;
	node->data.redir.file = NULL;
	node->data.redir.type = UNKNOWN;
	node->data.redir.limiter = NULL;
	return node;
}

// Helper: build a NULL-terminated args array from strings
char	**ft_create_args(int count, ...)
{
	if (count < 0) {
		errno = EINVAL;
		return NULL;
	}

	// Allocate array of (count + 1) pointers
	char **args = malloc((count + 1) * sizeof *args);
	if (!args) {
		return NULL;  // malloc sets errno on failure
	}

	va_list ap;
	va_start(ap, count);
	for (int i = 0; i < count; i++) {
		const char *s = va_arg(ap, const char *);
		if (s) {
			args[i] = strdup(s);
			if (!args[i]) {
				// strdup failed: clean up and report
				for (int j = 0; j < i; j++)
					free(args[j]);
				free(args);
				va_end(ap);
				return NULL;
			}
		} else {
			args[i] = NULL;
		}
	}
	va_end(ap);

	args[count] = NULL;
	return args;
}

// t_ast *ft_new_ast_node(t_gram type)
// {
//     t_ast *node = malloc(sizeof(t_ast));
//     if (!node) return NULL;
//     node->type = type;
//     node->data.args = NULL;
//     node->data.redir.file = NULL;
//     node->data.redir.append = 0;
//     node->left = NULL;
//     node->right = NULL;
//     return node;
// }

// char	**ft_create_args(t_token *tokens, int count)
// {
//     char **args = malloc(sizeof(char *) * (count + 1));
//     for (int i = 0; i < count; i++) {
//         args[i] = strdup(tokens->value);
//         tokens = tokens->next;
//     }
//     args[count] = NULL;
//     return args;
// }

// void ft_clear_ast(t_ast *a)
// {
//     if (!a) return;
//     ft_clear_ast(a->left);
//     ft_clear_ast(a->right);
//     if (a->type == GRAM_SIMPLE_COMMAND && a->data.args) {
//         for (char **p = a->data.args; *p; ++p) free(*p);
//         free(a->data.args);
//     }
//     if (a->type == GRAM_IO_REDIRECT && a->data.redir.file)
//         free(a->data.redir.file);
//     free(a);
// }
