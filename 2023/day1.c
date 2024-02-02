#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void)
{
    int sol = 0;

    const char *fname = "input.txt";
    FILE *strm = fopen(fname, "r");

    if(strm == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 1;
    }

    const char *nums[] = {"one", "two", "three", "four",
                          "five", "six", "seven", "eight", "nine"};
    char c, n[6] = "";
    int a = 0, b = 0, numlen;
    while( (c = fgetc(strm)) != EOF)
    {
        if(c >= '0' && c <= '9')
        {
            if(a == 0) a = c - 48;
            else
            {
                b = c - 48;
            }
            continue;
        }
        else
        {
            if(c != 10)
            {
                numlen = 1;
                for(int i = 0; i < numlen; ++i)
                {
                    n[numlen - 1] = c;
                    n[numlen] = '\0';
                    for(int j = 0; j < 9; ++j)
                    {
                        if(strncmp(n, nums[j], numlen) == 0)
                        {
                            if(strlen(n) == strlen(nums[j]))
                            {
                                if(a == 0) a = j + 1;
                                else
                                {
                                    b = j + 1;
                                }
                                fseek(strm, -1, SEEK_CUR);
                                break;
                            }
                            else
                            {
                                c = fgetc(strm);
                                ++numlen;
                                break;
                            }
                        }
                        else
                            if(j == 8)
                            {
                                fseek(strm, -(numlen-1), SEEK_CUR);
                                break;
                            }
                    }
                }
                continue;
            }
        }

        if(c == 10) //new line
        {
            if(b == 0)  b = a;
            sol += a*10 + b;
            a = 0;
            b = 0;
        }
    }
    printf("Day 1 solution: %d\n", sol);
}
