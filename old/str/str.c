/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:58:08 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 12:58:17 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str *merge_str(t_str *s1, t_str *s2)
{
	t_str	*s;

	if (!s1 || !s2 || !s1->str || !s2->str)
		return (NULL);
	s = (t_str *) ft_calloc(1, sizeof(t_str));
	if (!s)
		return (NULL);
	s->str = ft_strjoin(s1->str, s2->str);
	s->i = 0;
	s->len = ft_strlen(s->str);
	return (s);
}

t_str	*newstr(char *str)
{
	t_str	*node;

	node = (t_str *)ft_calloc(1, sizeof(t_str));
	if (!node)
		return (NULL);
	node->str = str;
	node->i = 0;
	node->len = ft_strlen(str);
	return (node);
}

void	clear_str(t_str *s)
{
	if (!s)
		return ;
	free(s->str);
	free(s);
}

// value -> ft_newstr(value)
// ft_newstr(value) + value -> ft_newstr(value)

// TODO: the actual struct is for each fragement (field), you can keep this strut only for string itself:

	// typedef struct  s_str
	// {
	// 	char    *str;
	//  size_t	i;
	// 	size_t  len;
	// }               t_str;

	// typedef struct  s_frag
	// {
	// 	t_str	str;
	//  t_str	mask;
	// }               t_frag;

// TODO do a demo node and test helper functions

// TODO: You must ignore readline leak (from valgrind)



