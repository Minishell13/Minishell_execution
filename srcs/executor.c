/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:45:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/24 14:43:56 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_simple_cmd(char **argv);

// TODO: You need first to know the exact struct of AST tree
// TODO: The representation each node with his type and args
// TODO: How to parcoure throw this three and get nodes in the correct order
// TODO: Create functions for execution (per node type)
// TODO: Focus on execution flow, (memory, fds, error) management
// TODO: ...

void	ft_executor()
{
	
}

// Example: cat file.txt | grep foo > out.txt

// GRAM_COMPLETE_COMMAND
// └── left → GRAM_PIPELINE
//       ├── left → GRAM_SIMPLE_COMMAND
//       │      └ data.argv = ["cat","file.txt",NULL]
//       └── right → GRAM_REDIR_OUT
//                  ├ data.redir.file   = "out.txt"
//                  ├ data.redir.append = false
//                  └ left → GRAM_SIMPLE_COMMAND
//                           └ data.argv = ["grep","foo",NULL]
