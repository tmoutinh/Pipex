/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:09:51 by tmoutinh          #+#    #+#             */
/*   Updated: 2023/06/22 18:12:48 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	executer(char *cmd_passed, char **env, char *message)
{	
	char	*path;
	char	**cmd;

	cmd = ft_split(cmd_passed, ' ');
	path = access_path(env, cmd);
	if (execve(path, cmd, env) == -1)
		exit_error(message);
}

void	child_command_execution(char *cmd_passed, char **env)
{
	int		fd[2];
	int		child;

	if (pipe(fd) == -1)
		exit_error("\x1b[31m Error creating pipe\x1b[0m");
	child = fork();
	if (child == -1)
		exit_error("\x1b[31m Error on the fork\x1b[0m");
	if (child == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		executer(cmd_passed, env, "\x1b[31mError: Child not executed\x1b[0m");
	}
	else
		extra(fd[0], fd[1], child);
}
