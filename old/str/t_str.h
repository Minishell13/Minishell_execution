/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:27:12 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 12:54:02 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_STR_H
# define T_STR_H

# include <stdlib.h>

typedef struct	s_str
{
	char	*str;
	size_t	i;
	size_t	len;
}				t_str;

t_str	*newstr(char *str);
t_str	*merge_str(t_str *s1, t_str *s2);
void	clear_str(t_str *s);

#endif
