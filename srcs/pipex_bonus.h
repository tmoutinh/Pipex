/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:04:55 by tmoutinh          #+#    #+#             */
/*   Updated: 2023/06/25 13:41:20 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libs/libft.h"
# include <fcntl.h>

void	exit_error(char *message);
void	path_freer(char **paths);
char	*get_path(char **env);
char	*access_path(char **env, char **path_cmd);
void	parent_command_execution(char *cmd_passed, char **env);
void	child_command_execution(char *cmd_passed, char **env);
int		main(int argc, char **argv, char **env);
void	extra(int fd_0, int fd_1, int pid);
void	executer(char *cmd_passed, char **env, int file, char *message);
void	initializer(char **argv, int argc, char **env);

#endif
