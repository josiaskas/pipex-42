/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:12:42 by jkasongo          #+#    #+#             */
/*   Updated: 2021/07/06 03:52:19 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (*str != 0)
	{
		str++;
		len++;
	}
	return (len);
}

void	ft_write_error(const char *str)
{
	char	*message;

	message = strerror(errno);
	write(STDERR_FILENO, "pipex: ", 7);
	write(STDERR_FILENO, message, ft_strlen(message));
	if (str)
	{
		write(STDERR_FILENO, ": ", 3);
		write(STDERR_FILENO, str, ft_strlen(str));
	}
	write(STDERR_FILENO, "\n", 1);
}

static char	*ft_strndup_local(const char *s1, size_t n)
{
	char	*heap_p;
	char	*p;

	heap_p = malloc(n + 1);
	if (!heap_p)
		return (0);
	p = heap_p;
	while ((*s1 != 0) && (n--))
		*p++ = *s1++;
	*p = '\0';
	return (heap_p);
}

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (*s != 0)
	{
		if ((*s == c) && (i == 0))
			s++;
		if ((*s == c) && (i != 0))
		{
			count++;
			i = 0;
		}
		if ((*s != c))
			i++;
		s++;
	}
	return (count);
}

static void	ft_splitter(char **words, char const *s, char c)
{
	size_t	nbr_words;
	size_t	i;

	nbr_words = 0;
	i = 0;
	while ((*s) != 0)
	{
		if ((*s == c) && (i == 0))
			s++;
		if ((*s == c) && (i != 0))
		{
			words[nbr_words++] = ft_strndup_local((s - i), i);
			i = 0;
		}
		if ((*s != c))
			i++;
		s++;
	}
	if (i != 0)
		words[nbr_words++] = ft_strndup_local((s - i), i);
	words[nbr_words] = 0;
}

char	**ft_split(char const *s, char c)
{
	size_t	nbr_words;
	char	**words;

	if (!s || !*s)
	{
		words = (char **)malloc(sizeof(char *) * 1);
		if (!words)
			return (0);
		*words = (void *)0;
		return (words);
	}
	nbr_words = count_words(s, c) + 1;
	words = (char **)malloc(sizeof(char *) * (nbr_words + 1));
	if (!words)
		return (0);
	ft_splitter(words, s, c);
	return (words);
}

void	make_first_proccess(int pipe[], char *args[], int file, char *env[])
{
	pid_t	pid;
	int		check_pipe;
	int		check_file;
	char	*path;

	pid = fork();
	path = args[0];
	if (pid == 0)
	{
		check_pipe = dup2(pipe[1], STDOUT_FILENO);
		check_file = dup2(file, STDIN_FILENO);
		if ((check_pipe < 0) || (check_file < 0))
		{
			ft_write_error(0);
			exit(1);
		}
		close(file);
		close(pipe[0]);
		close(pipe[1]);
		check_pipe = execve(path, args, env);
		if (check_pipe < 0)
			ft_write_error(0);
		exit(127);
	}
	waitpid(pid, NULL, 0);
}

void	make_last_proccess(int pipe[], char *args[], int file, char *env[])
{
	pid_t	pid;
	int		check_pipe;
	int		check_file;
	char	*path;

	pid = fork();
	path = args[0];
	if (pid == 0)
	{
		check_pipe = dup2(pipe[0], STDIN_FILENO);
		check_file = dup2(file, STDOUT_FILENO);
		if ((check_pipe < 0) || (check_file < 0))
		{
			ft_write_error(0);
			exit(1);
		}
		close(file);
		close(pipe[0]);
		close(pipe[1]);
		check_pipe = execve(path, args, env);
		if (check_pipe < 0)
			ft_write_error(0);
		exit(127);
	}
	waitpid(pid, NULL, 0);
}

void	connect(int *fds[], char *cmd1, char *cmd2, char *env[])
{
	char	**args1;
	char	**args2;
	int		*pipe;
	int		*files;

	pipe = fds[1];
	files = fds[0];
	args1 = ft_split(cmd1, 32);
	args2 = ft_split(cmd2, 32);
	make_first_proccess(pipe, args1, files[0], env);
	make_last_proccess(pipe, args2, files[1], env);
	close(files[0]);
	close(files[1]);
	close(pipe[0]);
	close(pipe[1]);
}

void	open_files(int files[], const char *path_in, const char *path_out)
{
	files[0] = open(path_in, O_RDONLY);
	if (files[0] < 0)
	{
		ft_write_error(path_in);
		exit(1);
	}
	files[1] = open(path_out, O_WRONLY | O_CREAT, 0700);
	if (files[1] < 0)
	{
		ft_write_error(path_out);
		exit(1);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	files[2];
	int	stream[2];
	int	*fds[2];
	int	checker;

	if (argc == 5)
	{
		checker = pipe(stream);
		if (checker < 0)
		{
			ft_write_error(0);
			return (1);
		}
		open_files(files, argv[1], argv[4]);
		fds[0] = files;
		fds[1] = stream;
		connect(fds, argv[2], argv[3], envp);
	}
	return (0);
}
