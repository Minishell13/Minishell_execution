/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:47:21 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/21 15:14:41 by abnsila          ###   ########.fr       */
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

char	*ft_charjoin(char *s, char c)
{
	size_t	s_len;
	size_t	total_size;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	total_size = (s_len + sizeof(c)) + 1;
	ptr = (char *) ft_calloc(1, total_size);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, total_size);
	free(s);
	ptr[s_len] = c;
	ptr[s_len + 1] = '\0';
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
