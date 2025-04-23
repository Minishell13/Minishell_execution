/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:14:45 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/23 16:15:00 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_node(t_token *node)
{
	ft_printf("|                     Node Members                     \n");
	ft_printf("| value:    %s                                              \n", node->value);
	// ft_printf("| prev: %p                                 \n", node->prev);
	// ft_printf("| next: %p                                 \n", node->next);
	ft_printf("|______________________________________________________\n");

}

void	print_token(t_token *list)
{
	t_token	*current;

	if (!list)
	{
		ft_printf("|                   List is empty !                    |\n");
		ft_printf("|______________________________________________________|\n");
		return ;
	}
	current = list;
	do {
		 print_node(current);
		current = current->next;
	} while (current != list);
}
