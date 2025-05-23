/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:14:45 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 16:41:11 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_node(t_token *node)
{
	ft_printf("|                        Token                        \n");
	ft_printf("| value:    %s                                              \n", node->value);
	// ft_printf("| prev: %p                                 \n", node->prev);
	// ft_printf("| next: %p                                 \n", node->next);
	ft_printf("|______________________________________________________\n");

}

void	ft_print_tokens(t_token *list)
{
	t_token	*current;

	if (!list)
	{
		ft_printf("|                   List is empty !                    |\n");
		ft_printf("|______________________________________________________|\n");
		return ;
	}
	current = list;
	do
	{
		ft_print_node(current);
		current = current->next;
	} while (current != list);
}

static char *gram_name(t_gram g)
{
	switch (g)
	{
	  case GRAM_COMPLETE_COMMAND: return "COMPLETE_COMMAND";
	  case GRAM_PIPELINE:         return "PIPELINE";
	  case GRAM_SIMPLE_COMMAND:   return "SIMPLE_COMMAND";
	  case GRAM_OPERATOR_AND:     return "OPERATOR_AND";
	  case GRAM_OPERATOR_OR:      return "OPERATOR_OR";
	  case GRAM_SUBSHELL:         return "SUBSHELL";
	  case GRAM_IO_REDIRECT:      return "IO_REDIRECT";
	  case GRAM_REDIR_IN:         return "REDIR_IN";
	  case GRAM_REDIR_OUT:        return "REDIR_OUT";
	  case GRAM_REDIR_APPEND:     return "REDIR_APPEND";
	  case GRAM_HEREDOC:          return "HEREDOC";
	  // … handle others …
	  default:                    return "UNKNOWN";
	}
}

void	ast_print(const t_ast *node, int indent)
{
	if (!node) return;
	for (int i = 0; i < indent; i++)	putchar(' ');
	printf("%s%s%s",BHCYN, gram_name(node->type), RESET);

	if (node->type == GRAM_SIMPLE_COMMAND && node->data.args)
	{
		printf("%s args: %s%s[", BHGRN, RESET, BHWHT);
		for (char **arg = node->data.args; *arg; arg++)
			printf(" \"%s\",", *arg);
		printf(" NULL ]%s", RESET);
	}
	else if (node->type == GRAM_IO_REDIRECT)
	{
		char *type = gram_name(node->data.redir.type);
		printf("%s redir:%s %s{file: \"%s\", type: %s, limiter: %s}%s",
				BHYEL, RESET, BHWHT,
				node->data.redir.file,
				type,
				node->data.redir.limiter, RESET);
	}
	putchar('\n');

	// Recurse into children
	for (int i = 0; node->children && node->children[i]; i++)
		ast_print(node->children[i], indent + 2);
}
