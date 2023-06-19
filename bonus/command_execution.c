/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:09:51 by tmoutinh          #+#    #+#             */
/*   Updated: 2023/06/19 17:05:16 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_command_execution(int *output, char *cmd_passed, char *argv, char **env)
{
	char	*path;
	int		file;
	char	**cmd;

	cmd = ft_split(cmd_passed, ' ');
	path = access_path(cmd_passed, env, cmd);
	printf("file is = %s\n", argv);
	printf("cmd is = %s\n", cmd_passed);
	file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		exit_error("\x1b[31mError opening file\x1b[0m");
	if (path)
	{
		dup2(output[0], STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
		if (execve(path, cmd, env) == -1)
			exit_error("\x1b[31mError: Parent not executed\x1b[0m");
	}
	else
		exit_error("\x1b[31mNot valid command\x1b[0m");
}

void	child_command_execution(int *input, int *output, char *cmd_passed, char **argv, char **env, int i)
{
	char	*path;
	int		file;
	char	**cmd;

	cmd = ft_split(cmd_passed, ' ');
	path = access_path(cmd_passed, env, cmd);
	file = open(argv[1], O_RDONLY, 0777);
	if (file == -1)
		exit_error("\x1b[31mError opening file\x1b[0m");
	if (path)
	{
		if (i == 0)
		{
			dup2(file, STDIN_FILENO);
			dup2(output[1], STDOUT_FILENO);
		}
		else
		{
			dup2(input[0], STDIN_FILENO);
			dup2(output[1], STDOUT_FILENO);
		}
		if (execve(path, cmd, env) == -1)
			exit_error("\x1b[31mError: Child not executed\x1b[0m");
	}
	else
		exit_error("\x1b[31mNot valid command\x1b[0m");
}

void	execute(char *cmd_passed, char **env)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(cmd_passed, ' ');
	path = access_path(cmd_passed, env, cmd);
	if (execve(path, cmd, env) == -1)
		exit_error("\x1b[31mError: Child not executed\x1b[0m");
}
