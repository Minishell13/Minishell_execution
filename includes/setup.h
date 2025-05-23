/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:19:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 21:20:54 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
#define SETUP_H

# include "typedef.h"

t_bool	var_exist(char *key);
int		get_var_index(char *key);
void	unset_var(char *key);
char	*get_value(char *key);
void	add_var(char *key, char *value);
void	setup_env(char **env);

#endif
