/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2022/02/15 18:07:30 by Emiliano         ###   ########.fr       */
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
/*
char	*get_next_line(int fd)
{
	static ssize_t	ret = BUFFER_SIZE;
	char			buf[BUFFER_SIZE + 1];
	static char		*line = NULL;
	char			*tmp;
	char			*reste_du_texte;
	size_t			line_size;
	static char		*line_returned = NULL;

	if (fd < 0 || fd > 999 why tripouille find that fd 1000 return has to be NULL? || BUFFER_SIZE < 1)
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
		line = NULL;
		line = reste_du_texte;
		reste_du_texte = NULL;
		return (line_returned);
	}
}
*/
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
				break;
			ret = read(fd, buf, BUFFER_SIZE);
			buf[ret] = '\0';
		}
	}
	if (storage != NULL) // si hay algo guardado en storage, copiamos nueva linea a next_line
	{
		if (next_line != NULL) // si existe next_line, la liberamos
		{
			free(next_line); // free next_line en caso de que existiera previamente
			next_line = NULL; // llevarla a null para evitar eventuales doble free
		}
		line_size = line_len(storage); // medir la linea
		if (ft_strchr(storage, '\n')) // si hay '\n' copiar hasta el '\n' (line_size + 1)
			next_line = ft_substr(storage, 0, line_size + 1);
		if (!ft_strchr(storage, '\n')) // si no hay retorno a la linea, entonces es la ultima linea y no se copia un caracter mas. solo hasta (line_size);
		{
			next_line = ft_substr(storage, 0, line_size);
			free(storage);
			storage = NULL;
			return (next_line);
		}
	}	
	if (ft_strchr(storage, '\n') && storage != NULL) // si hay nueva linea entonces decalar storage
	{
		tmp = ft_strdup(&(storage)[line_size + 1]);
		free(storage);
		storage = tmp;
		tmp = NULL;
		return(next_line);
	}
/*	if (!ft_strchr(storage, '\n') && storage != NULL) // si no hay nueva linea, entonces es la ultima linea, entonces borramos el storage y devolvemos la linea
	{
		free(storage);
		storage = NULL;
		return (next_line);
	}
*/	if (next_line != NULL)
	{
		free(next_line);
		next_line = NULL;
	}
	return(NULL);
}
	
/* IDEA TEXTUAL
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret > 0)
		llamar funcion que copie buf en la linea_larga usando read y que se termine cuando strchr(buf, '\n') o cuando no haya mas nada para leer: ret = 0;
	llamar funcion que copia nueva linea en next_line
		1 si existe next_line y next_line != NULL: free(next_line) y next_line = NULL.
		2 si existe linea_larga y linea_larga != NULL: guarde en next_linea la nueva linea obteniendola de linea.
			1 Si strchr(linea_larga, '\n'), quiere decir que hay varias lineas y entonces copia hasta n + 1 o solo copia hasta n y luego agrega un '\n' al final.
			2 si !strch(linea_larga, '\n') quiere decir que es la ultima linea y copia hasta n.
	llamar funcion que decale la linea_larga
		si existe linea_larga y linea_larga != NULL;
		1 si strchr(linea_larga, '\n') entonces hay nueva linea y hay que decalar linea_larga usando substr() [ver linea 84 de codigo actual]
		2 si !strch(linea_larga, '\n') entonces no hay nueva linea. free(linea_larga) y linea_larga = NULL;
	return(next_line);
}
*/
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