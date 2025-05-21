/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:12:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 15:29:33 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//? Calloc Version
// char	**arr_append(char **arr, char *str)
// {
// 	char	**new_arr;
// 	int		new_len;
	
// 	if (!arr || !str)
// 		return (NULL);
// 	new_len = arr_len(arr) + 2;
// 	new_arr = (char **) ft_calloc(new_len, sizeof(char *));
// 	if (!new_arr)
// 		return (NULL);
// 	if (!copy_arr(new_arr, arr))
// 	{
// 		clear_arr(new_arr);	
// 		return (NULL);
// 	}
// 	new_arr[new_len - 2] = str;
// 	new_arr[new_len - 1] = NULL;
// 	clear_arr(arr);
// 	return (new_arr);
// }

//? Realloc Version (Optimized)
char **arr_append(char **arr, char *str)
{
	size_t old_len;
	char **new_arr;

	old_len = arr_len(arr);
	new_arr = (char **) realloc(arr, sizeof(char*) * (old_len + 2));
	if (!new_arr)
		return (free(str), NULL);
	new_arr[old_len]     = str;
	new_arr[old_len + 1] = NULL;
	return (new_arr);
}

static char	**dup_but_last(char **arr)
{
	char	**new;
	size_t	len;
	size_t	i;

	len = arr_len(arr);
	if (len == 0 || !arr)
		return (ft_calloc(1, sizeof(char *)));
	new = ft_calloc(len + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}




/*
 * Merge the last element of arr1 with the first of arr2,
 * producing a single new string, then append it to out.
 */
static char	*merge_edges(char *last1, char *first2, char **arr1, char **arr2)
{
	char	*merged;

	merged = ft_strjoin(last1, first2);
	if (!merged)
	{
		clear_arr(arr1);
		clear_arr(arr2);
	}
	return (merged);
}

/*
 * Append all remaining elements of arr2 (from index 1 onward)
 * into out, one strdup per element.
 */
static char	**append_rest(char **out, char **arr2)
{
	size_t	i;

	i = 1;
	while (arr2[i])
	{
		out = arr_append(out, ft_strdup(arr2[i]));
		if (!out)
		{
			clear_arr(arr2);
			return (NULL);
		}
		i++;
	}
	return (out);
}

/*
 * inner_merge_arr: merges arr1 and arr2 into a new array out:
 *   - If one is empty, returns the other (after freeing the empty one)
 *   - Otherwise, merges the “edge” elements, then appends the rest
 */
char	**inner_merge_arr(char **arr1, char **arr2)
{
	size_t	lens[2];
	char	**out;
	char	*edge;

	lens[0] = arr_len(arr1);
	lens[1] = arr_len(arr2);
	if (lens[0]  == 0 && lens[1] == 0)
		return (clear_arr(arr2), arr1);
	if (lens[0]  == 0)
		return (clear_arr(arr1), arr2);
	if (lens[1] == 0)
		return (clear_arr(arr2), arr1);
	out = dup_but_last(arr1);
	edge = merge_edges(arr1[lens[0]  - 1], arr2[0], arr1, arr2);
	if (!edge)
		return (NULL);

	out = arr_append(out, edge);
	if (!out)
		return (free(edge), clear_arr(arr2), NULL);

	out = (char **)append_rest(out, arr2);
	if (!out)
		return (NULL);
	return (clear_arr(arr1), clear_arr(arr2), out);
}


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



