/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:47:21 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/12 16:23:31 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*ptr;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	total_size = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	ptr = (char *) malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, total_size);
	ft_strlcat(ptr, s2, total_size);
	return (ptr);
}

char	*ft_conststrjoin(char *s1, char *s2)
{
	size_t	total_size;
	char	*ptr;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	total_size = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	ptr = (char *) malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, total_size);
	free(s1);
	ft_strlcat(ptr, s2, total_size);
	free(s2);
	return (ptr);
}

char	*ft_charjoin(char *s1, char c)
{
	size_t	total_size;
	char	*ptr;

	if (s1 == NULL)
		return (NULL);
	total_size = (ft_strlen(s1) + sizeof(c)) + 1;
	ptr = (char *) ft_calloc(1, total_size);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, total_size);
	free(s1);
	ptr[total_size - 2] = c;
	ptr[total_size - 1] = '\0';
	return (ptr);
}

// #include <stdio.h>

// int main(int ac, char **av)
// {
// 	if (ac == 3)
// 	{
// 		printf("%s\n", ft_strjoin(av[1], av[2]));
// 		printf("%s\n", ft_strjoin(av[1], NULL));
// 		printf("%s\n", ft_strjoin(NULL, av[2]));
// 		printf("%s\n", ft_strjoin(NULL, NULL));
// 	}
// 	return (0);
// }
