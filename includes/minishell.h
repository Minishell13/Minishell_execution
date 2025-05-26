#ifndef MINISHELL_H
#define MINISHELL_H

# include "typedef.h"
// # include "lexer.h"
// # include "parser.h"
# include "expand.h"
# include "setup.h"
# include "execution.h"
# include "builtins.h"
# include "colors.h"

extern	t_minishell sh;

// t_token		*ft_last_token(t_token *token);
// t_token		*ft_new_token(char *value, t_token_type type);
// void		ft_push_token(t_token **token, t_token *new);
// void		ft_add_token(t_token **token, t_token *new);
// t_token		*ft_pop_token(t_token **token);
// int			ft_tokens_len(t_token *token);
// void		ft_clear_tokens(t_token **list);

// void		ft_print_node(t_token *node);
// void		ft_print_tokens(t_token *list);


// AST Utils
t_ast	*ast_new_node(t_gram type);
int		ast_add_child(t_ast *parent, t_ast *child);
char	**ast_create_args(const char *s);
void	ast_destroy(t_ast *node);

// Builts in execution functions
void	generate_tmpfile(t_redir *redir);

// Cleanup
void	ft_free_array(char **arr);
void	ft_free_count_array(char **arr, int count);
void	clear_sh(t_ast *root);

// Debugging
void	ast_print(const t_ast *node, int indent);
char	*gram_name(t_gram g);

// AST Examples
t_ast	*ft_get_ast_example(int n);

// Errors
void	put_error(char *cmd);
void	get_error(char *path);


#endif
