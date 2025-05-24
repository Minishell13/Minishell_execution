#ifndef BUILTINS_H
#define BUILTINS_H

# include "typedef.h"

t_error	exec_env();
t_error	exec_export(char **args);
t_error exec_cd(char *path);

#endif
