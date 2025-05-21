/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:12:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 17:07:41 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//? Calloc Version
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
		return (clear_arr(new_arr), NULL);
	if (!copy_arr(&(new_arr[len1]), arr2))
		return (clear_arr(new_arr), NULL);
	return (clear_arr(arr1), clear_arr(arr2), new_arr);
}

//? Realloc Version (Optimized)
/*
 * Append all strings from arr2 onto arr1, returning the combined array.
 * Uses realloc to avoid quadratic allocations.
 * Frees both inputs on success or failure.
 */
// char	**merge_arr(char **arr1, char **arr2)
// {
// 	int		len1;
// 	int		len2;
// 	char	**tmp;

// 	if (!arr1 || !arr2)
// 		return (NULL);
// 	len1 = arr_len(arr1);
// 	len2 = arr_len(arr2);
// 	tmp = realloc(arr1, sizeof(char *) * (len1 + len2 + 1));
// 	if (!tmp)
// 		creturn (clear_arr(arr1), clear_arr(arr2), NULL);
// 	for (int i = 0; i < len2; ++i)
// 		tmp[len1 + i] = arr2[i];
// 	tmp[len1 + len2] = NULL;
// 	return (free(arr2), tmp);
// }
