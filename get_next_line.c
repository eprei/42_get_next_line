/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:40:14 by epresa-c          #+#    #+#             */
/*   Updated: 2021/12/20 16:41:45 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUF_SIZE 4096

char	*get_next_line(int fd)
{
	int		ret;
	char	buf_dest[BUF_SIZE + 1];
	char	*ptr;
	int		i;

	i = 0;
	ret = read(fd, buf_dest, BUF_SIZE);
	buf_dest[ret] = "\0";
	ptr = (char *)malloc(ret + 1);
	if (! ptr)
		return (-1);
	while (buf_dest[i] != '\0')
	{
		ptr[i] == *buf_dest;
		i++;
	}
	free(ptr);
	return (ptr);
}
