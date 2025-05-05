/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:48:43 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/05 14:51:22 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_check_access(char *file, int permission)
{
	if (access(file, permission) == -1)
		return (false);
	return (true);
}

char	*ft_parse_path(char **all_path, char *command)
{
	int		i;
	char	*temp;
	char	*path;
	char	*result;

	i = 0;
	result = NULL;
	while (all_path[i] && !result)
	{
		temp = ft_strjoin("/", command);
		if (!temp)
			break ;
		path = ft_strjoin(all_path[i], temp);
		free(temp);
		if (path && ft_check_access(path, X_OK))
			result = path;
		else
			free(path);
		i++;
	}
	ft_free_array(all_path);
	if (!result)
		result = ft_strdup(command);
	return (result);
}

char	*ft_get_path(char *command, char **envp)
{
	(void)envp;
	char	*path_var;
	char	**all_path;
	char	*path;

	// 1) If name contains '/', try it directly
	if (ft_strchr(command, '/'))
		return ft_strdup(command);
	// 2) Get PATH and split
	path_var = getenv("PATH");
	if (!path_var)
		return (ft_strdup(command));
	all_path = ft_split(path_var, ':');
	if (!all_path)
		return (ft_strdup(command));
	path = ft_parse_path(all_path, command);
	return (path);
}
