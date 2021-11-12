/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:05:26 by nlouro            #+#    #+#             */
/*   Updated: 2021/11/12 18:13:47 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		else
			s++;
	}
	if (c == '\0' && *s == '\0')
		return ((char *)s);
	else
		return (NULL);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

/*
 * this version of ft_calloc does not depend/call ft_bzero
 * to cope with the norm the ft_bzero call was replaced by its code
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;
	char	*ptr;
	size_t	n;

	n = count * size;
	buffer = malloc(n);
	ptr = (char *) buffer;
	if (buffer == 0)
		return (NULL);
	while (n > 0)
	{
		n--;
		ptr[n] = 0;
	}
	return (buffer);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buffer;
	int		i;

	if (s == 0)
		return (0);
	if (start >= (unsigned int)ft_strlen(s))
	{
		buffer = (char *) ft_calloc(1, 1);
		if (buffer == 0)
			return (0);
		return (buffer);
	}
	buffer = (char *)malloc((len - start + 1) * sizeof(char));
	if (buffer == 0)
		return (0);
	i = 0;
	while ((size_t) i < len && *(s + start + i) != '\0')
	{
		buffer[i] = *(s + start + i);
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*buffer;

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
