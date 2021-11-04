/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:35:31 by nlouro            #+#    #+#             */
/*   Updated: 2021/11/03 19:22:26 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * find the position of the first newline within a given string
 * return its position or -1 if none found
 */

ssize_t	ft_nl_index(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		return (i);
	else
		return (-1);
}

void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    char    *ptr_d;
    char    *ptr_s;

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
	void *nptr;

	if (nlen == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
		return malloc(nlen);
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

/*
 * reads BUFFER_SIZE bytes from a given file descriptor into temp
 *
 */
char	*get_next_line(int fd)
{
	char *temp;
	static char *buffer;
	ssize_t blen;
	char *nline;
	ssize_t index;
	ssize_t bytes_read;

	if (fd < 0 || fd > 100 || BUFFER_SIZE < 1)
		return (NULL);
	if (buffer == NULL)
		buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
 
	while (ft_strchr(buffer, '\n') == NULL)
	{
		blen = ft_strlen(buffer);
		buffer = (char *) realloc(buffer, (blen + BUFFER_SIZE + 1) * sizeof(char));
		if (buffer == NULL)
			return (NULL);
		temp = (char *) malloc(BUFFER_SIZE * sizeof(char));
		if (temp == NULL)
			return (NULL);
		bytes_read = read(fd, temp, BUFFER_SIZE);
		// todo: if no newline found during read, the buffer size must be increased before strjoin is called
		buffer = ft_strjoin(buffer, temp);
		free(temp);
		if (bytes_read <= 0)
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
		nline = (char *) malloc((index + 1) * sizeof(char));
		if (nline == NULL)
			return (NULL);
		nline = ft_substr(buffer, 0, index);
		buffer = ft_substr(buffer, index + 1, ft_strlen(buffer));
		return (nline);
	}
}
