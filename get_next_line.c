/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:35:31 by nlouro            #+#    #+#             */
/*   Updated: 2021/11/12 15:57:51 by nlouro           ###   ########.fr       */
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

/*
 * return NULL if fd is invalid or BUFFER_SIZE smaller than 1 byte
 * initialise static variable buffer if NULL. ,i.e, first execution
 * while no newline find in buffer
 * read_file until \n is found, the file end is reached or an error occurs
 */
char	*get_next_line(int fd)
{
	static char	*buffer;
	ssize_t		blen;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (buffer == NULL)
		buffer = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (ft_strchr(buffer, '\n') == NULL)
	{
		blen = ft_strlen(buffer);
		bytes_read = read_file(fd, &buffer, blen);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read < BUFFER_SIZE)
			break ;
	}
	blen = ft_strlen(buffer);
	if (blen == 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (split_next_line(&buffer, blen));
}

/*
 * read BUFFER_SIZE bytes from fd into temp
 * concatenate temp into buffer
 * increase memory allocation as needed
 */
ssize_t	read_file(int fd, char **buffer, ssize_t blen)
{
	char	*temp;
	ssize_t	bytes_read;

	if (blen > 0)
	{
		temp = (char *) ft_calloc(blen + BUFFER_SIZE + 1, sizeof(char));
		ft_strlcat(temp, *buffer, blen + 1);
		free(*buffer);
		*buffer = temp;
	}
	temp = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
	else if (bytes_read > 0)
		ft_strlcat(*buffer, temp, blen + bytes_read + 2);
	free(temp);
	return (bytes_read);
}

/*
 * return first nextline from buffer 
 * shorten buffer accordingly
 */
char	*split_next_line(char **buffer, ssize_t blen)
{
	ssize_t	index;
	char	*temp;
	char	*nline;

	index = ft_nl_index(*buffer);
	if (index == -1)
	{
		nline = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		return (nline);
	}
	nline = ft_substr(*buffer, 0, index + 1);
	if (index + 1 < blen)
	{
		temp = ft_substr(*buffer, index + 1, blen + 1);
		free(*buffer);
		*buffer = temp;
	}
	else
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (nline);
}
