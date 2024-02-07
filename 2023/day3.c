#include <stdio.h>
#include <stdbool.h>

int main()
{
    const char *fname = "input.txt";
    FILE *data = NULL;
    data = fopen(fname, "r");

    if(data == NULL)
    {
        printf("Error: File does not exist");
        return 1;
    }

    int num = 0, col = 0;
    long curpos = ftell(data), prevline = ftell(data);
    bool symbol = false;
    char c;
    while((c = fgetc(data)) != EOF)
    {
        if(c >= '0' && c <= '9')
        {
            num = 0;
            do
            {
                num = num*10 + (c-48);
                c = fgetc(data);
            }while (c >= '0' && c <= '9');
            printf("%d\n", num);
        }
    }
}
