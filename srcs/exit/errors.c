/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:17:40 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/05 14:33:23 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_format_error(char *format, char *error, char *arg)
{
	char	buffer[1024];

	ft_bzero(buffer, sizeof(buffer));
	if (!format || !error)
		return ;
	ft_strlcat(buffer, "sh", sizeof(buffer));
	ft_strlcat(buffer, ": ", sizeof(buffer));
	ft_strlcat(buffer, error, sizeof(buffer));
	if (arg)
	{
		ft_strlcat(buffer, ": ", sizeof(buffer));
		ft_strlcat(buffer, arg, sizeof(buffer));
	}
	ft_strlcat(buffer, "\n", sizeof(buffer));
	write(STDERR_FILENO, buffer, ft_strlen(buffer));
}

void	ft_put_error(char *arg)
{
	if (!arg)
		ft_format_error("%s: %s: %s", "command not found", " ");
	else if (ft_strchr(arg, '/'))
		ft_format_error("%s: %s: %s", strerror(errno), arg);
	else
		ft_format_error("%s: %s: %s", "command not found", arg);
}
