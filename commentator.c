#include "commentator.h"

void usage()
{
    printf("Usage: commentator InFileName\nOptional:\n-o\tOut file\n-m\tMin symbols number to comment\n");
}

int main(int argc, const char** argv)
{
    FILE* inFile, *outFile;
    char buff[BUFSIZ];
    const char* out, *temp = "temp.txt";
    int distance = 0;
    int maxDistance = 0;
    int offset = 0;
    int read = 0;
    int chars = 0;
    int minimum = 2;

    if (argc < 2 || argc > 6)
    {
        usage();
        return -1;
    }

    out = temp;

    for (int i = 2; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-o"))
        {
            if (i + 1 >= argc)
            {
                usage();
                return -2;
            }
            out = argv[i + 1];
            ++i;
        }
        else if (!strcmp(argv[i], "-m"))
        {
            if (i + 1 >= argc)
            {
                usage();
                return -3;
            }
            minimum = atoi(argv[i + 1]);
            ++i;
        }
        else
        {
            printf("Wrong parameter!\n");
            usage();
            return -4;
        }
    }

    inFile = fopen(argv[1], "r");
    if (inFile == NULL)
    {
        printf("Error: cant open file %s\n", argv[1]);
        return -5;
    }

    while ((read = fread(buff, 1, BUFSIZ - 1, inFile)) > 0)
    {
        buff[read] = '\0';
        for (int i = 0; i < read; ++i)
        {
            if (buff[i] == '\n')
            {
                if (distance > maxDistance)
                {
                    maxDistance = distance;
                }
                distance = 0;
            }
            else
            {
                ++distance;
            }
        }
    }
    if (distance > maxDistance)
    {
        maxDistance = distance;
    }
    distance = 0;

    ++maxDistance;

    fseek(inFile, 0, SEEK_SET);

    outFile = fopen(out, "w");

    while ((read = fread(buff, 1, BUFSIZ - 1, inFile)) > 0)
    {
        buff[read] = '\0';
        for (int i = 0; i < read; ++i)
        {
            if (buff[i] == '\n')
            {
                if (chars >= minimum)
                {
                    offset = maxDistance - distance;
                    for (int i = 0; i < offset; ++i)
                    {
                        fwrite(" ", 1, 1, outFile);
                    }
                    fwrite("//", 1, 2, outFile);
                }
                fwrite("\n", 1, 1, outFile);
                distance = 0;
                chars = 0;
            }
            else
            {
                if (buff[i] != ' ')
                {
                    ++chars;
                }
                fwrite(&buff[i], 1, 1, outFile);
                ++distance;
            }
        }
    }

    fclose(outFile);
    fclose(inFile);

    if (out == temp)
    {
        sprintf(buff, "mv temp.txt %s", argv[1]);
        system(buff);
    }

    return 0;
}