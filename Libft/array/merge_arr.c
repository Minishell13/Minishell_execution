/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:12:58 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 19:14:25 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**merge_arr(char **arr1, char **arr2)
{
	int		len1;
	int		len2;
	char	**tmp;

	if (!arr1 || !arr2)
		return (NULL);
	len1 = arr_len(arr1);
	len2 = arr_len(arr2);
	tmp = ft_realloc(arr1, sizeof(char *) * (len1 + 1)
			, sizeof(char *) * (len1 + len2 + 1));
	if (!tmp)
		return (clear_arr(arr1), clear_arr(arr2), NULL);
	for (int i = 0; i < len2; ++i)
		tmp[len1 + i] = arr2[i];
	tmp[len1 + len2] = NULL;
	return (free(arr2), tmp);
}
