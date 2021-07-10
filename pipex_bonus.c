/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 21:52:08 by jkasongo          #+#    #+#             */
/*   Updated: 2021/07/10 02:16:58 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_execve(char **dirs, char **args, char **env)
{
	char	*tmp;
	int		i;

	tmp = 0;
	i = 0;
	tmp = ft_strtrim(args[0], " ");
	free(args[0]);
	args[0] = tmp;
	tmp = ft_strrchr(args[0], '/');
	if (tmp)
		execve(args[0], args, env);
	while (dirs[i])
	{
		if (args[0][0] != '/')
			tmp = join_path(dirs[i], args[0]);
		else
			tmp = args[0];
		execve(tmp, args, env);
		free(tmp);
		++i;
	}
}

void	make_first(int stream, int file, char *cmd, char *env[])
{
	char	**args;
	char	**dirs;

	args = ft_split(cmd, 32);
	dirs = get_env_directories(env);
	if (dirs == NULL)
		ft_write_error("error: can't get PATH environment variable");
	dup2(stream, STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(file);
	close(stream);
	ft_execve(dirs, args, env);
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putendl_fd(args[0], STDERR_FILENO);
	ft_dealloc_matrix(dirs);
	ft_dealloc_matrix(args);
	exit(127);
}

void	make_last(int stream, int file, char *cmd, char *env[])
{
	char	**args;
	char	**dirs;

	args = ft_split(cmd, 32);
	dirs = get_env_directories(env);
	if (dirs == NULL)
		ft_write_error("error: can't get PATH environment variable");
	dup2(file, STDOUT_FILENO);
	dup2(stream, STDIN_FILENO);
	close(file);
	close(stream);
	ft_execve(dirs, args, env);
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putendl_fd(args[0], STDERR_FILENO);
	ft_dealloc_matrix(dirs);
	ft_dealloc_matrix(args);
	exit(127);
}

void	make_inside_call(int readeable, int writeable, char *cmd, char *env[])
{
	char	**args;
	char	**dirs;

	args = ft_split(cmd, 32);
	dirs = get_env_directories(env);
	if (dirs == NULL)
		ft_write_error("error: can't get PATH environment variable");
	dup2(writeable, STDOUT_FILENO);
	dup2(readeable, STDIN_FILENO);
	close(writeable);
	close(readeable);
	ft_execve(dirs, args, env);
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putendl_fd(args[0], STDERR_FILENO);
	ft_dealloc_matrix(dirs);
	ft_dealloc_matrix(args);
	exit(127);
}
