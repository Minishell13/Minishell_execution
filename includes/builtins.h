#ifndef BUILTINS_H
#define BUILTINS_H

# include "typedef.h"

int		valid_key(char *arg);
char	*extract_key(char *arg, int end);

t_error	exec_env();
t_error	exec_export(char **args);
t_error	exec_unset(char **keys);
t_error exec_pwd();
t_error	exec_cd(char *path);

#endif
