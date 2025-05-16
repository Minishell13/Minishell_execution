/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:12:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/16 16:36:58 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arr_append(char **arr, char *str, t_bool take_ownership)
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
	if (take_ownership)
		new_arr[new_len - 2] = str;
	else
		new_arr[new_len - 2] = ft_strdup(str);
	new_arr[new_len - 1] = NULL;
	return (new_arr);
}

static char	**dup_but_last(char **arr)
{
	char	**new;
	size_t	len;
	size_t	i;

	len = arr_len(arr);
	if (len == 0)
		return (ft_calloc(1, sizeof(char *)));
	new = ft_calloc(len, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		new[i] = ft_strdup(arr[i]);
		if (!new[i++])
			return (clear_arr(new), NULL);
	}
	return (new);
}

static char	**copy_remaining(char **out, char **arr2, size_t i)
{
	size_t	j;
	size_t	len2;

	len2 = arr_len(arr2);
	j = 1;
	while (j < len2)
	{
		out[i] = ft_strdup(arr2[j]);
		if (!out[i++])
			return (clear_arr(out), NULL);
		j++;
	}
	return (out);
}

char	**inner_merge_arr(char **arr1, char **arr2)
{
	char	**out;
	char	*merged;
	size_t	lens[2];

	lens[0] = arr_len(arr1);
	lens[1] = arr_len(arr2);
	if (lens[0] == 0 && lens[1] == 0)
		return (arr1);
	else if (lens[0] == 0)
		return (clear_arr(arr1), arr2);
	else if (lens[1] == 0)
		return (clear_arr(arr2), arr1);
	out = dup_but_last(arr1);
	merged = ft_strjoin(arr1[lens[0] - 1], arr2[0]);
	if (!merged)
		return (clear_arr(arr1), clear_arr(arr2), NULL);
	out = arr_append(out, merged, true);
	out = copy_remaining(out, arr2, arr_len(out));
	return (clear_arr(arr1), clear_arr(arr2), out);
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


