/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:35:31 by nlouro            #+#    #+#             */
/*   Updated: 2021/11/02 15:05:47 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_next_line(int fd)
{
	char *temp;
	static char *buffer;
	ssize_t blen;
	char *nline;
	ssize_t index;
	ssize_t tlen;

	if (fd < 0 || fd > 100 || BUFFER_SIZE < 1)
		return (NULL);
	if (buffer == NULL)
		buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	else
	{
		blen = ft_strlen(buffer);
		temp = (char *) malloc((blen + BUFFER_SIZE + 1) * sizeof(char));
	}
	//buffer = (char *) ft_realloc(buffer, blen, blen + BUFFER_SIZE);
	index = -1;
	if (ft_strchr(buffer, '\n') == NULL)
	{
		temp = (char *) malloc(BUFFER_SIZE * sizeof(char));
		tlen = 0;
		while (ft_strchr(temp, '\n') == NULL)
		{
			tlen = read(fd, temp, BUFFER_SIZE);
			buffer = ft_strjoin(buffer, temp);
			//printf("DEBUG temp: %s\n", temp);
			if (tlen <= 0)
				break;
		}
		free(temp);
	}
	index = ft_nl_index(buffer);
	//	printf("DEBUG \\n found in pos: %zi\n", index);
	if (index == -1)
	{
		free(buffer);
		return (NULL);
	}
	else
	{
		nline = (char *) malloc(sizeof(char));
		nline = ft_substr(buffer, 0, index);
		buffer = ft_substr(buffer, index + 1, ft_strlen(buffer));
		return (nline);
	}
}
