/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:04:55 by tmoutinh          #+#    #+#             */
/*   Updated: 2023/06/22 18:10:05 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libs/libft.h"
# include <fcntl.h>

void	exit_error(char *message);
void	path_freer(char **paths);
char	*get_path(char **env);
char	*access_path(char **env, char **path_cmd);
void	parent_command_execution(int *fd, char **argv, char **env);
void	child_command_execution(int *fd, char **argv, char **env);
int		main(int argc, char **argv, char **env);

#endif
