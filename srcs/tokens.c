/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:45:27 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/23 17:43:15 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_last_token(t_token *token)
{
	t_token	*current;

	if (!token)
		return (NULL);
	current = token;
	while (current->next != token)
		current = current->next;
	return (current);
}

t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*node;

	node = (t_token *) malloc (sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = ft_strdup(value);
	node->type = type;
	node->prev = node;
	node->next = node;
	return (node);
}

void	ft_push_token(t_token **token, t_token *new)
{
	t_token	*last_token;

	if (!(*token))
	{
		*token = new;
		return ;
	}
	last_token = ft_last_token(*token);
	new->next = *token;
	new->prev = last_token;
	(*token)->prev = new;
	last_token->next = new;
	*token = new;
}

void	ft_add_token(t_token **token, t_token *new)
{
	t_token	*last_token;

	if (!(*token))
	{
		*token = new;
		return ;
	}
	last_token = ft_last_token(*token);
	last_token->next = new;
	new->next = (*token);
	new->prev = last_token;
}

t_token	*ft_pop_token(t_token **token)
{
	t_token	*popped_token;
	t_token	*last_token;

	popped_token = *token;
	if ((*token)->next == *token)
	{
		*token = NULL;
		return (popped_token);
	}
	last_token = ft_last_token(*token);
	(*token) = (*token)->next;
	last_token->next = *token;
	(*token)->prev = last_token;
	popped_token->next = popped_token;
	popped_token->prev = popped_token;
	return (popped_token);
}

int	ft_tokens_len(t_token *token)
{
	t_token	*current;
	int		size;

	current = token;
	size = 0;
	while (current)
	{
		size++;
		current = current->next;
		if (current == token)
			break ;
	}
	return (size);
}

void	ft_clear_tokens(t_token **list)
{
	t_token	*current;
	t_token	*temp;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		temp = current->next;
		free(current->value);
		free(current);
		if (temp == *list)
			break ;
		current = temp;
	}
	*list = NULL;
}
