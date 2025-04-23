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

typedef enum	e_token_type {
	TOK_WORD,		// e.g. "cat", "file.txt", "grep"
	TOK_PIPE,		// '|'
	TOK_REDIR_IN,	// '<'
	TOK_REDIR_OUT,	// '>'
	TOK_HERE_DOC,	// '<<'
	TOK_APPEND,		// '>>'
	/* … */
}				t_token_type;
 
typedef struct	s_token {
	char			*value;   // allocated string slice
	t_token_type	type;   // token kind
	struct s_token	*next;   // next in list
	struct s_token	*prev;   // previous in list
}				t_token;

t_token		*last(t_token *token);
t_token		*new(char *value, t_token_type type);
void		push(t_token **token, t_token *new);
void		add(t_token **token, t_token *new);
t_token		*pop(t_token **token);
int			token_size(t_token *token);
void		ft_clear(t_token **list);

void	print_node(t_token *node);
void	print_token(t_token *list);


#endif 