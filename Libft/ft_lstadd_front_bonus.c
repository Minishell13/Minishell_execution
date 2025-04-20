/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:34:15 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/10 10:16:30 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	if (!lst || !new_node)
		return ;
	new_node->next = *lst;
	*lst = new_node;
}

// #include <stdio.h>

// void	printlst(t_list *lst)
// {
// 	printf("%p\n", lst);
// 	if (lst)
// 	{
// 		while (lst)
// 		{
// 			printf("%s - ", (char *)(lst->content));
// 			lst = lst->next;
// 		}
// 		printf("NULL\n");
// 	}
// }

// int	main()
// {
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;

// 	node1 = ft_lstnew("First (1)");
// 	node2 = ft_lstnew("Second (2)");
// 	node3 = ft_lstnew("Third (3)");
// 	ft_lstadd_front(&node1, node2);
// 	ft_lstadd_front(&node1, node3);
// 	printlst(node1);
// }
