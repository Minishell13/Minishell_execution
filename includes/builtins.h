#ifndef BUILTINS_H
#define BUILTINS_H

# include "typedef.h"

// Setup
void	setup_env(char **env);

t_error	exec_env();
t_error exec_cd(char *path);

#endif
