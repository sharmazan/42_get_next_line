/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:02:20 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/19 18:59:02 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*read_line_to_buffer(int fd, char *buffer, int buffer_size)
{
	int		i;
	char	c;
	ssize_t	bytes_read;

	i = 0;
	while (i < buffer_size - 1)
	{
		bytes_read = read(fd, &c, 1);
		if (bytes_read <= 0 || c == '\n')
			break ;
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';
	if (i > 0 || bytes_read > 0)
		return (buffer);
	else
		return (NULL);
}


char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}


char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p)
	{
		if (*p == (unsigned char)c)
			return (p);
		p++;
	}
	if (*p == (unsigned char)c)
		return (p);
	else
		return (NULL);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;

	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (*s1)
		p[i++] = *s1++;
	while (*s2)
		p[i++] = *s2++;
	p[i] = 0;
	return (p);
}


void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	if (n == 0)
		return (s);
	i = 0;
	p = (char *)s;
	while (i < n)
		p[i++] = (unsigned char)c;
	return (s);
}


size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
