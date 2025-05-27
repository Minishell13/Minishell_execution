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


## Remarque
- Before run the cmd, you see the redir list
- all heredoc execute first, then run all other redir, then run the cmd
- so the last redir affect the stdin/stdout
- Each herdoc restore stdin