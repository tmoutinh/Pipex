/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:31:28 by tmoutinh          #+#    #+#             */
/*   Updated: 2023/06/09 20:11:40 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//This function will get the path
char	*get_path(char **env)
{
	int		i;
	char	*path;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = env[i] + 5;
	}
	return (path);
}
/*This function will take the env and extract the path and join it 
with / and the initial portion of the command*/
char	*access_path(char *cmd, char **env, char **path_cmd)
{
	int	i;
	char	*path;
	char	*temp_path;
	char	**paths;
	
	path = get_path(env);
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp_path, path_cmd[0]);
		free(temp_path);
		if (access(path, F_OK) == 0)
			return(path);
		free(path);
	}
	i = -1;
	while(paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
	
}

void	parent_command_execution(int *fd, char **argv, char **env)
{
	char	*path;
	int		file;
	char	**cmd;

	cmd = ft_split(argv[3], ' ');
	path = access_path(argv[3], env, cmd);
	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		perror("\x1b[31mError opening file\x1b[0m");
	if (path)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
		close(fd[1]);
		execve(path, cmd, env);
	}
	else
		perror("\x1b[31mNot valid command\x1b[0m");
}

void	child_command_execution(int *fd, char **argv, char **env)
{
	char	*path;
	int		file;
	char	**cmd;

	cmd = ft_split(argv[2], ' ');
	path = access_path(argv[2], env, cmd);
	file = open(argv[1], O_RDONLY, 0777);
	if (file == -1)
		perror("\x1b[31mError opening file\x1b[0m");
	if (path)
	{
		dup2(fd[1], STDOUT_FILENO);
		dup2(file, STDIN_FILENO);
		close(fd[0]);
		perror("ok\n");
		//execve(path, cmd, env);
	}
	else
		perror("\x1b[31mNot valid command\x1b[0m");
}

int main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	if (argc == 5)
	{
		pid = fork();
		if (pid == 0)
		{
			//Child Process
			child_command_execution(fd, argv, env); 
		}
		else
		{
			waitpid(pid, NULL, 0);
			//Parent Process
			parent_command_execution(fd, argv, env);
		}
	}
	else
	{
		ft_putstr_fd("\x1b[31mError: Bad arguments\n\x1b[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}