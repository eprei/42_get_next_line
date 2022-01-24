/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2022/01/24 16:00:27 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 500

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
	char		*dst;
    char        *tmp;
    static int  i = 0;
    int         j;

    j = 0;
	len = read(fd, buffer, BUFFER_SIZE);
	buffer[len] = '\0';
    tmp = dst;
    while (buffer[i] != '\n')
    {
        dst[j] = buffer[i];
        i++;
        j++;
    }
	dst[j] = '\0';
    return (tmp);
}

int main()
{
	int	fd;
	char *linea = NULL;

	fd = open("TextToRead", O_RDONLY);
	linea = get_next_line(fd);
	printf("%s\n", linea);
	linea = get_next_line(fd);
	printf("%s\n", linea);
	return (0);
}