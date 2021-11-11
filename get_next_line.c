/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:35:31 by nlouro            #+#    #+#             */
/*   Updated: 2021/11/11 16:28:09 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * find the position of the first newline within a given string
 * return its position or -1 if none found
 */

ssize_t	ft_nl_index(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		return (i);
	else
		return (-1);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	dst_len = (size_t) ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	if (dstsize < dst_len)
		return (src_len + dstsize);
	while ((dst_len + i < dstsize) && *(src + i) != '\0')
	{
		*(dst + dst_len + i) = *(src + i);
		i++;
	}
	if (dst_len < dstsize && dst_len + i == dstsize)
		*(dst + dst_len + i - 1) = '\0';
	else
		*(dst + dst_len + i) = '\0';
	return (dst_len + src_len);
}

/* return NULL if fd is invalid or BUFFER_SIZE smaller than 1 byte
 * initialise static variable buffer if NULL. i,.e, first execution
 * return NULL if malloc fails to allocate the requested memory
 * while no newline find
 *  check the lenght of the buffer content
 *  reallocate additional BUFFER_SIZE + 1 bytes of memory if buffer not empty
 *  reads BUFFER_SIZE bytes from a given file descriptor into temp
 *  concatenate temp into buffer using strjoin and free temp
 *  exit the while look if nr of bytes read is less than requested or read function returns an error
 * find index of newline in buffer
 *  return NULL if none
 *  allocate index + 2 bytes for next line in buffer
 *
 */
char	*get_next_line(int fd)
{
	char	*tmp;
	char	*temp;
	char	*temp2;
	static char	*buffer;
	ssize_t	blen;
	char	*nline;
	ssize_t	index;
	ssize_t	bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (buffer == NULL)
	{
		buffer = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	}
	while (ft_strchr(buffer, '\n') == NULL)
	{
		blen = ft_strlen(buffer);
		if (blen > 0)
		{
			// no newline found during read => buffer size must be increased before strlcat
			tmp = (char *) ft_calloc(blen + BUFFER_SIZE + 1, sizeof(char));
			ft_strlcat(tmp, buffer, blen + 1);
			free(buffer);
			buffer = tmp;
		}
		temp = (char *) ft_calloc(BUFFER_SIZE, sizeof(char));
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(temp);
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		else if (bytes_read > 0)
		{
			ft_strlcat(buffer, temp, blen + bytes_read + 1);
		}
		free(temp);
		if (bytes_read < BUFFER_SIZE)
			break;
	}
	blen = ft_strlen(buffer);
	if (blen == 0)
	{
		// causing errors like: "pointer being freed was not allocated"
		if (buffer != NULL)
			free(buffer);
		return (NULL);
	}
	index = ft_nl_index(buffer);
	if (index == -1)
	{
		nline = ft_strdup(buffer);
		free(buffer);
		buffer = NULL;
		return (nline);
	}
	nline = ft_substr(buffer, 0, index + 1);
	if (index + 1 < blen)
	{
		temp2 = ft_substr(buffer, index + 1, blen);
		free(buffer);
		buffer = temp2;
	}
	else
	{
		free(buffer);
		buffer = NULL;
	}
	return (nline);
}

char    *ft_strdup(const char *s1)
{
    size_t  i;
    size_t  len;
    char    *buffer;

    len = ft_strlen(s1);
    buffer = malloc(len + 1);
    if (buffer == 0)
        return (NULL);
    i = 0;
    while (*(s1 + i) && i < len)
    {
        *(buffer + i) = *(s1 + i);
        i++;
    }
    *(buffer + i) = '\0';
    return (buffer);
}
