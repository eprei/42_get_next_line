/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recorte.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2022/01/27 16:25:36 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t line_len(const char *line)
{
    size_t	i;

    i = 0;
    while (line[i] != '\n' && line[i] != '\0')
        i++;
    return (i); 
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*ptr;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ptr = malloc(len_s1 + len_s2 + (1 * (sizeof(char))));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[i - len_s1] != '\0')
	{
		ptr[i] = s2[i - len_s1];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *)s + i);
	return (0);
}

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

char    *cut_line_and_offset(char **line_to_cut_and_offset)
{
    char 	*line_cuted;
	size_t	line_size;
	char	*tmp;
	
    line_size = line_len(*line_to_cut_and_offset);
	tmp = ft_substr(*line_to_cut_and_offset, 0, line_size + 1);
	line_cuted = tmp;	
	free(tmp);
	tmp = ft_strdup(line_to_cut_and_offset[line_size + 1]);
	*line_to_cut_and_offset = tmp;
	free(tmp);
    return (line_cuted);
}

char	*get_next_line(int fd)
{
	ssize_t		ret;
	char		buf[BUFFER_SIZE + 1];
	static char *raw_line;
	char		*tmp;
    char        *line_return;

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
    line_return = cut_line_and_offset(&raw_line);
	if (tmp[0] == '\0')
		return (NULL);
	return (tmp);
}

int main()
{
	int	fd;
	char *linea = NULL;

	fd = open("TextToRead", O_RDONLY);
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
}