/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_examples.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:49:24 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 14:54:35 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//? Command: cat ./temp/file.txt | grep foo > ./temp/out.txt
t_ast	*ft_get_ast0(void)
{
	// Simple command: cat ./temp/file.txt
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(2, "cat", "./temp/file.txt");

	// Simple command: grep foo
	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd2->data.args = ft_create_args(2, "grep", "foo");

	// I/O redirect: > ./temp/out.txt
	t_ast *redir = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir->data.redir.file = strdup("./temp/out.txt");
	redir->data.redir.type = GRAM_REDIR_OUT;
	redir->left = cmd2;

	// Pipeline: cmd1 | redir(cmd2)
	t_ast *pipe = ft_new_ast_node(GRAM_PIPELINE);
	pipe->left = cmd1;
	pipe->right = redir;

	// Complete command wrapper
	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = pipe;
	return root;
}

//? Command: < ./temp/infile cat | wc > ./temp/outfile
// Builds: input redirection, pipeline, ./temp/output redirection
t_ast *ft_get_ast1(void)
{
	// Simple command: ls -l
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(1, "cat");

	// Simple command: wc -l
	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd2->data.args = ft_create_args(1, "wc");

	// Pipeline: cmd1 | cmd2
	t_ast *pipe = ft_new_ast_node(GRAM_PIPELINE);
	pipe->left  = cmd1;
	pipe->right = cmd2;

	// ./temp/Output redirection: > ./temp/outfile
	t_ast *redir_out = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir_out->data.redir.file   = strdup("./temp/outfile");
	redir_out->data.redir.type   = GRAM_REDIR_OUT;
	redir_out->left              = pipe;

	// Input redirection: < ./temp/infile
	t_ast *redir_in = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir_in->data.redir.file    = strdup("./temp/infile");
	redir_in->data.redir.type    = GRAM_REDIR_IN;
	redir_in->left               = redir_out;

	// Complete command wrapper
	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = redir_in;
	return root;
}

//? Command: make && make clean && clear
// Builds: chained && operators
t_ast *ft_get_ast2(void)
{
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(1, "make");

	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd2->data.args = ft_create_args(2, "make", "clean");

	t_ast *cmd3 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd3->data.args = ft_create_args(1, "clear");

	// First AND: make && make clean
	t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and1->left  = cmd1;
	and1->right = cmd2;

	// Second AND: (and1) && clear
	t_ast *and2 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and2->left  = and1;
	and2->right = cmd3;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = and2;
	return root;
}

//? Command: << "END" grep "gg" | wc -l >> ./temp/outfile
// Builds: here-doc, pipeline, append redirection
t_ast *ft_get_ast3(void)
{
	// Simple command: grep "gg"
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(2, "grep", "gg");
	
	// Here-doc limiter
	t_ast *heredoc = ft_new_ast_node(GRAM_IO_REDIRECT);
	ft_generate_tmpfile(&(heredoc->data.redir));
	heredoc->data.redir.type = GRAM_HEREDOC;
	heredoc->data.redir.limiter = strdup("END");
	heredoc->left = cmd1;

	// Simple command: wc -l
	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd2->data.args = ft_create_args(2, "wc", "-l");

	// Pipeline: heredoc(cmd1) | cmd2
	t_ast *pipe = ft_new_ast_node(GRAM_PIPELINE);
	pipe->left  = heredoc;
	pipe->right = cmd2;

	// Append redirection: >> ./temp/outfile
	t_ast *redir_app = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir_app->data.redir.file = strdup("./temp/outfile");
	redir_app->data.redir.type = GRAM_REDIR_APPEND;
	redir_app->left           = pipe;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = redir_app;
	return root;
}

//? Command: << "END" grep "gg" | wc -l && (ls -l | wc > ./temp/out) >> ./temp/outfile
// Builds: here-doc, pipeline, AND, subshell, redirections, append
t_ast *ft_get_ast4(void)
{
	// Simple command: grep "gg"
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(2, "grep", "gg");
	
	// Here-doc limiter
	t_ast *heredoc = ft_new_ast_node(GRAM_IO_REDIRECT);
	ft_generate_tmpfile(&(heredoc->data.redir));
	heredoc->data.redir.type    = GRAM_HEREDOC;
	heredoc->data.redir.limiter = strdup("END");
	heredoc->left = cmd1;

	// Simple command: wc -l
	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd2->data.args = ft_create_args(2, "wc", "-l");

	// Pipeline left: heredoc(cmd1) | cmd2
	t_ast *pipe1 = ft_new_ast_node(GRAM_PIPELINE);
	pipe1->left  = heredoc;
	pipe1->right = cmd2;

	// Subshell: ls -l | wc > ./temp/out
	t_ast *cmd3 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd3->data.args = ft_create_args(2, "ls", "-l");
	t_ast *cmd4 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd4->data.args = ft_create_args(1, "wc");
	t_ast *pipe2 = ft_new_ast_node(GRAM_PIPELINE);
	pipe2->left  = cmd3;
	pipe2->right = cmd4;
	t_ast *redir_sub = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir_sub->data.redir.file = strdup("./temp/out");
	redir_sub->data.redir.type = GRAM_REDIR_OUT;
	redir_sub->left = pipe2;
	t_ast *subshell = ft_new_ast_node(GRAM_SUBSHELL);
	subshell->left = redir_sub;

	// Append redirection: >> ./temp/outfile
	t_ast *redir_app = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir_app->data.redir.file = strdup("./temp/outfile");
	redir_app->data.redir.type = GRAM_REDIR_APPEND;
	redir_app->left           = subshell;
	
	// AND: pipe1 && redir_app
	t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and1->left  = pipe1;
	and1->right = redir_app;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = and1;
	return root;
}

//? Command: grep "error" system.log | sort -u > ./temp/errors.txt
t_ast *ft_get_ast5(void)
{
	// grep "error" system.log
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(3, "grep", "error", "system.log");

	// sort -u
	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd2->data.args = ft_create_args(2, "sort", "-u");

	// pipeline cmd1 | cmd2
	t_ast *pipe = ft_new_ast_node(GRAM_PIPELINE);
	pipe->left  = cmd1;
	pipe->right = cmd2;

	// redirect > ./temp/errors.txt
	t_ast *redir = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir->data.redir.file   = strdup("./temp/errors.txt");
	redir->data.redir.type   = GRAM_REDIR_OUT;
	redir->left              = pipe;

	// complete
	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = redir;
	return root;
}

//? Command: make clean && make all || echo "Build failed"
t_ast *ft_get_ast6(void)
{
	// make clean
	t_ast *c1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	c1->data.args = ft_create_args(2, "make", "clean");

	// make all
	t_ast *c2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	c2->data.args = ft_create_args(2, "make", "all");

	// echo "Build failed"
	t_ast *c3 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	c3->data.args = ft_create_args(2, "echo", "Build failed");

	// c1 && c2
	t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and1->left  = c1;
	and1->right = c2;

	// and1 || c3
	t_ast *or1 = ft_new_ast_node(GRAM_OPERATOR_OR);
	or1->left  = and1;
	or1->right = c3;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = or1;
	return root;
}

//? Command: (cd src && make) > ./temp/build.log
t_ast *ft_get_ast7(void)
{
	// cd src
	t_ast *d = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	d->data.args = ft_create_args(2, "cd", "src");

	// make
	t_ast *m = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	m->data.args = ft_create_args(1, "make");

	// d && m
	t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and1->left  = d;
	and1->right = m;

	// subshell ( … )
	t_ast *sub = ft_new_ast_node(GRAM_SUBSHELL);
	sub->left = and1;

	// redirect > build.log
	t_ast *redir = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir->data.redir.file = strdup("./temp/build.log");
	redir->data.redir.type = GRAM_REDIR_OUT;
	redir->left            = sub;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = redir;
	return root;
}

//? Command: <<EOF grep foo | tee ./temp/foo.log
t_ast *ft_get_ast8(void)
{
	// heredoc EOF
	t_ast *hd = ft_new_ast_node(GRAM_IO_REDIRECT);
	hd->data.redir.file    = strdup("EOF");
	hd->data.redir.type    = GRAM_HEREDOC;
	hd->data.redir.limiter = strdup("EOF");

	// grep foo
	t_ast *g = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	g->data.args = ft_create_args(2, "grep", "foo");
	hd->left      = g;

	// tee foo.log
	t_ast *t = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	t->data.args = ft_create_args(2, "tee", "./temp/foo.log");

	// hd | t
	t_ast *pipe = ft_new_ast_node(GRAM_PIPELINE);
	pipe->left  = hd;
	pipe->right = t;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = pipe;
	return root;
}

//? Command: cat ./temp/in.txt | grep -v "^#" && wc -l || echo "0"
t_ast *ft_get_ast9(void)
{
	// cat ./temp/in.txt
	t_ast *c = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	c->data.args = ft_create_args(2, "cat", "./temp/in.txt");

	// grep -v "^#"
	t_ast *g = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	g->data.args = ft_create_args(3, "grep", "-v", "^#");

	// pipeline c | g
	t_ast *p = ft_new_ast_node(GRAM_PIPELINE);
	p->left  = c;
	p->right = g;

	// wc -l
	t_ast *w = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	w->data.args = ft_create_args(2, "wc", "-l");

	// echo "0"
	t_ast *e = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	e->data.args = ft_create_args(2, "echo", "0");

	// p && w
	t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and1->left  = p;
	and1->right = w;

	// and1 || e
	t_ast *or1 = ft_new_ast_node(GRAM_OPERATOR_OR);
	or1->left  = and1;
	or1->right = e;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = or1;
	return root;
}

//? Command: sleep 30 &> ./temp/sleep.log &
t_ast *ft_get_ast10(void)
{
	// sleep 30
	t_ast *s = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	s->data.args = ft_create_args(2, "sleep", "30");

	// redirect both stdout/stderr: &> sleep.log
	t_ast *redir = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir->data.redir.file = strdup("./temp/sleep.log");
	redir->data.redir.type = GRAM_REDIR_OUT; // treat &> as ./temp/OUT+ERR
	redir->left            = s;

	// (no intrinsic background node—handled in executor)
	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = redir;
	return root;
}

//? Command: (echo foo || false) && (date; uptime) | awk '{print $1}'
t_ast *ft_get_ast11(void)
{
	// echo foo
	t_ast *e1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	e1->data.args = ft_create_args(2, "echo", "foo");
	// false
	t_ast *f = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	f->data.args = ft_create_args(1, "false");

	// e1 || f
	t_ast *or1 = ft_new_ast_node(GRAM_OPERATOR_OR);
	or1->left  = e1;
	or1->right = f;

	t_ast *sub1 = ft_new_ast_node(GRAM_SUBSHELL);
	sub1->left = or1;

	// date
	t_ast *d = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	d->data.args = ft_create_args(1, "date");
	// uptime
	t_ast *u = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	u->data.args = ft_create_args(1, "uptime");

	// list ; is like COMMAND_LIST under a subshell
	t_ast *list = ft_new_ast_node(GRAM_COMMAND_LIST);
	list->left  = d;
	list->right = u;

	t_ast *sub2 = ft_new_ast_node(GRAM_SUBSHELL);
	sub2->left = list;

	// sub2 | awk '{print $1}'
	t_ast *awk = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	awk->data.args = ft_create_args(2, "awk", "{print $1}");

	t_ast *pipe = ft_new_ast_node(GRAM_PIPELINE);
	pipe->left  = sub2;
	pipe->right = awk;

	// join sub1 AND pipe
	t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and1->left  = sub1;
	and1->right = pipe;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = and1;
	return root;
}

//? Command: <<A cat <<B fileB | sed 's/x/y/' | tee ./temp/out.txt A B
t_ast *ft_get_ast12(void)
{
	// heredoc A for first cat
	t_ast *hdA = ft_new_ast_node(GRAM_IO_REDIRECT);
	ft_generate_tmpfile(&(hdA->data.redir));
	hdA->data.redir.type    = GRAM_HEREDOC;
	hdA->data.redir.limiter = strdup("A");

	// heredoc B for cat
	t_ast *hdB = ft_new_ast_node(GRAM_IO_REDIRECT);
	ft_generate_tmpfile(&(hdB->data.redir));
	hdB->data.redir.type    = GRAM_HEREDOC;
	hdB->data.redir.limiter = strdup("B");
	hdB->left               = hdA;

	// cat
	t_ast *cat = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cat->data.args = ft_create_args(1, "cat");
	hdB->left = cat;

	// sed 's/x/y/'
	t_ast *sed = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	sed->data.args = ft_create_args(3, "sed", "s/x/y/", NULL);

	// pipe1: hdB | sed
	t_ast *p1 = ft_new_ast_node(GRAM_PIPELINE);
	p1->left  = hdB;
	p1->right = sed;

	// tee ./temp/out.txt
	t_ast *tee = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	tee->data.args = ft_create_args(2, "tee", "./temp/out.txt");

	// p1 | tee
	t_ast *pipe2 = ft_new_ast_node(GRAM_PIPELINE);
	pipe2->left  = p1;
	pipe2->right = tee;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = pipe2;
	return root;
}

//? Command: echo foo; ls -a; pwd
t_ast *ft_get_ast13(void)
{
	t_ast *e = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	e->data.args = ft_create_args(2, "echo", "foo");
	t_ast *l = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	l->data.args = ft_create_args(2, "ls", "-a");
	t_ast *p = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	p->data.args = ft_create_args(1, "pwd");

	// semi-colon list
	t_ast *list1 = ft_new_ast_node(GRAM_COMMAND_LIST);
	list1->left  = e;
	list1->right = l;
	t_ast *list2 = ft_new_ast_node(GRAM_COMMAND_LIST);
	list2->left  = list1;
	list2->right = p;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = list2;
	return root;
}

//? Command: (grep foo < ./temp/in.txt || echo nofoo) && tar -czf archive.tgz ./temp/outdir >> ./temp/log.txt
t_ast *ft_get_ast14(void)
{
	// grep foo
	t_ast *g = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	g->data.args = ft_create_args(2, "grep", "foo");

	// input redirect for grep: < ./temp/in.txt
	t_ast *ri = ft_new_ast_node(GRAM_IO_REDIRECT);
	ri->data.redir.file = strdup("./temp/in.txt");
	ri->data.redir.type = GRAM_REDIR_IN;
	ri->left            = g;

	// echo nofoo
	t_ast *e = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	e->data.args = ft_create_args(2, "echo", "nofoo");

	// ri || e
	t_ast *or1 = ft_new_ast_node(GRAM_OPERATOR_OR);
	or1->left  = ri;
	or1->right = e;

	// subshell
	t_ast *sub = ft_new_ast_node(GRAM_SUBSHELL);
	sub->left = or1;

	// tar -czf archive.tgz ./temp/outdir
	t_ast *t = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	t->data.args = ft_create_args(4, "tar", "-czf", "archive.tgz", "./temp/outdir");

	// redirect append >> ./temp/log.txt
	t_ast *ro = ft_new_ast_node(GRAM_IO_REDIRECT);
	ro->data.redir.file = strdup("./temp/log.txt");
	ro->data.redir.type = GRAM_REDIR_APPEND;
	ro->left            = t;

	// sub && ro
	t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and1->left  = sub;
	and1->right = ro;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = and1;
	return root;
}

//? Command: (head -n1 && head -n2 | cat -e || ls) < ./temp/infile | cat -n && echo hello > ./temp/outfile
t_ast	*ft_get_ast15(void)
{
	//* ------------- (head -n1 && head -n2 | cat -e || ls) -------------
	// Simple command: head -n1
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(2, "head", "-n1");

	// Simple command: head -n2
	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd2->data.args = ft_create_args(2, "head", "-n2");
	// Simple command: cat -e
	t_ast *cmd3 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd3->data.args = ft_create_args(2, "cat", "-e");
	// Pipeline: cmd1 | cmd2
	t_ast *pipe1 = ft_new_ast_node(GRAM_PIPELINE);
	pipe1->left = cmd2;
	pipe1->right = cmd3;

	// Simple command: ls
	t_ast *cmd4 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd4->data.args = ft_create_args(1, "ls");

	// AND: cmd1 | pipe1
	t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and1->left = cmd1;
	and1->right = pipe1;

	// OR: and1 || cmd4
	t_ast *or1 = ft_new_ast_node(GRAM_OPERATOR_OR);
	or1->left = and1;
	or1->right = cmd4;

	t_ast *subshell1 = ft_new_ast_node(GRAM_SUBSHELL);
	subshell1->left = or1;

	//* ------------- subshell1 < ./temp/infile -------------
	// I/O redirect: < ./temp/infile
	t_ast *redir1 = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir1->data.redir.file = strdup("./temp/infile");
	redir1->data.redir.type = GRAM_REDIR_IN;
	redir1->left = subshell1;

	//* ------------- redir1 | cat -n -------------
	// Simple command: cat -e
	t_ast *cmd5 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd5->data.args = ft_create_args(2, "cat", "-n");
	// Pipeline: redir1 | cmd5
	t_ast *pipe2 = ft_new_ast_node(GRAM_PIPELINE);
	pipe2->left = redir1;
	pipe2->right = cmd5;

	//* ------------- echo hello > ./temp/outfile -------------
	// Simple command: echo hello
	t_ast *cmd6 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd6->data.args = ft_create_args(2, "echo", "hello");
	// I/O redirect: > ./temp/outfile
	t_ast *redir2 = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir2->data.redir.file = strdup("./temp/outfile");
	redir2->data.redir.type = GRAM_REDIR_OUT;
	redir2->left = cmd6;

	//* ------------- pipe2 && redir2 -------------
	// AND: pipe2 && redir2
	t_ast *and2 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and2->left = pipe2;
	and2->right = redir2;

	// Complete command wrapper
	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = and2;
	return root;
}

//? Command: /gg | ls > ./temp/out
t_ast	*ft_get_ast16(void)
{
	// Simple command: /gg
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(1, "/gg");

	// Simple command: ls
	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd2->data.args = ft_create_args(1, "ls");

	// I/O redirect: > ./temp/out.txt
	t_ast *redir = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir->data.redir.file = strdup("./temp");
	redir->data.redir.type = GRAM_REDIR_OUT;
	redir->left = cmd2;

	// Pipeline: cmd1 | redir(cmd2)
	t_ast *pipe = ft_new_ast_node(GRAM_PIPELINE);
	pipe->left = cmd1;
	pipe->right = redir;

	// Complete command wrapper
	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = pipe;
	return root;
}

//? Commmand: ls -l < temp/infile > temp/outfile
t_ast	*ft_get_ast17(void)
{
	// Simple command: ls -l
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(1, "ls", "-l");

	// I/O redirect: < temp/infile
	t_ast *redir1 = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir1->data.redir.file = strdup("./temp/infile");
	redir1->data.redir.type = GRAM_REDIR_IN;
	redir1->left = cmd1;
	
	// I/O redirect: > ./temp/out.txt
	t_ast *redir2 = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir2->data.redir.file = strdup("./temp/outfile");
	redir2->data.redir.type = GRAM_REDIR_OUT;
	redir2->left = redir1;

	// Complete command wrapper
	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = redir2;
	return root;
}

//? Command: cat < ./temp/out
t_ast	*ft_get_ast18(void)
{
	// Simple command: ls
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(1, "cat");

	// I/O redirect: > ./temp/out.txt
	t_ast *redir = ft_new_ast_node(GRAM_IO_REDIRECT);
	redir->data.redir.file = strdup("./temp/out");
	redir->data.redir.type = GRAM_REDIR_IN;
	redir->left = cmd1;

	// Complete command wrapper
	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = redir;
	return root;
}

//? Command: << EOF &&
t_ast *ft_get_ast19(void)
{
	// 1) Build the heredoc redirection node
	t_ast *hd = ft_new_ast_node(GRAM_IO_REDIRECT);
	// Generate a unique temp-file name and mark as HEREDOC
	ft_generate_tmpfile(&hd->data.redir);
	hd->data.redir.type    = GRAM_HEREDOC;
	hd->data.redir.limiter = ft_strdup("EOF");
	// No 'left' child here—heredoc stands alone until execution

	// 2) Build the AND operator wrapping the heredoc
	t_ast *and = ft_new_ast_node(GRAM_OPERATOR_AND);
	and->left  = hd;
	and->right = NULL;  // trailing && with no command yet

	// 3) Wrap in a COMPLETE_COMMAND
	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = and;
	return root;
}

// TODO: Fix this ast example or the execution flow
//! Maybe i need just to skip incomplet commands (i add "pwd" for now)
//? Command: ls && << EOF && pwd
t_ast *ft_get_ast20(void)
{
	// 1) Simple command: ls
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(1, "ls");
	
	// 2) Here-doc redirect: << EOF (processed FIRST)
	t_ast *hd_redirect = ft_new_ast_node(GRAM_IO_REDIRECT);
	hd_redirect->data.redir.type = GRAM_HEREDOC;
	hd_redirect->data.redir.limiter = strdup("EOF");
	ft_generate_tmpfile(&hd_redirect->data.redir);


	// 3) Build AND operators
	t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and1->left = hd_redirect;  // Process heredoc first
	and1->right = cmd1;      // Then ls if heredoc succeeds

	// 4) Simple command: ls
	t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd2->data.args = ft_create_args(1, "pwd");

	t_ast *and2 = ft_new_ast_node(GRAM_OPERATOR_AND);
	and2->left = and1;
	and2->right = cmd2;

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = and2;
	return root;
}

//? Command: pwd
t_ast *ft_get_ast21(void)
{
	// 1) Simple command: ls
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(1, "pwd");

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = cmd1;
	return root;
}

//? Command: echo -n "OK"
t_ast *ft_get_ast22(void)
{
	// 1) Simple command: ls
	t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
	cmd1->data.args = ft_create_args(3, "echo", "-n", "OK");

	t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
	root->left = cmd1;
	return root;
}

//? Command: echo "'""$PATH""'" && echo '""$SHELL""' && echo ""$PWD"" && echo '"$CC"'
t_ast *ft_get_ast23(void)
{
    // Command 1: echo "'""$PATH""'"
    t_ast *cmd1 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd1->data.args = ft_create_args(2, "echo", "'\"$PATH\"'");

    // Command 2: echo '""$SHELL""'
    t_ast *cmd2 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd2->data.args = ft_create_args(2, "echo", "\"\"$SHELL\"\"");

    // Command 3: echo """$PWD""
    t_ast *cmd3 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd3->data.args = ft_create_args(2, "echo", "$a\"\"");

    // Command 4: echo ''$CC''
    t_ast *cmd4 = ft_new_ast_node(GRAM_SIMPLE_COMMAND);
    cmd4->data.args = ft_create_args(2, "echo", "'\"$CC\"'");

    // First AND: cmd1 && cmd2
    t_ast *and1 = ft_new_ast_node(GRAM_OPERATOR_AND);
    and1->left = cmd1;
    and1->right = cmd2;

    // Second AND: (cmd1 && cmd2) && cmd3
    t_ast *and2 = ft_new_ast_node(GRAM_OPERATOR_AND);
    and2->left = and1;
    and2->right = cmd3;

    // Third AND: ((cmd1 && cmd2) && cmd3) && cmd4
    t_ast *and3 = ft_new_ast_node(GRAM_OPERATOR_AND);
    and3->left = and2;
    and3->right = cmd4;

    // Wrap in complete command
    t_ast *root = ft_new_ast_node(GRAM_COMPLETE_COMMAND);
    root->left = and3;

    return root;
}


t_ast	*ft_get_ast_example(int n)
{
	static t_ast *(*examples[])(void) = {
		ft_get_ast0,
		ft_get_ast1,
		ft_get_ast2,
		ft_get_ast3,
		ft_get_ast4,
		ft_get_ast5,
		ft_get_ast6,
		ft_get_ast7,
		ft_get_ast8,
		ft_get_ast9,
		ft_get_ast10,
		ft_get_ast11,
		ft_get_ast12,
		ft_get_ast13,
		ft_get_ast14,
		ft_get_ast15,
		ft_get_ast16,
		ft_get_ast17,
		ft_get_ast18,
		ft_get_ast19,
		ft_get_ast20,
		ft_get_ast21,
		ft_get_ast22,
		ft_get_ast23,
	};
	int max = sizeof(examples) / sizeof(examples[0]);
	if (n < 0 || n >= max)
	{
		ft_putstr_fd("Error on get_ast_example\n", STDERR_FILENO);	
		return (NULL);
	}
	return (examples[n]());
}

