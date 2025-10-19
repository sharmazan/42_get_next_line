/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:02:20 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/19 18:56:19 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

// new_line_pos = 0
// str = NULL
// try to read BUFFER_SIZE bytes
// if 0 is returned
//   return str
// new_line_pos = find_new_line
// if new_line_pos
//   str = increase_alloc(new_line_pos)
// allocate new buffer with size 1, save the byte to the buffer
// if it is \n -

char *ft_zerostring(size_t size)
{
    char *s = malloc(size);
    if (!s)
        return (NULL);
    while (size)
        s[--size] = 0;
    return (s);
}


char *get_next_line(int fd)
{
	char    *buffer;
	char    *str;
	char    *temp;
	ssize_t	bytes_read;
    char    *newline_ptr;

    buffer = ft_zerostring(BUFFER_SIZE + 1);
	int		i;
	char	c;

	i = 0;
    str = NULL;
    temp = NULL;
    // if (bytes_read < BUFFER_SIZE)
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) == BUFFER_SIZE && !(newline_ptr = ft_strchr(buffer, '\n')))
    {
        printf("Bytes read:%zd\n", bytes_read);
        printf("Buffer:%s\n", buffer);
        temp = ft_strdup(str);
        free(str);
        str = ft_strjoin(temp, buffer);
        free(temp);
        ft_memset(buffer, 0, BUFFER_SIZE);
    }
    if (bytes_read < BUFFER_SIZE)
        printf("EOF found\n");
    else
        printf("New line found\n");
    while (buffer[i] && i<bytes_read && buffer[i] != '\n')
        printf("%c", buffer[i++]);
    printf("\n");

    // if (buffer)
    //     zero_terminate(buffer);
    // return (buffer);
    // buffer = increase_buffer(buffer, bytes_read);
    // buffer[bytes_read] = c;
	// }
	// read_line_to_buffer(fd, str, sizeof(str));
    return (str);
}
/*
char *get_next_line2(int fd)
{
	static char	str[100];
	ssize_t	bytes_read;

	read_line_to_buffer(fd, str, sizeof(str));
    return (str);
    // try to read 1 byte
    // if 0 is returned
    //   if we don't have buffer - return NULL
    //   else NULL-terminate the buffer and return it
    // else (we read something)
    // allocate new buffer with size 1, save the byte to the buffer
    // if it is \n -

}
*/
int main()
{
    int fd;

    fd = open("testfile", O_RDONLY);
    printf("Descriptor:%d\n", fd);
    printf("%s\n", get_next_line(fd));
    return(0);
}
