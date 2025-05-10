#ifndef MINISHELL_H
#define MINISHELL_H

# include "typedef.h"
// # include "lexer.h"
// # include "parser.h"
# include "expand.h"
# include "execution.h"
# include "colors.h"

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
t_ast	*ft_new_ast_node(t_gram type);
char	**ft_create_args(int count, ...);

// Builts in execution functions
void	ft_generate_tmpfile(t_redir *redir);

// Cleanup
void	ft_destroy_ast(t_ast *ast);
void	ft_free_array(char **arr);
void	ft_free_count_array(char **arr, int count);

// Debugging
void	ft_print_ast(const t_ast *node, int indent);

// AST Examples
t_ast	*ft_get_ast_example(int n);

// Errors
void	ft_put_error(char *arg);


#endif
