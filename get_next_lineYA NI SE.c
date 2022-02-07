/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2022/02/05 11:26:42 by Emiliano         ###   ########.fr       */
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
	static char	*str = NULL;
	char		*tmp;
	char		*line_return = NULL;

	ret = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		buf[ret] = '\0';
		if (str == NULL)
			str = ft_strdup(buf);
		tmp = str;
		str = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(str, '\n') || ft_strchr(str, '\n'))
			break;
	}
	if (ret == 0 && (str[0] == '\0'))
	{
		free(str);
		free(line_return);
		str = NULL;
		line_return = NULL;
		return (NULL);
	}
	else
	{
		cut_line_and_offset(&line_return, &str);
		return (line_return);
	}
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