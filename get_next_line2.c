/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2022/01/27 17:48:49 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#define BUFFER_SIZE 4096

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_linelen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int ft_line_len(char *line)
{
    int    i;

    i = 0;
    while (line[i] != '\n' && line[i] != '\0')
        i++;
    return (i); 
}

char	*get_next_line(int fd)
{
	ssize_t		len;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd < 0)
		return (0);
	while ((len = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[len] = '\0';
		
	}
	return (buffer);
}

int main()
{
	int	fd;

	fd = open("TextToRead", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	return (0);
}