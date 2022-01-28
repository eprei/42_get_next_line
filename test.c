#include    <stdio.h>
#include    <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t line_len(const char *line)
{
    size_t	i;

    i = 0;
    while (line[i] != '\n' && line[i] != '\0')
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

char    *cut_line_and_offset(char **line_to_cut_and_offset) //add other parameter to the return line like codigo externo and modify it directly
{
    char 	*line_cuted;
	size_t	line_size;
	char	*tmp;
	
    line_size = line_len(*line_to_cut_and_offset);
	tmp = ft_substr(*line_to_cut_and_offset, 0, line_size + 1);
	line_cuted = tmp;	
//	free(tmp);
	tmp = ft_strdup(&((*line_to_cut_and_offset)[line_size + 1]));
	*line_to_cut_and_offset = tmp;
//	free(tmp);
    return (line_cuted);
}

int main()
{
    char *str = "Esto\nes\nuna\nprueba";
    char *cortada = cut_line_and_offset(&str);

    printf("%s", cortada);
    printf("%s\n", str);
    return (0);
}