/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_frag.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:34:48 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 14:24:24 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_FRAG_H
# define T_FRAG_H

# include "typedef.h"

typedef struct	s_frag
{
	t_str			*value;
	t_str			*mask;
	struct s_frag	*next;
}				t_frag;

char	*get_mask(size_t len, t_bool is_inside);
t_frag	*newfrag(char *value, t_bool is_inside);

t_frag	*last_frag(t_frag *lst);
void	add_back_frag(t_frag **lst, t_frag *frag);

void	pop_frag(t_frag **lst, t_bool idx);
t_frag	*merge_frags(t_frag *f1, t_frag *f2);


void	print_frag(t_frag *frag);
void	print_frags(t_frag *frag);

void	clear_frag(t_frag *frag);
void	clear_frags(t_frag *frag);

#endif
