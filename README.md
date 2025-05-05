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



#### Quotes prevent parameter expansion (Heredoc)

 - Without quotes:

```bash
a=0
cat <<EOF
$a
EOF
```

 - Output:
```bash
0
```

 - With quotes:
```bash
a=0
cat <<'EOF'
$a
EOF
```

 - or (ugly but valid):
```bash
a=0
cat <<E"O"F
$a
EOF
```

 - Outputs:
```bash
$a
```

##### Hyphen removes leading tabs

 - Without hyphen:
```bash
cat <<EOF
<tab>a
EOF
```

 - where <tab> is a literal tab, and can be inserted with Ctrl + V <tab>

 - Output:
```bash
<tab>a
```

 - With hyphen:
```bash
cat <<-EOF
<tab>a
<tab>EOF
```

Output:
```bash
a
```

