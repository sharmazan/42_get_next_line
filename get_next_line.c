/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:02:20 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/27 20:17:27 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

// ALGO:
// if fd < 0 -> return NULL
// if not \n in storage: read in loop
//   read from file BUFFER_SIZE bytes to buffer
//   if error (bytes_read == -1 -> return NULL)
//   increase storage, save buffer to storage
//   if bytes_read < BUFFER_SIZE: break ;
// if \n in storage: return substr with \n, store everything else to storage
// else return storage

// TODO
// save fd and storage in a linked list to read from several files

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
	while (srclen--)
		str[srclen] = temp[srclen];
	free(*src);
	*src = str;
	return (free(temp), str);
}

char	*get_line(char **str)
{
	char	*buf;
	char	*temp;
	size_t	i;

	i = 0;
	if (!*str)
		return (NULL);
	while ((*str)[i])
		if ((*str)[i++] == '\n')
			break ;
	if (i == ft_strlen(*str))
	{
		buf = ft_strdup(*str);
		free(*str);
		*str = NULL;
		return (buf);
	}
	buf = ft_substr(*str, 0, i);
	temp = ft_substr(*str, i, ft_strlen(*str));
	if (!buf || !temp)
		return (free(buf), free(temp), NULL);
	free(*str);
	*str = temp;
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*buffer;
	ssize_t		bytes_read;

	buffer = ft_zerostring(BUFFER_SIZE + 1);
	if (fd < 0 || !buffer)
		return (NULL);
	while (!ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
		if (!ft_realloc_str(&storage, bytes_read))
			return (free(storage), free(buffer), NULL);
		ft_strlcat(storage, buffer, ft_strlen(storage) + bytes_read + 1);
		if (bytes_read < BUFFER_SIZE)
			break ;
		while (bytes_read--)
			buffer[bytes_read] = 0;
	}
	return (free(buffer), get_line(&storage));
}
