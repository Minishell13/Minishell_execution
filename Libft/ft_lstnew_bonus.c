/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:18:30 by abnsila           #+#    #+#             */
/*   Updated: 2024/11/08 16:26:04 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

// #include <stdio.h>

// void	print_node(t_list *node)
// {
// 	printf("----------------------------------------\n");
// 	printf("node Address: %p\n", &node);
// 	printf("node Content: %s\n", (char *)node->content);
// 	printf("node Next: %p\n", (t_list *)node->next);
// 	printf("----------------------------------------\n");
// }

// int	main(void)
// {
// 	t_list	*node;
// 	char	content[] = "Abdellah";
// 	node = ft_lstnew((void *)content);
// 	print_node(node);
// }
