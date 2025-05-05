/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:14:45 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/05 14:33:02 by abnsila          ###   ########.fr       */
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

// Helper: get a human-readable name for each t_gram
static char *ft_gram_name(t_gram g)
{
	switch (g)
	{
		case GRAM_COMPLETE_COMMAND:    return "COMPLETE_COMMAND";
		case GRAM_COMMAND_LIST:        return "COMMAND_LIST";
		case GRAM_COMPOUND_COMMAND:    return "COMPOUND_COMMAND";
		case GRAM_PIPELINE:            return "PIPELINE";
		case GRAM_COMMAND:             return "COMMAND";
		case GRAM_SUBSHELL:            return "SUBSHELL";
		case GRAM_SIMPLE_COMMAND:      return "SIMPLE_COMMAND";
		case GRAM_REDIRECT_LIST:       return "REDIRECT_LIST";
		case GRAM_IO_REDIRECT:         return "IO_REDIRECT";
		case GRAM_WORD:                return "WORD";
		case GRAM_OPERATOR_AND:        return "OPERATOR_AND";
		case GRAM_OPERATOR_OR:         return "OPERATOR_OR";
		case GRAM_OPERATOR_PIPE:       return "OPERATOR_PIPE";
		case GRAM_REDIR_IN:            return "REDIR_IN";
		case GRAM_REDIR_OUT:           return "REDIR_OUT";
		case GRAM_REDIR_APPEND:        return "REDIR_APPEND";
		case GRAM_HEREDOC:             return "HEREDOC";
		case GRAM_FILENAME:            return "FILENAME";
		case GRAM_LINEBREAK:           return "LINEBREAK";
		default:                       return "UNKNOWN";
	}
}

// The main recursive printer
void	ft_print_ast(const t_ast *node, int indent)
{
	if (!node) return;

	// Print indent
	for (int i = 0; i < indent; i++) printf("  ");

	// Print node type
	printf("%s%s%s",BHCYN, ft_gram_name(node->type), RESET);

	// If it's a simple command, dump args[]
	if (node->type == GRAM_SIMPLE_COMMAND) {
		if (node->data.args) {
			printf("%s args: %s%s[", BHGRN, RESET, BHWHT);
			for (char **arg = node->data.args; *arg; arg++)
				printf(" \"%s\",", *arg);
			printf(" NULL ]%s", RESET);
		}
	}
	// If it's I/O redirection, show file and mode
	else if (node->type == GRAM_IO_REDIRECT) {
		// You might encode the operator as a string in the node; 
		// otherwise infer from node->type or value
		char *type = ft_gram_name(node->data.redir.type);
		printf("%s redir:%s %s{file: \"%s\", type: %s, limiter: %s}%s",
				BHYEL, RESET, BHWHT,
				node->data.redir.file,
				type,
				node->data.redir.limiter, RESET);
	}

	putchar('\n');
	
	// Recurse into left child
	if (node->left)
	ft_print_ast(node->left, indent + 2);
	
	// Then into right child
	if (node->right)
	ft_print_ast(node->right, indent + 2);
}

// void	ft_destroy_ast(t_ast *ast)
// {
// 	int	i = 0;
// 	if (!ast)
// 		return ;
// 	if (ast->type == GRAM_SIMPLE_COMMAND)
// 	{
// 		while (ast->data.args[i])
// 		{
// 			free(ast->data.args[i]);
// 			i++;
// 		}
// 		free(ast->data.args);
// 	}
// 	else if (ast->type == GRAM_IO_REDIRECT)
// 	{
// 		free(ast->data.redir.file);
// 	}
// 	ft_destroy_ast(ast->left);
// 	ft_destroy_ast(ast->right);
// 	free(ast);
// }

void	ft_destroy_ast(t_ast *ast)
{
	int	i;

	if (!ast)
		return ;
	i = 0;
	if (ast->type == GRAM_SIMPLE_COMMAND)
	{
		if (ast->data.args)
		{
			while (ast->data.args[i])
			{
				free(ast->data.args[i]);
				i++;
			}
			free(ast->data.args);
		}
	}
	else if (ast->type == GRAM_IO_REDIRECT)
	{
		if (ast->data.redir.file)
		{
			if (ast->data.redir.type == GRAM_HEREDOC)
				unlink(ast->data.redir.file);
			free(ast->data.redir.file);
		}
		if (ast->data.redir.limiter)
			free(ast->data.redir.limiter);
	}
	ft_destroy_ast(ast->left);
	ft_destroy_ast(ast->right);
	free(ast);
}
