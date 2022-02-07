/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2022/02/05 11:21:03 by Emiliano         ###   ########.fr       */
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
	tmp = NULL;
	tmp = ft_strdup(&((*line_to_cut_and_offset)[line_size + 1]));
	*line_to_cut_and_offset = tmp;
	tmp = NULL;
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	j = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	if (size == 0)
		return (src_len);
	if (size < dst_len)
		return (src_len + size);
	else
	{
		while (src[j] && (dst_len + j) < size)
			dst[i++] = src[j++];
		if ((dst_len + j) == size && dst_len < size)
			dst[--i] = '\0';
		else
			dst[i] = '\0';
		return (src_len + dst_len);
	}
}

char *ft_select(char *buf, int *ret)
{    int i;
    char *dest;
    i = 0;
    while (buf && buf[i] && buf[i] != '\n')
        i++;
    dest = malloc (i + 1);
    if (!dest)
        return (NULL);
    if (ft_strchr(buf, '\n') != 0)
        *ret = 1;
    i = 0;
    while (buf && buf[i] && buf[i] != '\n')
    {    dest[i] = buf[i];
        i++; }
    dest[i] = 0;
    return (dest);}

char *ft_select2(char *buf)
{
    int i;
    int j;
    char *dest;

    i = 0;
    while (buf && buf[i] && buf[i] != '\n')
        i++;
    dest = malloc(sizeof (*dest) * (ft_strlen(buf) - i + 1)); 
   if (!dest)
        return (NULL);
    j = 0;
   while (buf && buf[i])
        dest[j++] = buf[++i];
    dest[j] = 0;
    return (dest);
}

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(*str) * size + 1);
	if (str == NULL)
		return (NULL);
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	int			ret = BUFFER_SIZE;
	char		buf[BUFFER_SIZE + 1];
	static char	*str;
	char		*tmp;
	char		*line_return = NULL;

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
		else 
		{
			tmp = str;
			str = ft_strjoin(tmp, buf);
			free(tmp);
		}
		if (ft_strchr(str, '\n'))
			break;
	}
	if (str[0] == 0)
	{ 
		free(line_return);
		free(str);
	    return (NULL);
	}
	tmp = str;
	line_return = ft_select(str, &ret);
    str = ft_select2(tmp);
	free(tmp);
    tmp = NULL;
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