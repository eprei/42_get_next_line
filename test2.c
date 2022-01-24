#include    <stdio.h>
#include    <stdlib.h>

size_t	ft_strlen(const char *s)
{
	unsigned long long	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (!dstsize)
		return (src_len);
	while (src[i] != '\0' && (i < dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize < src_len)
		dst[dstsize - 1] = '\0';
	else if (dstsize != 0)
		dst[i] = '\0';
	return (src_len);
}

int ft_largon(char *str)
{
    int    i;

    i = 0;
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    return (i); 
}

char *cortar(char *str)
{
    static int    i = 0;
    int           j = 0;
    int            largo;
    char        *ptr;
    char        *ret;

    largo = ft_largon(str + i);
    ptr = (char *) malloc((sizeof(char)*largo) + 1);
    if (ptr == NULL)
        return (0);
    while (*str && str[i] != '\n' && str[i] != '\0')
          ptr[j++] = str[i++];
    ptr[j] = '\0';
    ft_strlcpy(ret, ptr, largo);
    free(ptr);
    i++;
    return (ret);
}

int main()
{
    char *str = "Esto\nes\nuna\nprueba";
    char *copia = cortar(str);

    printf("%s\n", copia);
//   printf("%s\n", cortar(str));
    return (0);
}