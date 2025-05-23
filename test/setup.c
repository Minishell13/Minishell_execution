/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:25:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 22:06:18 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	char *key = "name";
	char *value = "Abdellah";
	
	setup_env(env);
	add_var(key, value);
	exec_env();
	printf("index of var: %d\n", get_var_index(key));
	char *v = get_value(key);
	printf("var value: %s\n", v);
	unset_var(key);
	printf("index of var: %d\n", get_var_index(key));
	exec_env();

	free(v);
	clear_arr(sh.my_env);

	return (EXIT_SUCCESS);
}

