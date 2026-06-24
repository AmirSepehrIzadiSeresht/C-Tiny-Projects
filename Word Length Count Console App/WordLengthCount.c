#include <stdio.h>
#include <string.h>

int main()
{

    char line[100] = {0};
    char *word;
    char freq[30] = {0};

    int maxSize = 0;

    puts("Enter a  line of text. Type END when you are done");

    fgets(line, 100, stdin);

    do
    {
        word = strtok(line, " ,.:-;!?\n");
        freq[strlen(word)]++;
        if (strlen(word) > maxSize)
        {
            maxSize = strlen(word);
        }

        while(word = strtok(NULL, " ,.:-;!?\n")) {
            freq[strlen(word)]++;
            if (strlen(word) > maxSize)
            {
                maxSize = strlen(word);
            }
        }
        
        fgets(line, 100, stdin);
    } while (strcmp(line, "END\n"));

    printf("%11s%16s\n", "Word length", "Occurrences");
    printf("%27s\n", "---------------------------");
    for (int i = 0; i <= maxSize; i++)
    {
        printf("%6d%16d\n", i, freq[i]);
    }
}