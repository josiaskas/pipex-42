/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:54:53 by jkasongo          #+#    #+#             */
/*   Updated: 2021/07/08 19:55:16 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_write_error_with_errno(char *str)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	if (str)
	{
		write(STDERR_FILENO, ": ", 3);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

void	ft_write_error(char *str)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	exit(1);
}

char	**get_env_directories(char *env[])
{
	char	**directories;
	char	*path_env;
	int		i;

	i = 0;
	directories = NULL;
	if (!env || !*env)
	{
		directories = (char **)malloc(sizeof(char *) * 1);
		if (!directories)
			return (0);
		*directories = NULL;
		return (directories);
	}
	while (env[i] != NULL)
	{
		path_env = ft_strnstr(env[i], "PATH", 5);
		if (path_env)
		{
			directories = ft_split((path_env + 5), ':');
			break ;
		}
		i++;
	}
	return (directories);
}

char	*join_path(const char *dir, const char *path)
{
	char	*str;
	size_t	size;
	size_t	i;

	if (dir == 0 || path == 0)
		return (0);
	size = ft_strlen(dir) + ft_strlen(path) + 1;
	str = (char *)malloc(size + 1);
	i = 0;
	while (*dir)
		str[i++] = *dir++;
	str[i++] = '/';
	while (*path)
		str[i++] = *path++;
	str[i] = 0;
	return (str);
}

void	ft_dealloc_matrix(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
