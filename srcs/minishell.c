/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:15:07 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/28 14:15:23 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp) {
	(void)argc; (void)argv; (void)envp;
	char  *line;
	t_token *tokens;
	t_ast   *root;

	while (1) {
		line = readline("> ");
		if (!line) { printf("exit\n"); break; }
		if (*line) add_history(line);

		tokens = ft_lexer(line);
		if (!tokens) { free(line); continue; }

		root = ft_parser(&tokens);
		ft_clear_tokens(&tokens);

		if (root) {
			ft_print_ast(root, 0);
			ft_clear_ast(root);
		} else {
			fprintf(stderr, "parse error\n");
		}

		free(line);
	}
	exit(EXIT_SUCCESS);
}
