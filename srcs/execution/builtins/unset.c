/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:47:40 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 15:00:49 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	exec_unset(char **keys)
{
	int		i;
	
	i = 1;
	while (keys[i])
	{
		// Just for testing
		char *key = extract_key(keys[i], valid_key(keys[i]));
		unset_var(key);
		free(key);
		//TODO:  For real behavioure use this
		// unset_var(keys[i]);
		i++;
	}
	return (SUCCESS);
}
