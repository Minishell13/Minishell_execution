/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:43:42 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 14:45:17 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct	s_array
{
	char	**data;
	size_t	size;
	size_t	capacity;
}			t_array;

t_array*	arr_create()
{
	t_array *arr = malloc(sizeof(t_array));
	arr->capacity = 8;
	arr->size = 0;
	arr->data = malloc(arr->capacity * sizeof(char *));
	return arr;
}

void	arr_append(t_array *arr, char *element)
{
	if (arr->size >= arr->capacity)
	{
		arr->capacity *= 2;
		arr->data = realloc(arr->data, arr->capacity * sizeof(char *));
	}
	arr->data[arr->size++] = element;
	arr->data[arr->size] = NULL;
}
