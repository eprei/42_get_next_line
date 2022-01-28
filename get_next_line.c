/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2022/01/25 18:32:38 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "get_next_line.h"
#define BUFFER_SIZE 100

int ft_line_len(char *str)
{
    int    i;

    i = 0;
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    return (i); 
}

char	*get_next_line(int fd)
{
	int			len;
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;
	char		*line;
	static int	i = 0;
	int			j;

	i = 0;
	read(fd, buffer, BUFFER_SIZE);
	len = ft_line_len(buffer);
	buffer[len] = '\0';
	str = (char *)malloc(len + 1);
	if (! str)
		return (0);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		str[j++] = buffer[i++];
	str[j] = '\0';
	i++;
	return (str);
}

int main()
{
	int	fd;
	char *linea = NULL;

	fd = open("hola", O_RDONLY);
	linea = get_next_line(fd);
	printf("%s\n", linea);
	linea = get_next_line(fd);
	printf("%s\n", linea);
	return (0);
}