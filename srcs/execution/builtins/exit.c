/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:48:06 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/28 16:55:17 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exit(t_ast *root, t_ast *node)
{
	if (!no_args(node->data.args))
		builtins_error("exit: ", node->data.args[1], ": no options allowed");
	//TODO: Cleanup ressources
	ast_destroy(root);
	exit(sh.exit_code);
}
