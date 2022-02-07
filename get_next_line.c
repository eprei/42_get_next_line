/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2022/02/07 19:04:14 by Emiliano         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static ssize_t	ret = BUFFER_SIZE;
	char			buf[BUFFER_SIZE + 1];
	static char		*line = NULL;
	char			*tmp;
	char			*reste_du_texte;
	size_t			line_size;
	static char		*line_returned = NULL;

	if (fd < 0 || fd > 999 /*why tripouille find that fd 1000 return has to be NULL?*/ || BUFFER_SIZE < 1)
		return (0);
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		if (ret < 0) 
			return (NULL);
		if (line == NULL)
			line = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(line, buf);
			free(line);
			line = tmp;
			tmp = NULL;
		}
		if (ft_strchr(line, '\n'))
			break;
	}
	if (line[0] == 0)
	{ 
		if (line != NULL)
		{
			free(line);
			line = NULL;
		}
		return (NULL);
	}
	else
	{
		line_size = line_len(line); // mesurer la ligne
		line_returned = ft_substr(line, 0, line_size + 1); // extrait la nouvelle ligne et la stocke dans line_returned
		reste_du_texte = ft_strdup(&(line)[line_size + 1]); // extraire le reste de la ligne et l'enregistrer dans reste_du_texte
		free(line);
//		line = NULL;
		line = reste_du_texte;
//		reste_du_texte = NULL;
		return (line_returned);
	}
}
/*
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
}*/
