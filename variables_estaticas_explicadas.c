/*int main(void)
{
    int x = open ("C:\Users\mykje\Documents\GitHub\42_Get_Next_Line\subject.txt", O_RDONLY);

    get_next_line(x);
}*/

#include <stdio.h>

int suma(int x)
{
    static int i = 0;
    i += x;
    return (i);
}
int main(void)
{
    int z = 1;
    suma(z);
    suma(z);
    printf("%d", suma(z));
}
/*
    Las variables estáticas, mientras dure el main, mantendrán el valor.
    Como la variable estática existe, la línea donde se inicia se obvia.
        El resto del código se ejecuta con normalidad.
*/