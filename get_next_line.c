/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2022/02/16 12:45:57 by epresa-c         ###   ########.fr       */
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
	static char		*storage;
	char			*next_line = NULL;
	char			buf[BUFFER_SIZE + 1];
	int				line_size;
	char			*tmp;
	ssize_t			ret;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret < 0)
		return (NULL);
	if (ret == 0 && storage == NULL)
	{
		free(next_line);
		next_line = NULL;
		return (next_line);
	}
	buf[ret] = '\0';
	while (ret > 0) // rellenar storage con buf hasta que encuentra una nueva linea '\n'
	{
		if (storage == NULL)
			storage = ft_strdup("");
		else
		{
			tmp = ft_strjoin(storage, buf);
			free(storage);
			storage = tmp;
			tmp = NULL;
			if (ft_strchr(buf, '\n'))
				break ;
			ret = read(fd, buf, BUFFER_SIZE);
			buf[ret] = '\0';
		}
	}
	if (storage != NULL) // si hay algo guardado en storage, copiamos nueva linea a next_line
	{
		line_size = line_len(storage); // medir la linea
		if (ft_strchr(storage, '\n')) // si hay '\n' copiar hasta el '\n' (line_size + 1)
			next_line = ft_substr(storage, 0, line_size + 1);
		if (!ft_strchr(storage, '\n') && line_size != 0) // si no hay retorno a la linea, entonces es la ultima linea y no se copia un caracter mas. solo hasta (line_size);
			next_line = ft_substr(storage, 0, line_size);
	}	
	if (ft_strchr(storage, '\n') && storage != NULL) // si hay nueva linea entonces decalar storage
	{
		tmp = ft_strdup(&(storage)[line_size + 1]);
		free(storage);
		storage = tmp;
		tmp = NULL;
		return (next_line);
	}
	if (!ft_strchr(storage, '\n') && storage != NULL) // si no hay nueva linea, entonces es la ultima linea, entonces borramos el storage y devolvemos la linea
	{
		free(storage);
		storage = NULL;
		return (next_line);
	}
	if (next_line != NULL)
	{
		free(next_line);
		next_line = NULL;
	}
	return (NULL);
}
/*
int main()
{
	int	fd;
	char *linea = NULL;

	fd = open("TextToRead", O_RDONLY);
	linea = get_next_line(fd);
	printf("1: %s", linea);
	linea = get_next_line(fd);
	printf("2: %s", linea);
	linea = get_next_line(fd);
	printf("3: %s", linea);
	linea = get_next_line(fd);
	printf("4: %s", linea);
	linea = get_next_line(fd);
	printf("5: %s", linea);
	linea = get_next_line(fd);
	printf("6: %s", linea);
	linea = get_next_line(fd);
	printf("7: %s", linea);
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
*/