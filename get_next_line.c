/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:35:31 by nlouro            #+#    #+#             */
/*   Updated: 2021/10/15 15:38:38 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char *temp;
	static char *buffer;
	ssize_t n;

	if (fd < 0 || fd > 100)
		return (NULL);
	temp = (char *) malloc(BUFFER_SIZE * sizeof(char));
	buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));
	n = read(fd, buffer, BUFFER_SIZE);
	printf("DEBUG: %ld bytes read", n);

	return (buffer);
}
