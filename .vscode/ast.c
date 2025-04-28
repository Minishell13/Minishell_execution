/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:13:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/28 13:25:56 by abnsila          ###   ########.fr       */
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
	node->data.argv = NULL;
	node->data.redir.file = NULL;
	node->data.redir.append = false;
	return node;
}

// Helper: build a NULL-terminated argv array from strings
char	**ft_create_argv(int count, ...)
{
	if (count < 0) {
		errno = EINVAL;
		return NULL;
	}

	// Allocate array of (count + 1) pointers
	char **argv = malloc((count + 1) * sizeof *argv);
	if (!argv) {
		return NULL;  // malloc sets errno on failure
	}

	va_list ap;
	va_start(ap, count);
	for (int i = 0; i < count; i++) {
		const char *s = va_arg(ap, const char *);
		if (s) {
			argv[i] = strdup(s);
			if (!argv[i]) {
				// strdup failed: clean up and report
				for (int j = 0; j < i; j++)
					free(argv[j]);
				free(argv);
				va_end(ap);
				return NULL;
			}
		} else {
			argv[i] = NULL;
		}
	}
	va_end(ap);

	argv[count] = NULL;
	return argv;
}

// t_ast *ft_new_ast_node(t_gram type)
// {
//     t_ast *node = malloc(sizeof(t_ast));
//     if (!node) return NULL;
//     node->type = type;
//     node->data.argv = NULL;
//     node->data.redir.file = NULL;
//     node->data.redir.append = 0;
//     node->left = NULL;
//     node->right = NULL;
//     return node;
// }

// char	**ft_create_argv(t_token *tokens, int count)
// {
//     char **argv = malloc(sizeof(char *) * (count + 1));
//     for (int i = 0; i < count; i++) {
//         argv[i] = strdup(tokens->value);
//         tokens = tokens->next;
//     }
//     argv[count] = NULL;
//     return argv;
// }

// void ft_clear_ast(t_ast *a)
// {
//     if (!a) return;
//     ft_clear_ast(a->left);
//     ft_clear_ast(a->right);
//     if (a->type == GRAM_SIMPLE_COMMAND && a->data.argv) {
//         for (char **p = a->data.argv; *p; ++p) free(*p);
//         free(a->data.argv);
//     }
//     if (a->type == GRAM_IO_REDIRECT && a->data.redir.file)
//         free(a->data.redir.file);
//     free(a);
// }
