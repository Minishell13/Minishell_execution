/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:58:08 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 14:27:32 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_mask(size_t len, t_bool is_inside)
{
	char		*mask;
	size_t		i;

	mask = (char *) ft_calloc(len + 1, sizeof(char));
	if (!mask)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (is_inside)
			mask[i] = '1';
		else
			mask[i] = '0';	
		i++;	
	}
	mask[i] = '\0';
	return (mask);
}

t_frag	*newfrag(char *value, t_bool is_inside)
{
	t_frag	*frag;
	size_t	len;

	if (!value)
		return (NULL);
	frag = (t_frag *) ft_calloc(1, sizeof(t_frag));
	if (!frag)
		return (NULL);
	len = ft_strlen(value);
	frag->value = newstr(value);
	frag->mask = newstr(get_mask(len, is_inside));
	frag->next = NULL;
	return (frag);
}

t_frag	*last_frag(t_frag *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_frag(t_frag **lst, t_frag *frag)
{
	t_frag *last;

	if (!lst || !frag)
		return ;
	if (*lst == NULL)
	{
		*lst = frag;
		return ;
	}
	last = last_frag(*lst);
	if (last)
		last->next = frag;
}

t_frag	*split_frag(t_frag *frag)
{
	char	**arr;
	size_t	i;
	t_frag	*tmp;
	t_frag	*lst;

	arr = ft_split(frag->value->str, ' ');
	if (!arr)
		return (NULL);
	i = 0;
	lst = NULL;
	while (arr[i])
	{
		tmp = newfrag(ft_strdup(arr[i]), true);
		if (!tmp)
		return (clear_frags(lst), NULL);
		add_back_frag(&lst, tmp);
		i++;
	}
	clear_arr(arr);
	clear_frag(frag);
	return (lst);
}

// t_bool idx:   true : pop first     false: pop last
void	pop_frag(t_frag **lst, t_bool idx)
{
	t_frag	*tmp;

	// Pop First element
	if (idx)
	{
		tmp = *lst;
		*lst = ((*lst)->next);
		clear_frag(tmp);
	}
	// Pop last element
	else
	{
		while ((*lst))
		{
			if ((*lst)->next->next == NULL)
			{
				tmp = (*lst)->next;
				(*lst)->next = NULL;
				clear_frag(tmp);
				return ;
			}
			lst = &((*lst)->next);
		}
		
	}
}

t_frag	*merge_frags(t_frag *f1, t_frag *f2)
{
	t_frag	*merged;

	merged = (t_frag *) ft_calloc(1, sizeof(t_frag));
	if (!merged)
		return (NULL);
	
	merged->value = merge_str(f1->value, f2->value);
	merged->mask = merge_str(f1->mask, f2->mask);
	merged->next = NULL;
	return (merged);
}

t_frag	*merge_lsts(t_frag *l1, t_frag *l2)
{
	t_frag	*merged;

	merged = merge_frags(last_frag(l1), l2);
	if (!merged)
		return (NULL);
	pop_frag(&l1, false);
	pop_frag(&l2, true);
	add_back_frag(&l1, merged);
	merged->next = l2;
	return (NULL);
}









void	print_frag(t_frag *frag)
{
	printf("-------------------- Frag --------------------\n");
	printf("value : %s\n", frag->value->str);	
	printf("mask  : %s\n", frag->mask->str);
	printf("----------------------------------------------\n");
}

void	print_frags(t_frag *frag)
{
	printf("\n\n-------------------- List of Frags --------------------\n");
	while (frag)
	{
		print_frag(frag);
		frag = frag->next;
	}
}

void	clear_frag(t_frag *frag)
{
	clear_str(frag->value);
	clear_str(frag->mask);
	free(frag);
}

void	clear_frags(t_frag *frag)
{
	t_frag	*tmp;

	while (frag)
	{
		tmp = frag;
		frag = frag->next;
		clear_frag(tmp);
	}
	free(frag);
}



int	main()
{
	t_frag	*f0;
	t_frag	*f1;
	t_frag	*f2;

	f0 = newfrag(ft_strdup("f0 gg oo"), true);
	f1 = newfrag(ft_strdup("f1"), false);
	f2 = newfrag(ft_strdup("f2"), false);

	add_back_frag(&f0, f1);
	add_back_frag(&f0, f2);
	
	print_frags(f0);
	f0 = split_frag(f0);
	print_frags(f0);
	
	clear_frags(f0);
}


//? Test: newfrag, add_back_frag, merge_frags, merge_lsts, pop_frag, last_frag, get_mask, print_frag, print_frags, clear_frag, clear_frags
// int	main()
// {
// 	t_frag	*f0;
// 	t_frag	*f1;
// 	t_frag	*f2;
// 	t_frag	*f3;
// 	t_frag	*f4;

// 	f0 = newfrag(ft_strdup("f0"), true);
// 	f1 = newfrag(ft_strdup("f1"), false);
// 	f2 = newfrag(ft_strdup("f2"), false);
// 	f3 = newfrag(ft_strdup("f3"), true);
// 	f4 = newfrag(ft_strdup("f4"), true);

// 	add_back_frag(&f0, f1);
// 	add_back_frag(&f0, f2);
	
// 	add_back_frag(&f3, f4);
	

// 	print_frags(f0);	
	
// 	merge_lsts(f0, f3);

// 	print_frags(f0);

// 	clear_frags(f0);
// }
