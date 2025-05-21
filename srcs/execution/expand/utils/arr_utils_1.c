/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:48:57 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 15:30:43 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arr_len(char **arr)
{
	int	len;
	
	len = 0;
	if (!arr) return (len);
	while (arr[len])
		len++;
	return (len);
}

char	**copy_arr(char **new_arr, char **arr)
{
	int	i;

	if (!arr || !new_arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
		{
			clear_arr(new_arr);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

char	**dup_arr(char **arr)
{
	char	**new_arr;

	if (!arr)
		return (NULL);
	new_arr = (char **) ft_calloc(arr_len(arr) + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	if (!copy_arr(new_arr, arr))
		return (NULL);
	return (new_arr);
}

void	print_arr(char **arr)
{
	int	i;

	// printf("---------------------- Printing arr... ----------------------\n");
	if (!arr) return ;
	i = 0;
	while (arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
}

char	**last_item_ptr(char **arr)
{
	int	i;

	if (!arr || !arr[0])
		return (NULL);
	i = 0;
	while (arr[i + 1] != NULL)
		i++;
	return (&arr[i]);
}

void	clear_arr(char **arr)
{
	int	i;

	i = 0;
	// printf("---------------------- Clearing arr... ----------------------\n");
	if (!arr) return ;
	while (arr[i])
	{
		// printf("clear: %s\n", arr[i]);
		if (arr[i])
			free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}
