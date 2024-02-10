#include <stdio.h>
#include <stdbool.h>

int count_ndigits(int num)
{
    int ndigits = 0;
    do
    {
        ++ndigits;
        num /= 10;
    } while(num != 0);
    return ndigits;
}

bool check_pline(FILE *data, long prevline, int col, int ndigits)
{
    fseek(data, prevline, SEEK_SET);
    char c;

    for(int i = 0; i < col; ++i)
    {
        c = fgetc(data);
        if(i >= col-(ndigits+2))
            if((c != '.' && c != '\n') && !(c >= '0' && c <= '9'))
                return true;
    }
    return false;
}

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

    int num = 0, col = 0, sol = 0, ndigits = 0;
    long curpos = 0, prevline = 0, curline = 0;
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
            ndigits = count_ndigits(num);
        }

        if(c == '\n')
        {
            prevline = curline;
            curline = ftell(data);
            col = 0;
        }

        /* if(symbol && num == 0) symbol = false; */

        /* if(c != '.' && c != '\n') */
        /* { */
        /*     symbol = true; */
        /*     if(num == 0) continue; */
        /* } */

        curpos = ftell(data);

        if(num != 0)
            symbol = check_pline(data, prevline, col, ndigits);

        if(symbol)
        {
            sol += num;
            symbol = false;
            printf("%d\n", num);
        }

        fseek(data, curpos, SEEK_SET);

        num = 0;
    }
}
