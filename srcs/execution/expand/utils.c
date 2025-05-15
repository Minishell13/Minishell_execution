/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:48:57 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/15 16:59:39 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arr_len(char **arr)
{
	int	len;
	
	len = 0;
	while (arr[len])
	len++;
	return (len);
}

char	**copy_arr(char **new_arr, char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
			return (NULL);
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

char	**dup_arr(char **arr)
{
	char	**new_arr;
	
	new_arr = (char **) ft_calloc(arr_len(arr) + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	if (!copy_arr(new_arr, arr))
		return (NULL);
	return (new_arr);
}

char	**arr_append(char **arr, char *str)
{
	char	**new_arr;
	int		new_len;
	
	new_len = arr_len(arr) + 2;
	new_arr = (char **) ft_calloc(new_len, sizeof(char *));
	if (!new_arr)
		return (NULL);
	if (!copy_arr(new_arr, arr))
	{
		clear_arr(new_arr);	
		return (NULL);
	}
	new_arr[new_len - 2] = str;
	new_arr[new_len - 1] = NULL;
	return (new_arr);
}

int	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
	return (i);
}

char	**merge_arr(char **arr1, char **arr2)
{
	int		len1;	
	int		len2;
	int		len3;
	char	**new_arr;
	
		
	len1 = arr_len(arr1);	
	len2 = arr_len(arr2);
	len3 = len1 + len2 + 1;
	new_arr = (char **) ft_calloc(len3, sizeof(char *));
	if (!new_arr)
		return (NULL);
	if (!copy_arr(new_arr, arr1))
	{
		clear_arr(new_arr);	
		return (NULL);
	}
	if (!copy_arr(&(new_arr[len1]), arr2))
	{
		clear_arr(new_arr);	
		return (NULL);
	}
	clear_arr(arr1);
	clear_arr(arr2);
	return (new_arr);
}

void	clear_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}
