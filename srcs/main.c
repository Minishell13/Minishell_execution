/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/20 16:54:53 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	print_prompt1(void)
{
	fprintf(stderr, "$ ");
}

void	print_prompt2(void)
{
	fprintf(stderr, "> ");
} 

int main(int argc, char **argv)
{
	char *cmd;
	do
	{
		print_prompt1();
		cmd = read_cmd();
		if(!cmd)
		{
			exit(EXIT_SUCCESS);
		}

		if(cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
		{
			free(cmd);
			continue;
		}

		if(strcmp(cmd, "exit\n") == 0)
		{
			free(cmd);
			break;
		}

		printf("%s\n", cmd);        free(cmd);
	}	while(1);
	exit(EXIT_SUCCESS);
} 