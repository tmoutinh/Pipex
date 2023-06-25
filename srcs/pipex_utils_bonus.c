/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:06:25 by tmoutinh          #+#    #+#             */
/*   Updated: 2023/06/25 20:11:28 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	extra(int fd_0, int fd_1, int pid)
{
	close(fd_1);
	dup2(fd_0, STDIN_FILENO);
	waitpid(pid, NULL, 0);
}

void	exit_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

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

void	path_freer(char **paths)
{
	int	i;

	i = -1;
		i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}

/*This function will take the env and extract the path and join it 
with / and the initial portion of the command*/
char	*access_path(char **env, char **path_cmd)
{
	int		i;
	char	*path;
	char	*temp_path;
	char	**paths;

	paths = ft_split(get_path(env), ':');
	i = -1;
	while (paths[++i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp_path, path_cmd[0]);
		free(temp_path);
		if (access(path, F_OK) == 0)
		{
			path_freer(paths);
			return (path);
		}
		free(path);
	}
	path_freer(paths);
	return (NULL);
}
