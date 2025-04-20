/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:51:16 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/10 18:00:34 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;

	if (!del || !lst || !*lst)
		return ;
	while (*lst)
	{
		node = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = node;
	}
}

// #include <stdio.h>

// void	printlst(t_list *lst)
// {
// 	if (lst)
// 	{
// 		while (lst)
// 		{
// 			printf("%s - ", (char *)(lst->content));
// 			lst = lst->next;
// 		}
// 	}
// 	printf("NULL\n");
// }

// void del(void *content)
// {
//   free(content);
// }

// int	main()
// {
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;

// 	node1 = ft_lstnew(ft_strdup("First 1"));
// 	node2 = ft_lstnew(ft_strdup("Second 2"));
// 	node3 = ft_lstnew(ft_strdup("Third 3"));
// 	ft_lstadd_back(&node1, node2);
// 	ft_lstadd_back(&node1, node3);

// 	printlst(node1);
// 	ft_lstclear1(&node1, del);
// 	printlst(node1);
// }
