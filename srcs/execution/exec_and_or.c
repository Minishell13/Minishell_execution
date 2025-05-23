/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:31:59 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/23 17:58:20 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//* -------------------------------- AND_OR --------------------------------

t_error	ft_execute_and_or(t_ast *root, t_ast *node, char **envp)
{
    if (node->type == GRAM_OPERATOR_AND)
    {
        int status = ft_executor(root, node->children[0], envp);
        if (status == 0)
            status = ft_executor(root, node->children[1], envp);
        return (status);
    }

    if (node->type == GRAM_OPERATOR_OR)
    {
        int status = ft_executor(root, node->children[0], envp);
        if (status != 0)
            status = ft_executor(root, node->children[1], envp);
        return (status);
    }
    return (ERROR);
}

