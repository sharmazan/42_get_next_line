/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:02:20 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/19 20:49:21 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// TODO
// save the buffer left after the new_line to continue reading

char	*ft_zerostring(size_t size)
{
	char	*s;

	s = malloc(size);
	if (!s)
		return (NULL);
	while (size)
		s[--size] = 0;
	return (s);
}

char	*increase_str(char **src, size_t size)
{
	char	*temp;
	char	*str;
	size_t	i;
	size_t	srclen;

	if (*src)
	{
		temp = ft_strdup(*src);
		if (!temp)
			return (NULL);
		srclen = ft_strlen(temp);
	}
	str = ft_zerostring(srclen + size + 1);
	if (!str)
		return (free(temp), NULL);
	i = 0;
	while (i < srclen)
	{
		str[i] = temp[i];
		i++;
	}
	free(*src);
	free(temp);
	*src = str;
	return (str);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*str;
	ssize_t	bytes_read;
	ssize_t	bytes_to_copy;
	char	*newline_ptr;
	int		i;
	char	c;

	buffer = ft_zerostring(BUFFER_SIZE + 1);
	i = 0;
	str = NULL;
	while (1)
	{
		printf("Reading from file\n");
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		newline_ptr = ft_strchr(buffer, '\n');
		printf("Bytes read:%zd\n", bytes_read);
		printf("Buffer:%s\n", buffer);
		if (bytes_read < BUFFER_SIZE)
			printf("EOF found\n");
		if (newline_ptr)
		{
			printf("New line found\n");
			bytes_to_copy = newline_ptr - buffer + 1;
		}
		else
			bytes_to_copy = bytes_read;
		if (str)
		{
			printf("Increasing str\n");
			if (!increase_str(&str, bytes_to_copy + 1))
				return (free(str), free(buffer), NULL);
		}
		else
		{
			printf("Allocating %zd bytes to str\n", bytes_to_copy + 1);
			str = ft_zerostring(bytes_to_copy + 1);
		}
		printf("Copy buffer to str\n");
		ft_strlcat(str, buffer, ft_strlen(str) + bytes_to_copy + 1);
		printf("str now:%s\n", str);
		if (bytes_to_copy < BUFFER_SIZE)
			break ;
		ft_memset(buffer, 0, BUFFER_SIZE);
	}
	free(buffer);
	return (str);
}

int	main(void)
{
	int	fd;

	fd = open("testfile", O_RDONLY);
	printf("Descriptor:%d\n", fd);
	printf("%s\n", get_next_line(fd));
	return (0);
}
