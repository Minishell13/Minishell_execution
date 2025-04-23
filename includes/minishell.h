#ifndef MINISHELL_H
#define MINISHELL_H

// Libft
# include "../Libft/includes/libft.h"

// Log
# include <stdio.h>

// Readline
# include <readline/readline.h>
# include <readline/history.h>

// Utils function
# include <stdlib.h>
# include <string.h>

// Error
# include <errno.h>

typedef enum	e_token_type
{
	TOK_WORD,		// e.g. "cat", "file.txt", "grep"
	TOK_PIPE,		// '|'
	TOK_REDIR_IN,	// '<'
	TOK_REDIR_OUT,	// '>'
	TOK_HERE_DOC,	// '<<'
	TOK_APPEND,		// '>>'
	/* … */
}				t_token_type;
 
typedef struct	s_token
{
	char			*value;   // allocated string slice
	t_token_type	type;   // token kind
	struct s_token	*next;   // next in list
	struct s_token	*prev;   // previous in list
}				t_token;

t_token		*ft_last_token(t_token *token);
t_token		*ft_new_token(char *value, t_token_type type);
void		ft_push_token(t_token **token, t_token *new);
void		ft_add_token(t_token **token, t_token *new);
t_token		*ft_pop_token(t_token **token);
int			ft_tokens_len(t_token *token);
void		ft_clear_tokens(t_token **list);

void		ft_print_node(t_token *node);
void		ft_print_tokens(t_token *list);


typedef enum {
	AST_CMD,         // simple command
	AST_PIPE,        // '|'
	AST_REDIR_OUT,   // '>' or '>>'
	AST_REDIR_IN,    // '<' or '<<'
	AST_AND,         // '&&'
	AST_OR,          // '||'
	AST_SUBSHELL,    // '( … )'
}   ast_type;  

typedef struct s_ast {
	ast_type       type;       // node kind
	struct s_ast  *left;       // left child / first element
	struct s_ast  *right;      // right child / next element
	union
	{
		char	**argv;       // for AST_CMD: NULL‑terminated argv
		struct
		{
			char *file;        // for redirections: target filename
			t_bool  append;      // true for '>>'
		} redir;
	}   data;
}   t_ast;

#endif
