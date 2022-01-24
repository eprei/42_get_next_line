#include    <stdio.h>
#include    <stdlib.h>

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

    largo = ft_largon(str + i);
    ptr = (char *) malloc((sizeof(char)*largo) + 1);
    if (ptr == NULL)
        return (0);
    while (*str && str[i] != '\n' && str[i] != '\0')
          ptr[j++] = str[i++];
    ptr[j] = '\0';
    i++;
    return (ptr);
}

int main()
{
    char *str = "Esto\nes\nuna\nprueba";
    
    printf("%s\n", cortar(str));
    printf("%s\n", cortar(str));
    printf("%s\n", cortar(str));
    printf("%s\n", cortar(str));
    return (0);
}