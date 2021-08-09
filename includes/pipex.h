/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:56:20 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/09 15:51:02 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"

# define PROGNAME "pipex"

void	ft_write_error_with_errno(char *str);
void	ft_write_error(char *str);
char	**get_env_directories(char *env[]);
char	*join_path(const char *dir, const char *path);
void	ft_dealloc_matrix(char **matrix);
void	connect(int *fds[], char *cmd1, char *cmd2, char *env[]);
void	make_first(int stream, int file, char *cmd, char *env[]);
void	make_last(int stream, int file, char *cmd, char *env[]);
#endif
