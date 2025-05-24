#ifndef BUILTINS_H
#define BUILTINS_H

# include "typedef.h"

int		valid_key(char *arg);
char	*extract_key(char *arg, int end);
t_bool	check_input(char **args);

t_error	exec_env(t_ast *node);
t_error	exec_export(t_ast *node);
t_error	exec_unset(t_ast *node);
t_error exec_pwd(t_ast *node);
t_error	exec_cd(t_ast *node);
t_error	exec_echo(t_ast *node);
t_error	exec_exit(t_ast *root);

t_bool  is_builtins(t_ast *node);
t_error	exec_builtins(t_ast *root, t_ast *node);

#endif
