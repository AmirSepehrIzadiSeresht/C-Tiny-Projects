#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *abbreviations[] = {"&", "imo", "hru", "ic", "lol",
                               "bro", "2morrow", "2day", "bf", "mu",
                               "b4", "bt", "ruok", "aka", "ama",
                               "2nite", "irl", "ily", "hmu", "l8r",
                               "jk", "afaik", "btw", "brb", "tbh",
                               "gr8", "sis", "asap", "l8r", "gf",
                               "r", "u", "c"};

const char *phrases[] = {"and", "in my opinion", "how are you",
                         "I see", "laughing out loud", "brother",
                         "tomorrow", "today", "boyfriend", "I miss you",
                         "before", "but", "are you ok", "also known as",
                         "ask me anything", "tonight", "in real life",
                         "I love you", "hit me up", "later", "just kidding",
                         "as far as I know", "by the way", "be right back",
                         "to be honest", "great", "sister",
                         "as soon as possible", "later", "girlfriend",
                         "are", "you", "see"};

void smsToEnglish(char *sms);
void englishToSms(char *message);

int main()
{

    char sms[161];
    int i, ch = 0;

    puts("Enter SMS (^ to end): \n");

    for (i = 0; i < 160 && ch != '^'; ++i)
    {
        scanf("%c", &ch);

        if (ch != '^')
            sms[i] = ch;
        else
            sms[i] = '\0';
    }

    smsToEnglish(sms);

    char message[501];

    ch = 0;

    puts("Enter a message without abbreviations (^ to end)");

    for (i = 0; i < 500 && ch != '^'; ++i)
    {
        scanf("%c", &ch);

        if (ch != '^')
            message[i] = ch;
        else
            message[i] = '\0';
    }

    englishToSms(message);
}

void smsToEnglish(char *sms)
{

    char message[500];
    char *occurance;
    char remainder[500];

    strcpy(message, sms);

    for (int i = 0; i < 33; ++i)
    {
        if (occurance = strstr(message, abbreviations[i]))
        {

            strcpy(remainder, occurance + strlen(abbreviations[i]));

            if (!isalpha(*(occurance - 1)) && !isalpha(*remainder))
            {

                *occurance = '\0';

                    strcat(occurance, phrases[i]);

                strcat(message, remainder);
            }

            while(occurance = 
                strstr(message + strlen(message) - strlen(remainder), abbreviations[i])) {
                strcpy(remainder, occurance + strlen(abbreviations[i]));

                if (!isalpha(*(occurance - 1)) && !isalpha(*remainder))
                {

                    *occurance = '\0';

                        strcat(occurance, phrases[i]);

                    strcat(message, remainder);
                }
        

            }
        }

    }
    printf("\n%s", message);
}

void englishToSms(char *message)
{
    char *occurence;
    char remainder[500];

    for (int i = 0; i < 33; i++)
    {
        if (occurence = strstr(message, phrases[i]))
        {
            strcpy(remainder, occurence + strlen(phrases[i]));

            if (!isalpha(*remainder) && !isalpha(*(occurence - 1)))
            {
                *occurence = '\0';

                strcat(occurence, abbreviations[i]);

                strcat(message, remainder);

                while (occurence =
                           strstr(message + strlen(message) - strlen(remainder),
                                  phrases[i]))
                {

                    strcpy(remainder, occurence +
                                          strlen(phrases[i]));

                    if (!isalpha(*remainder) &&
                        !isalpha(*(occurence - 1)))
                    {
                        *occurence = '\0';

                        strcat(occurence, abbreviations[i]);

                        strcat(message, remainder);
                    }
                }
            }
        }
    }

    if (strlen(message) <= 160)
    {
        printf("\n%s", message);
    }
    else
    {
        printf("\nThe message is too long!");
    }
}