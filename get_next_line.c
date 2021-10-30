/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:35:31 by nlouro            #+#    #+#             */
/*   Updated: 2021/10/30 23:00:21 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char *temp;
	static char *buffer;
	char *nline;
	char *ptr;
	ssize_t n;

	if (fd < 0 || fd > 100)
		return (NULL);
	temp = (char *) malloc(sizeof(char));
	if (buffer == NULL)
		buffer = (char *) malloc(sizeof(char));
	nline = (char *) malloc(sizeof(char));
	printf("DEBUG start buffer: %s\n", buffer);
	n = ft_strlen(buffer);
	printf("DEBUG n is: %zi\n", n);
	if (ft_strchr(buffer, '\n') == NULL)
	{
		while ((ptr = ft_strchr(temp, '\n')) == NULL)
		{
			n += read(fd, temp, BUFFER_SIZE);
			buffer = ft_strjoin(buffer, temp);
			//printf("DEBUG temp: %s\n", temp);
			//printf("DEBUG buffer: %s\n", buffer);
			//printf("DEBUG n bytes read: %zi\n", n);
			//if (n < BUFFER_SIZE)
			//	break;
		}
		//printf("DEBUG ptr: %p\n", ptr);
		while (buffer[n] != '\n')
			n--;
		//printf("DEBUG n is: %zi\n", n);
	}
	//printf("DEBUG buffer: %s\n", buffer);
	nline = ft_substr(buffer, 0, n);
	buffer = ft_substr(buffer, n + 1, 999);
	//printf("DEBUG last buffer: %s\n", buffer);
	return (nline);
}
