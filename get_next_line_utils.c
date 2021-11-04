/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:05:26 by nlouro            #+#    #+#             */
/*   Updated: 2021/11/04 13:21:05 by nlouro           ###   ########.fr       */
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
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	int		s1_len;
	int		s2_len;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	buffer = (char *) malloc(s1_len + s2_len + 1);
	if (!buffer)
		return (NULL);
	i = -1;
	while (i++ < s1_len)
		*(buffer + i) = *(s1 + i);
	i = 0;
	while (i < s2_len)
	{
		*(buffer + s1_len + i) = *(s2 + i);
		i++;
	}
	*(buffer + s1_len + i) = '\0';
	return (buffer);
}
*/
void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *) s;
	while (n > 0)
	{
		n--;
		ptr[n] = 0;
	}
	return ;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;

	buffer = malloc(count * size);
	if (buffer == 0)
		return (NULL);
	ft_bzero(buffer, count * size);
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
