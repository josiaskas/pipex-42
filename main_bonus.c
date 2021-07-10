/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 21:52:51 by jkasongo          #+#    #+#             */
/*   Updated: 2021/07/10 02:19:44 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	open_files(int files[], char *path_in, char *path_out)
{
	char	*tmp;

	tmp = ft_strtrim(path_in, " ");
	files[0] = open(tmp, O_RDONLY);
	free(tmp);
	if (files[0] < 0)
		ft_write_error_with_errno(path_in);
	tmp = ft_strtrim(path_out, " ");
	files[1] = open(tmp, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRGRP \
						| S_IROTH);
	free(tmp);
	if (files[1] < 0)
		ft_write_error_with_errno(path_out);
}

int	main(int argc, char *argv[])
{
	int			i;
	int			files[2];
	int			checker;
	extern char	**environ;

	i = 0;
	if (argc < 5)
		ft_write_error("usage: ./pipex file1 cmd1 cmd2 file2");
	while (argv[i])
		i++;
	open_files(files, argv[1], argv[i - 1]);
	//
	connect(files, argv, i, environ);
	return (0);
}