/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 09:34:49 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/11 14:41:59 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}

// #include <stdio.h>

// void del(void *content)
// {
//   free(content);
// }

// void	*to_upper(void *content)
// {
//     char	*s;
//     char	*new_str;
//     size_t	len;
//     size_t	i;

//     s = (char *)content;
//     len = ft_strlen(s);
//     new_str = (char *)malloc((len + 1) * sizeof(char));
//     if (!new_str)
//         return (NULL);
//     i = 0;
//     while (i < len)
//     {
//         if (s[i] >= 'a' && s[i] <= 'z')
//             new_str[i] = s[i] - 32;
//         else
//             new_str[i] = s[i];
//         i++;
//     }
//     new_str[len] = '\0';
//     return (new_str);
// }

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
// 	t_list	*new_lst;

// 	node1 = ft_lstnew(ft_strdup("First (1)"));
// 	node2 = ft_lstnew(ft_strdup("Second (2)"));
// 	node3 = ft_lstnew(ft_strdup("Third (3)"));
// 	ft_lstadd_back(&node1, node2);
// 	ft_lstadd_back(&node1, node3);
// 	printlst(node1);

// 	new_lst = ft_lstmap(node1, to_upper, del);
// 	printlst(new_lst);

// 	ft_lstclear(&node1, del);
//     ft_lstclear(&new_lst, del);
// }
