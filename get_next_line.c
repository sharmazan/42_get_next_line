/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:02:20 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/21 19:04:33 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ALGO:
// if fd < 0 -> return NULL
// if not \n in storage: read in loop
//   read from file BUFFER_SIZE bytes to buffer
//   if error (bytes_read == -1 -> return NULL)
//   increase storage, save buffer to storage
//   if bytes_read < BUFFER_SIZE: break; 
// if \n in storage: return substr with \n, store everything else to storage
// else return storage

// Handled:
// not existing fd==-1 - return null
// zero-file - return null
// BUFFER_SIZE in the file - return BUFFER_SIZE bytes + 0 in the end
// more then BUFFER_SIZE - return the string
// TODO
// save the rest of the buffer after reaching a new_line to continue reading later

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

char	*ft_realloc_str(char **src, size_t size)
{
	char	*temp;
	char	*str;
	size_t	srclen;
	
	if (!*src)
	{
		*src = ft_zerostring(size + 1);
		return (*src);
	}
	temp = ft_strdup(*src);
	if (!temp)
		return (NULL);
	srclen = ft_strlen(temp);
	str = ft_zerostring(srclen + size + 1);
	if (!str)
		return (free(temp), NULL);
	ft_memcpy(str, temp, srclen);
	free(*src);
	*src = str;
	return (free(temp), str);
}

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

char	*get_line(char **str)
{
	char	*buf;
	char	*temp;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(*str);
	while (*str[i] != 0 || *str[i] != '\n')
		i++;
	if (i = len)
		return (*str);
	buf = ft_substr(*str, 0, i);
	if (!buf)
		return (NULL);
	temp = ft_substr(*str, i, len);
	if (!temp)
		return (NULL);
	free(*str);
	*str = temp;
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char	*buffer;
	ssize_t	bytes_read;
	ssize_t	bytes_to_copy;
	char	*newline_ptr;

	buffer = ft_zerostring(BUFFER_SIZE + 1);
	if (fd < 0 || !buffer)
		return (NULL);
	while (!ft_strchr(storage, '\n'))
	{
		printf("Reading from file\n");
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		printf("Bytes read:%zd\n", bytes_read);
		printf("Buffer:%s\n", buffer);
		if (bytes_read == 0)
			return (free(buffer), storage);
		// if (bytes_read < BUFFER_SIZE)
		// 	printf("EOF found\n");
		if (!ft_realloc_str(&storage, bytes_read))
			return (free(storage), free(buffer), NULL);
		printf("Copy buffer to str\n");
		ft_strlcat(storage, buffer, ft_strlen(storage) + bytes_read + 1);
		printf("storage now:%s\n", storage);
		if (bytes_to_copy < BUFFER_SIZE)
			break ;
		ft_memset(buffer, 0, BUFFER_SIZE);
	}
	return (free(buffer), get_line(&storage));
}

int	main(int ac, char **av)
{
	int		fd;
	char	*str;

	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("testfile", O_RDONLY);
	printf("%d\n", fd);
	str = get_next_line(fd);
	printf("-----------------------------------------\n");
	printf("%s", str);
	printf("-----------------------------------------\n");
	free(str);
	// str = get_next_line(fd);
	// printf("-----------------------------------------\n");
	// printf("%s", str);
	// printf("-----------------------------------------\n");
	// free(str);
	// str = get_next_line(fd);
	// printf("-----------------------------------------\n");
	// printf("%s", str);
	// printf("-----------------------------------------\n");
	// free(str);
	return (0);
}
