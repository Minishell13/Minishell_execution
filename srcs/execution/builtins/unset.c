/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:40 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/28 17:10:06 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(t_ast *node)
{
	int		i;
	char	**keys;
	
	i = 1;
	keys = node->data.args;
	while (keys[i])
	{
		if (!no_options(keys[i]))
		{
			builtins_error("unset", NULL, ": no options allowed");
			return (EXIT_FAILURE);
		}
		// Just for testing
		// char *key = extract_key(keys[i], valid_key(keys[i]));
		// unset_var(key);
		// free(key);
		//TODO: For real behavioure use this
		unset_var(keys[i]);
		i++;
	}
	return (EXIT_FAILURE);
}
