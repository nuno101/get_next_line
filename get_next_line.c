/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:35:31 by nlouro            #+#    #+#             */
/*   Updated: 2021/10/31 14:41:24 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_nl_index(char *s)
{
	ssize_t	i;

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
	ssize_t blen;
	ssize_t tlen;

	if (fd < 0 || fd > 100)
		return (NULL);
	temp = (char *) malloc(sizeof(char));
	if (buffer == NULL)
		buffer = (char *) malloc(sizeof(char));
	nline = (char *) malloc(sizeof(char));
//	printf("DEBUG start buffer: %s\n", buffer);
	index = -1;
	blen = ft_strlen(buffer);
	//printf("DEBUG n is: %zi\n", n);
	if (ft_strchr(buffer, '\n') == NULL)
	{
		tlen = 0;
		while (ft_strchr(temp, '\n') == NULL)
		{
			tlen = read(fd, temp, BUFFER_SIZE);
			buffer = ft_strjoin(buffer, temp);
//			printf("DEBUG new buffer: %s\n", buffer);
			if (tlen == 0)
				break;
		}
	}
	index = ft_nl_index(buffer);
//	printf("DEBUG \\n found in pos: %zi\n", index);
//	printf("DEBUG work buffer: %s\n", buffer);
	if (index == -1)
		return (NULL);
	nline = ft_substr(buffer, 0, index);
	buffer = ft_substr(buffer, index + 1, 999);
	//printf("DEBUG last buffer: %s\n", buffer);
	return (nline);
}
