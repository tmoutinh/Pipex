/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:31:28 by tmoutinh          #+#    #+#             */
/*   Updated: 2023/07/01 16:58:55 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(int argc, char **argv)
{
	int		reader;
	char	*line;
	int		fd[2];

	if (argc < 6)
		exit_error("\x1b[31mInsufficient parameters\x1b[0m");
	if (pipe(fd) == -1)
		exit_error("\x1b[31m Error creating pipe\x1b[0m");
	reader = fork();
	if (reader == -1)
		exit_error("\x1b[31m Error on the fork\x1b[0m");
	if (reader == 0)
	{
		line = get_next_line(0);
		while (line)
		{
			close(fd[0]);
			if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
			line = get_next_line(0);
		}
	}
	else
		extra(fd[0], fd[1]);
}

void	open_checker(int fd, char *message)
{
	if (fd == -1)
		exit_error(message);
}

void	initializer(char **argv, int argc, char **env)
{
	int	infile;
	int	outfile;
	int	first_cmd;

	if (ft_strncmp("here_doc", argv[1], ft_strlen("here_doc")) == 0)
	{
		first_cmd = 2;
		here_doc(argc, argv);
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		open_checker(outfile, "\x1b[31mError opening files\x1b[0m");
	}
	else
	{
		first_cmd = 1;
		infile = open(argv[1], O_RDONLY, 0777);
		open_checker(infile, "\x1b[31mError opening files\x1b[0m");
		dup2(infile, STDIN_FILENO);
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		open_checker(outfile, "\x1b[31mError opening files\x1b[0m");
	}
	while (++first_cmd < argc - 2)
		child_command_execution(argv[first_cmd], env);
	dup2(outfile, STDOUT_FILENO);
	executer(argv[first_cmd], env, outfile, "Error: Parent not executed");
}

int	main(int argc, char **argv, char **env)
{
	if (argc >= 5)
		initializer(argv, argc, env);
	else
		exit_error("\x1b[31mError incorrect arguments\n\x1b[0m");
	return (0);
}
