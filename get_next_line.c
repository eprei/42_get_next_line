/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2022/02/16 16:33:10 by epresa-c         ###   ########.fr       */
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

void	ft_refill_storage(char **storage, int fd, int ret, char *buf)
{
	char	*tmp;

	while (ret > 0)
	{
		if (*storage == NULL)
			*storage = ft_strdup("");
		else
		{	
			buf[ret] = '\0';
			tmp = ft_strjoin(*storage, buf);
			free(*storage);
			*storage = tmp;
			tmp = NULL;
			if (ft_strchr(buf, '\n'))
				break ;
			ret = read(fd, buf, BUFFER_SIZE);
			buf[ret] = '\0';
		}
	}
}

void	ft_copy_next_line_and_offset_storage(char **storage, char **next_line)
{
	char	*tmp;
	size_t	line_size;

	if (*storage != NULL)
	{
		line_size = line_len(*storage);
		if (ft_strchr(*storage, '\n'))
		{
			*next_line = ft_substr(*storage, 0, line_size + 1);
			tmp = ft_strdup(&(*storage)[line_size + 1]);
			free(*storage);
			*storage = tmp;
			tmp = NULL;
		}
		else
		{
			if (line_size != 0)
				*next_line = ft_substr(*storage, 0, line_size);
			free(*storage);
			*storage = NULL;
		}
	}
}

char	*get_next_line(int fd)
{
	static char		*storage = NULL;
	char			*next_line;
	char			buf[BUFFER_SIZE + 1];
	int				ret;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret < 0)
		return (NULL);
	if (ret == 0 && storage == NULL)
	{
		free(next_line);
		next_line = NULL;
	}
	ft_refill_storage(&storage, fd, ret, buf);
	ft_copy_next_line_and_offset_storage(&storage, &next_line);
	return (next_line);
}
