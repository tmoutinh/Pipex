/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:31:28 by tmoutinh          #+#    #+#             */
/*   Updated: 2023/06/11 18:04:27 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_command_execution(int *fd, char *cmd_passed, char *argv, char **env)
{
	char	*path;
	int		file;
	char	**cmd;

	cmd = ft_split(cmd_passed, ' ');
	path = access_path(cmd_passed, env, cmd);
	printf("%s\n", argv);
	file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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

void	child_command_execution(int *fd, char *cmd_passed, char **argv, char **env)
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
		dup2(fd[1], STDOUT_FILENO);
		dup2(file, STDIN_FILENO);
		close(fd[0]);
		if (execve(path, cmd, env) == -1)
			exit_error("\x1b[31mError: Child not executed\x1b[0m");
	}
	else
		exit_error("\x1b[31mNot valid command\x1b[0m");
}

void	initializer(int argc, char **argv, char **env, int cmd_number)
{
	int	fd[cmd_number][2];
	int	pid[cmd_number - 1];
	int	i;
	//fd[0] = STDINPUT
	//fd[1] = STDOUT
	i = -1;
	while (++i < cmd_number)
	{
		if (pipe(fd[i]) == -1)
			exit_error("\x1b[31mError: Pipe not generated\n\x1b[0m");
	}
	i = -1;
	while (++i < cmd_number - 1)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit_error("\x1b[31mError: Fork not executed\n\x1b[0m");
		if (pid[i] == 0) //Child Process
		{
			printf("The cmd being passed to child is = %s\n", argv[2 + i]);
			child_command_execution(fd[i], argv[2 + i], argv, env);
		}
	}
	//Parent Process
	i = -1;
	while (++i < cmd_number - 1)
	{
		waitpid(pid[i], NULL, 0);
	}
	printf("i = %d\n", i);
	printf("The cmd being passed to parent is = %s\n", argv[1 + cmd_number]);
	parent_command_execution(fd[i], argv[1 + cmd_number], argv[argc - 1], env);
}

int	main(int argc, char **argv, char **env)
{
	int	cmd_number;

	if (argc >= 5)
	{
		cmd_number = 0;
		while (cmd_number + 3 < argc)
			cmd_number++;
		printf("Number of cmds = %d\n", cmd_number);
		printf("After cmds = %s\n", argv[cmd_number + 2]);
		initializer(argc, argv, env, cmd_number);
	}
	else
	{
		ft_putstr_fd("\x1b[31mError: Bad arguments\n\x1b[0m", 2);
		exit_error("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
	}
	return (0);
}
