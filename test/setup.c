/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:25:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 11:48:38 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	setup_env(env);
	
	char **args = init_arr();
	args = append_arr(args, ft_strdup("export"));
	args = append_arr(args, ft_strdup("a==.c"));
	args = append_arr(args, ft_strdup("b=*$f"));
	args = append_arr(args, ft_strdup("c=.md i"));
	args = append_arr(args, ft_strdup("a=*e.h"));
	args = append_arr(args, ft_strdup("c="));
	args = append_arr(args, ft_strdup("_="));
	args = append_arr(args, ft_strdup("NVM_DIR=NONE"));
	args = append_arr(args, ft_strdup("f_6=    OK"));
	args = append_arr(args, ft_strdup("1hh="));
	args = append_arr(args, ft_strdup("*hh="));
	args = append_arr(args, ft_strdup("$hh="));
	args = append_arr(args, ft_strdup("!6h="));
	args = append_arr(args, ft_strdup("_!6h="));
	args = append_arr(args, ft_strdup(".="));
	print_arr(args);


	exec_export(args);

	exec_env();
	// printf("var value: %s\n", get_value("f"));
	
	clear_arr(args);
	clear_arr(sh.my_env);

	return (EXIT_SUCCESS);
}

