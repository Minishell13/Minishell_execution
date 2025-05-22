
# Maybe Yes/No  handle those Commands :

```bash
ls && << EOF &&
ls && << EOF && pwd
```

## TODO:
- You are currently working in testing some ast example (16, 24)
- Go and make some test in redirection and prioipities to help parsing phase to continue correctly
- You have to complete: expansion, heredoc, files, command
- Do the expansion in right order to (&& or ||)
- build the buitins: start with env (ask team mate)
- So you can setup env, add utils to help in( env, export, unset)
- Check leaks, undefind behavioure, unclosed fds, zombie processes
- get last exit code from each comand fragement (pipe, subshell, &&, ||)
- struct the global variable correctly

## Expansion $:

- I need just to detect quote state and do expansion in `Default` and `Expand` modes
- Also do necessary (split and merge or apppend, ...) to the args arr
- I keep the quotes in each args result

## Expansion *:

- I need just to detect quote state and do expansion only in `Default` mode
- Do necessary actions (Remove quotes, split, merge, append, ...), to produce the final arr of args (files)
- 
- Replace the old node args arr with new expanded arr