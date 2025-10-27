/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:02:20 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/27 20:14:45 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*str;

	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = 0;
	printf("File descriptor: %d\n", fd);
	for (int i = 0; i < 10; i++)
	{
		printf("\nline %d:", i);
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	}
	return (0);
}
