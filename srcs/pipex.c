/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:31:28 by tmoutinh          #+#    #+#             */
/*   Updated: 2023/06/22 18:09:36 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_command_execution(int *fd, char **argv, char **env)
{
	char	*path;
	int		file;
	char	**cmd;

	cmd = ft_split(argv[3], ' ');
	path = access_path(env, cmd);
	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		exit_error("\x1b[31mError opening file\x1b[0m");
	if (path)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
		close(fd[1]);
		if (execve(path, cmd, env) == -1)
			exit_error("\x1b[31mError: Child not executed\x1b[0m");
	}
	else
		exit_error("\x1b[31mNot valid command\x1b[0m");
}

void	child_command_execution(int *fd, char **argv, char **env)
{
	char	*path;
	int		file;
	char	**cmd;

	cmd = ft_split(argv[2], ' ');
	path = access_path(env, cmd);
	file = open(argv[1], O_RDONLY, 0777);
	if (file == -1)
		exit_error("\x1b[31mError opening file\x1b[0m");
	if (path)
	{
		dup2(fd[1], STDOUT_FILENO);
		dup2(file, STDIN_FILENO);
		close(fd[0]);
		if (execve(path, cmd, env) == -1)
			exit_error("\x1b[31mError: Child not executed\x1b[0m");
	}
	else
		exit_error("\x1b[31mNot valid command\x1b[0m");
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit_error("\x1b[31mError: Pipe not generated\n\x1b[0m");
		pid = fork();
		if (pid == -1)
			exit_error("\x1b[31mError: Fork not executed\n\x1b[0m");
		if (pid == 0)
			child_command_execution(fd, argv, env);
		else
		{
			if (waitpid(pid, NULL, 0) == -1)
				exit_error("\x1b[31mError: Unable to wait\n\x1b[0m");
			parent_command_execution(fd, argv, env);
		}
	}
	else
	{
		ft_putstr_fd("\x1b[31mError: Bad arguments\n\x1b[0m", 2);
		exit_error("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
	}
	return (0);
}
