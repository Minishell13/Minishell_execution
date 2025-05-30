#ifndef MINISHELL_H
#define MINISHELL_H

# include "typedef.h"
# include "signals.h"
# include "setup.h"
# include "expand.h"
# include "execution.h"
# include "builtins.h"
# include "colors.h"

extern	t_minishell sh;

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
