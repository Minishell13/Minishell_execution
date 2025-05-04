# Minishell_learn_repo
The initial look to this project


## Exit Code Mapping :

|                                      Situation | Exit Code |
| ---------------------------------------------: | :-------: |
|                   Command not found (`ENOENT`) |    127    |
|            Found but not executable (`EACCES`) |    126    |
|                     Bad argument (usage error) |     2     |
|              Redirection file missing or error |     1     |
|                              `SIGINT` (Ctrl-C) |    130    |
|                                      `SIGQUIT` |    131    |
| Other `execve()` failures (`ENOMEM`, `EFAULT`) |    126    |

