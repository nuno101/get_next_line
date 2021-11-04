/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:35:31 by nlouro            #+#    #+#             */
/*   Updated: 2021/11/04 17:48:08 by nlouro           ###   ########.fr       */
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (*(src + i) && i < dstsize - 1)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (src_len);
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*ptr_d;
	char	*ptr_s;

	if (dst == (void *)0 && src == (void *)0)
		return ((void *)0);
	ptr_d = dst;
	ptr_s = (char *)src;
	while (n > 0)
	{
		*ptr_d = *ptr_s;
		n--;
		ptr_d++;
		ptr_s++;
	}
	return (dst);
}

void	*ft_realloc(void *ptr, size_t olen, size_t nlen)
{
	void	*nptr;

	if (nlen == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
		return (malloc(nlen));
	else if (nlen <= olen)
		return (ptr);
	else
	{
		nptr = malloc(nlen);
		if (nptr)
		{
			ft_memcpy(nptr, ptr, olen);
			free(ptr);
		}
		return (nptr);
	}
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
	char	*temp;
	//char	*temp2;
	static char	*buffer;
	ssize_t	blen;
	char	*nline;
	ssize_t	index;
	ssize_t	bytes_read;

	if (fd < 0 || fd > 100 || BUFFER_SIZE < 1)
		return (NULL);
	if (buffer == NULL)
		buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (ft_strchr(buffer, '\n') == NULL)
	{
		blen = ft_strlen(buffer);
		if (blen > 0)
		{
			// no newline found during read
			// the buffer size must be increased before strjoin is called again
			buffer = (char *) realloc(buffer, (blen + BUFFER_SIZE + 1) * sizeof(char));
			if (buffer == NULL)
				return (NULL);
		}
		temp = (char *) malloc(BUFFER_SIZE * sizeof(char));
		if (temp == NULL)
			return (NULL);
		bytes_read = read(fd, temp, BUFFER_SIZE);
		//buffer = ft_strjoin(buffer, temp);
		ft_strlcat(buffer, temp, blen + bytes_read + 1);
		free(temp);
		if (bytes_read < BUFFER_SIZE)
			break;
	}
	index = ft_nl_index(buffer);
	if (index == -1)
	{
		free(buffer);
		return (NULL);
	}
	else
	{
		nline = ft_substr(buffer, 0, index);
		blen = ft_strlen(buffer);
		buffer = ft_substr(buffer, index + 1, blen);
		// the buffer size must be decreased by index + 1 bytes
		//buffer = (char *) realloc(buffer, (blen - (index + 1)) * sizeof(char));
		//ft_strlcpy(buffer, temp2, blen - (index + 1));
		//free(temp2);
		return (nline);
	}
}
