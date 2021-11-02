/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:35:31 by nlouro            #+#    #+#             */
/*   Updated: 2021/10/31 22:29:06 by nlouro           ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	char *temp;
	static char *buffer;
	char *nline;
	ssize_t index;
	ssize_t tlen;

	if (fd < 0 || fd > 100 || BUFFER_SIZE < 1)
		return (NULL);
	if (buffer == NULL)
		buffer = (char *) malloc(sizeof(char));
//	printf("DEBUG start buffer: %s\n", buffer);
	index = -1;
	if (ft_strchr(buffer, '\n') == NULL)
	{
		temp = (char *) malloc(sizeof(char));
		tlen = 0;
		while (ft_strchr(temp, '\n') == NULL)
		{
			tlen = read(fd, temp, BUFFER_SIZE);
			buffer = ft_strjoin(buffer, temp);
			//printf("DEBUG tlen: %zd\n", tlen);
			//printf("DEBUG temp: %s\n", temp);
			//printf("DEBUG new buffer: %s\n", buffer);
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
