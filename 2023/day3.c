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

    int num = 0, col = 0, sol = 0;
    long curpos = ftell(data), prevline = ftell(data);
    bool symbol = false;
    char c;
    while((c = fgetc(data)) != EOF)
    {
        ++col;
        if(c >= '0' && c <= '9')
        {
            do
             {
                num = num*10 + (c-48);
                c = fgetc(data);
                ++col;
            }while (c >= '0' && c <= '9');
        }

        if(symbol && num == 0) symbol = false;

        if(c != '.' && c != '\n')
        {
            symbol = true;
            if(num == 0) continue;
        }

        if(symbol)
        {
            sol += num;
            symbol = false;
            printf("%d\n", num);
        }

        num = 0;
    }
}
