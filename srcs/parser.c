/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:54:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/24 16:53:32 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // Helper: check current token type
// static t_token_type peek_type(t_token **toks)
// {
// 	return *toks ? (*toks)->type : TOKEN_EMPTY;
// }

// // Helper: advance past current token
// static void advance(t_token **toks)
// {
// 	if (*toks) *toks = (*toks)->next;
// }

// /**
//  * parse_compound_command:
//  *   Handles `&&` and `||` with left-associativity.
//  *   compound := pipeline ( ('&&' | '||') pipeline )*
//  */
// t_ast *parse_compound_command(t_token **tokens)
// {
//     t_ast *left = parse_pipeline(tokens);
//     if (!left) return NULL;

//     while (*tokens && ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
//     {
//         t_token_type op = (*tokens)->type;
//         *tokens = (*tokens)->next;  // consume && or ||

//         t_ast *right = parse_pipeline(tokens);
//         if (!right)
//         {
//             ft_clear_ast(left);
//             return NULL;
//         }

//         // Build the operator node
//         t_ast *op_node = ft_new_ast_node(
//             op == TOKEN_AND ? GRAM_OPERATOR_AND : GRAM_OPERATOR_OR);
//         op_node->left  = left;
//         op_node->right = right;
//         left = op_node;
//     }
//     return left;
// }


// /**
//  * parse_complete_command:
//  *   Entry point. Wraps a pipeline node under GRAM_COMPLETE_COMMAND.
//  */
// t_ast *parse_complete_command(t_token **tokens)
// {
// 	t_ast *pipe_node = parse_pipeline(tokens);
// 	if (!pipe_node) return NULL;

// 	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
// 	root->left = pipe_node;
// 	return root;
// }

// /**
//  * parse_pipeline:
//  *   Build left-associative pipeline tree:
//  *     cmd1 | cmd2 | cmd3  ⇒  PIPE( PIPE(cmd1, cmd2), cmd3 )
//  */
// t_ast *parse_pipeline(t_token **tokens)
// {
// 	// Parse first command (with redirects)
// 	t_ast *left = parse_simple_command(tokens);
// 	if (!left) return NULL;

// 	// While next token is '|', consume and parse RHS
// 	while (peek_type(tokens) == TOKEN_PIPE)
// {
// 		advance(tokens);  // skip '|'
// 		t_ast *right = parse_simple_command(tokens);
// 		if (!right)
// {   // syntax error
// 			ft_clear_ast(left);
// 			return NULL;
// 		}
// 		// Wrap into PIPE node
// 		t_ast *pipe_node = ft_new_ast_node(GRAM_PIPELINE);
// 		pipe_node->left  = left;
// 		pipe_node->right = right;
// 		left = pipe_node;
// 	}
// 	return left;
// }

// /**
//  * parse_simple_command:
//  *   Collect all WORD tokens into argv[], then
//  *   repeatedly wrap with I/O-redirect nodes for any redirections.
//  */
// t_ast *parse_simple_command(t_token **tokens)
// {
// 	// Require at least one WORD
// 	if (peek_type(tokens) != TOKEN_WORD)
// 		return NULL;

// 	// 1) Count consecutive WORD tokens
// 	int count = 0;
// 	t_token *tmp = *tokens;
// 	while (tmp && tmp->type == TOKEN_WORD)
// {
// 		count++;
// 		tmp = tmp->next;
// 	}

// 	// 2) Allocate argv array
// 	char **argv = malloc((count + 1) * sizeof *argv);
// 	for (int i = 0; i < count; i++)
// {
// 		argv[i] = strdup((*tokens)->value);
// 		advance(tokens);
// 	}
// 	argv[count] = NULL;

// 	// 3) Create the base SIMPLE_COMMAND node
// 	t_ast *cmd = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
// 	cmd->data.argv = argv;

// 	// 4) Handle any following redirections
// 	while (peek_type(tokens) == TOKEN_REDIR_IN
// 		|| peek_type(tokens) == TOKEN_REDIR_OUT
// 		|| peek_type(tokens) == TOKEN_REDIR_APPEND
// 		|| peek_type(tokens) == TOKEN_HEREDOC)
// 	{
// 		t_token_type op = peek_type(tokens);
// 		advance(tokens);  // skip the redirection token

// 		// Next must be a WORD (the filename)
// 		if (peek_type(tokens) != TOKEN_WORD)
//		{
// 			ft_clear_ast(cmd);
// 			return NULL;
// 		}
// 		char *fname = strdup((*tokens)->value);
// 		advance(tokens);

// 		// Create redirect node and wrap the existing cmd
// 		t_ast *redir = ft_new_ast_node(GRAM_IO_REDIRECT);
// 		redir->data.redir.file   = fname;
// 		redir->data.redir.append = (op == TOKEN_REDIR_APPEND);
// 		redir->left              = cmd;
// 		cmd = redir;
// 	}

// 	return cmd;
// }

// t_ast *ft_parser(t_token *tokens)
// {
//     t_token *t = tokens;
//     t_ast   *compound = parse_compound_command(&t);
//     if (!compound) return NULL;

//     t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
//     root->left = compound;
//     return root;
// }






#include "minishell.h"

// Advance and peek helpers
static	t_token_type	peek(t_token **t)
{
	return *t ? (*t)->type  :  TOKEN_EMPTY;
}
static void	eat (t_token **t)
{
	if (*t) *t = (*t)->next;
}

// Forward declarations


/* command_list : compound_command ( compound_command )* */
t_ast *parse_command_list(t_token **toks)
{
    t_ast *first = parse_compound_command(toks);
    if (!first) return NULL;
    t_ast *cur = first;
    // no explicit newline tokens here; could loop o n  TOKEN_EMPTY if present
    while ((peek(toks) ==  TOKEN_WORD    ) || // next command
           (peek(toks) ==  TOKEN_OPARENTHES)) // next subshell
    {
        t_ast *next = parse_compound_command(toks);
        if (!next) break;
        // chain via a COMMAND_LIST node
        t_ast *list = ft_new_ast_node(GRAM_COMMAND_LIST);
        list->left = cur;
        list->right = next;
        cur = list;
    }
    return cur;
}

/* compound_command : pipeline ( '&&' | '||' pipeline )* */
t_ast *parse_compound_command(t_token **toks)
{
    t_ast *left = parse_pipeline(toks);
    if (!left) return NULL;
    while (peek(toks) == TOKEN_AND || peek(toks) == TOKEN_OR)
	{
        t_token_type op = peek(toks);
        eat(toks);
        t_ast *right = parse_pipeline(toks);
        if (!right)
		{ ft_clear_ast(left); return NULL; }
        t_ast *node = ft_new_ast_node(
            op == TOKEN_AND ? GRAM_OPERATOR_AND : GRAM_OPERATOR_OR);
        node->left  = left;
        node->right = right;
        left = node;
    }
    return left;
}

/* pipeline : command ( '|' command )* */
t_ast *parse_pipeline(t_token **toks)
{
    t_ast *left = parse_command(toks);
    if (!left) return NULL;
    while (peek(toks) == TOKEN_PIPE)
	{
        eat(toks);
        t_ast *right = parse_command(toks);
        if (!right)
		{ ft_clear_ast(left); return NULL; }
        t_ast *node = ft_new_ast_node(GRAM_PIPELINE);
        node->left  = left;
        node->right = right;
        left = node;
    }
    return left;
}

/* command : subshell | simple_command */
t_ast *parse_command(t_token **toks)
{
    if (peek(toks) == TOKEN_OPARENTHES)
        return parse_subshell(toks);
    return parse_simple_command(toks);
}

/* subshell : '(' command_list ')' redirect_list* */
t_ast *parse_subshell(t_token **toks)
{
    eat(toks);  // '('
    t_ast *inner = parse_command_list(toks);
    if (!inner || peek(toks) != TOKEN_CPARENTHES)
        return NULL;
    eat(toks);  // ')'
    t_ast *node = ft_new_ast_node(GRAM_SUBSHELL);
    node->left = inner;
    // now allow trailing redirects
    while (peek(toks) == TOKEN_REDIR_IN || peek(toks) == TOKEN_REDIR_OUT ||
           peek(toks) == TOKEN_REDIR_APPEND || peek(toks) == TOKEN_HEREDOC)
    {
        t_ast *redir = parse_subshell(toks); // reuse or write parse_io_redirect
        if (!redir) break;
        // chain by wrapping
        redir->left = node;
        node = redir;
    }
    return node;
}

/* simple_command : (io_redirect | WORD)+ */
t_ast *parse_simple_command(t_token **toks)
{
    // We gather a list of WORDs and prefix redirects
    t_ast *cmd = NULL;
    char **argv = NULL;
    int    argc = 0;

    // Loop while we're seeing WORD or redirection token
    while (peek(toks) == TOKEN_WORD ||
           peek(toks) == TOKEN_REDIR_IN  ||
           peek(toks) == TOKEN_REDIR_OUT ||
           peek(toks) == TOKEN_REDIR_APPEND ||
           peek(toks) == TOKEN_HEREDOC)
    {
        if (peek(toks) == TOKEN_WORD)
		{
            // accumulate argv
            argv = realloc(argv, sizeof *argv * (argc+1));
            argv[argc++] = strdup((*toks)->value);
            eat(toks);
        } else {
            // io_redirect : op + WORD
            t_token_type op = peek(toks);
            eat(toks);
            if (peek(toks) != TOKEN_WORD)
			{ /* error */ break;}
            char *file = strdup((*toks)->value);
            eat(toks);

            t_ast *redir = ft_new_ast_node(GRAM_IO_REDIRECT);
            redir->data.redir.file = file;
            redir->data.redir.append     = (op == TOKEN_REDIR_APPEND);
            // if we already built a command, nest it
            if (cmd)
			{
                redir->left = cmd;
            }
            cmd = redir;
        }
    }

    // finalize the base simple command if we saw words
    if (argc>0)
	{
        t_ast *base = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
        base->data.argv = malloc(sizeof *base->data.argv * (argc+1));
        for (int i=0; i<argc; i++)
            base->data.argv[i] = argv[i];
        base->data.argv[argc] = NULL;
        free(argv);
        // nest under any redirections parsed earlier
        if (cmd)
		{
            cmd->left = base;
            return cmd;
        }
        return base;
    }
    // if no WORD at all, error
    free(argv);
    if (cmd) return cmd;
    return NULL;
}

/* complete_command : command_list */
t_ast *ft_parser(t_token **toks)
{
    // skip any  TOKEN_EMPTY (linebreak) if you tokenize newline
    t_ast *list = parse_command_list(toks);
    if (!list) return NULL;
    t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
    root->left = list;
    return root;
}
