/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:31:28 by tmoutinh          #+#    #+#             */
/*   Updated: 2023/06/20 16:42:45 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*For more than two commands*/
void	initializer(int argc, char **argv, char **env, int cmd_number)
{
	int	fd[cmd_number][2];
	int	pid[cmd_number - 1];
	int	i;
	int	j;
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
		//Child Process
		if (pid[i] == 0)
		{
			j = -1;
			while (++j < cmd_number - 1)
			{
				if (i != j)
					close(fd[j][0]);
				if (i + 1 != j)
					close(fd[j][1]);
			}
			printf("The cmd being passed to child is = %s\n", argv[2 + i]);
			child_command_execution(fd[i], fd[i + 1], argv[2 + i], argv, env);
		}
	}
	//Parent Process
	i = -1;
	while (++i < cmd_number - 2)
	{
		printf("%d\n", i);
		waitpid(pid[i], NULL, 0);
	}
	printf("Reaching parent ok\n");
	j = -1;
	while (++j < cmd_number)
	{
		if (j != cmd_number - 1)
			close(fd[j][0]);
		if (j != 0)
			close(fd[j][1]);
	}
	printf("i = %d\n", i);
	printf("The cmd being passed to parent is = %s\n", argv[1 + cmd_number]);
	parent_command_execution(fd[cmd_number - 1], argv[1 + cmd_number], argv[argc - 1], env);
}

void	here_doc(int argc, char **argv, char **env)
{
	int		reader;
	char	*line;
	int		fd[2];
	
	pipe(fd);
	reader = fork();
	if (reader == 0)
	{
		line = get_next_line(0);
		while (line)
		{
			close(fd[0]);
			//printf("ok\n");
			//printf("%s\n", line);
			if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
			line = get_next_line(0);
		}
	}
	else
	{
		close(fd[1]);
		//dup2(fd[0], STDIN_FILENO);
		wait(NULL);
		//parent_command_execution(fd, argv[4], argv[5], env);
		initializer(argc, argv, env, argc - 4);
	}
}

int	main(int argc, char **argv, char **env)
{
	if (ft_strncmp("here_doc", argv[1], ft_strlen("here_doc")) ==0 )
	{
		if (argc < 6)
			exit_error("\x1b[31mInsufficient parameters\x1b[0m");
		here_doc(argc, argv, env);
	}
	else if (argc >= 5)
	{
		printf("Number of cmds = %d\n", argc - 3);
		printf("After cmds = %s\n", argv[argc - 3 + 2]);
		initializer(argc, argv, env, argc - 3);
	}
	else
	{
		ft_putstr_fd("\x1b[31mError: Bad arguments\n\x1b[0m", 2);
		exit_error("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
	}
	return (0);
}
