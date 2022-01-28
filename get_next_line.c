/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2022/01/28 16:47:38 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	size_copy;

	if (!s)
		return (NULL);
	else if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s) - start)
		size_copy = ft_strlen(s) - start;
	else
		size_copy = len;
	substr = malloc(sizeof(char) * (size_copy + 1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len && i < size_copy)
	{
		substr[i] = *(s + start + i);
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

void	cut_line_and_offset(char **line_cuted, char **line_to_cut_and_offset)
{
	size_t	line_size;
	char	*tmp;

	line_size = line_len(*line_to_cut_and_offset);
	tmp = ft_substr(*line_to_cut_and_offset, 0, line_size + 1);
	*line_cuted = tmp;
	tmp = ft_strdup(&((*line_to_cut_and_offset)[line_size + 1]));
	*line_to_cut_and_offset = tmp;
	tmp = NULL;
}

char	*get_next_line(int fd)
{
	ssize_t		ret;
	char		buf[BUFFER_SIZE + 1];
	static char	*raw_line;
	char		*tmp;
	char		*line_return;

	if (fd < 0)
		return (0);
	while ((ret = read(fd, buf, BUFFER_SIZE)))
	{
		buf[ret] = '\0';
		if (ret < 0)
			return (NULL);
		else if (raw_line == NULL)
			raw_line = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(raw_line, buf);
			free(raw_line);
			raw_line = tmp;
		}
	}
	if (raw_line == NULL)
		return (NULL);
	cut_line_and_offset(&line_return, &raw_line);
	if (line_return == NULL)
		return (NULL);
	else
		return (line_return);
}
/*
int main()
{
	int	fd;
	char	*linea = NULL;

	fd = open("vacio", O_RDONLY);
	linea = get_next_line(fd);
	printf("%s", linea);
	linea = get_next_line(fd);
	printf("%s", linea);
	linea = get_next_line(fd);
	printf("%s", linea);
	linea = get_next_line(fd);
	printf("%s", linea);
	linea = get_next_line(fd);
	printf("%s", linea);
	linea = get_next_line(fd);
	printf("%s", linea);
	linea = get_next_line(fd);
	printf("%s", linea);
	return (0);
}*/