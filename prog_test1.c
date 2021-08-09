/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_test1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:57:39 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/09 15:57:40 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(char *str)
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

int	main(int argc, char *argv[])
{
	int		len;
	char	buffer[400] = {0};
	int		rtn;

	len = 0;
	rtn = 0;
	while (argc > 1)
	{
		len = ft_strlen(argv[argc - 1]);
		write(STDOUT_FILENO, argv[argc - 1], len);
		argc--;
	}
	rtn = read(STDIN_FILENO, buffer, 399);
	buffer[rtn] = 0;
	write(STDOUT_FILENO, "\n>>>prog1\n", 11);
	write(STDOUT_FILENO, buffer, rtn);
	write(STDOUT_FILENO, "\n<<<end\n", 9);
	return (0);
}
