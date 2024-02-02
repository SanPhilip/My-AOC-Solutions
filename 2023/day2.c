#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define SIZE 20
#define RED 12
#define GREEN 13
#define BLUE 14

void clin()
{
    const char *input = "input.txt";
    FILE *read = fopen(input, "r");
    if(read == NULL)
        printf("Error: %s\n", strerror(errno));

    FILE *write = fopen("output.txt", "w");

    int c;
    while((c = fgetc(read)) != EOF)
    {
        if(c == ' ') fputc(10, write);
        else
            if ((c == 10)
                || (c >= '0' && c <= '9')
                || (c >= 'A' && c <= 'Z')
                || (c >= 'a' && c <= 'z'))
                fputc(c, write);
    }
    fclose(read);
    fclose(write);
}

int main()
{
    clin();
    const char *fname = "output.txt";
    FILE *data = fopen(fname, "r");
    if(data == NULL)
        printf("Error: %s\n", strerror(errno));

    int c, ids = 0, previds = 1, ncubes = 0, sol = 0;
    bool possible = true;
    char s[SIZE] = "";
    while( (c = fgetc(data)) != EOF)
    {
        if(c >= '0' && c <= '9')
        {
            ncubes = 0;
            do
            {
                ncubes = ncubes*10 + (c - 48);
            } while((c = fgetc(data)) >= '0' && c <= '9');
        }
        else
        {
            fseek(data, -1, SEEK_CUR);

            if(fgets(s, SIZE, data) != NULL)
            {
                if(strcmp(s, "Game\n") == 0) ++ids;
                else if(strcmp(s, "green\n") == 0)
                {
                    if(ncubes > GREEN) possible = false;
                }
                else if(strcmp(s, "red\n") == 0)
                {
                    if(ncubes > RED) possible = false;
                }
                else
                    if(ncubes > BLUE) possible = false;
            }
            /* printf("ids: %d\ncolor: %sncubes: %d\n", ids, s, ncubes); */
            if(ids != previds)
            {
                /* printf("ids: %d\n", ids - 1); */
                if(possible) sol += ids - 1;
                previds = ids;
                possible = true;
            }
        }
    }
    if(possible) sol += ids;
    printf("Day 2 solution: %d\n", sol);
    return 0;
}
