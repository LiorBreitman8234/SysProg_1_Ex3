#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define TXT 1024
#define WORD 30

int calcGimatricValue(const char* text)
{
    int valueOfText = 0;
    int i =0;
    while(*(text+i) != '\0')
    {
        if((*(text+i) >= 'a' && *(text+i) <= 'z'))
        {
            valueOfText += *(text+i) - 96;
        }
        else if((*(text+i) >= 'A' && *(text+i) <= 'Z'))
        {
            valueOfText += *(text+i) - 64;
        }
        i++;
    }

    return valueOfText;
}
char* atBash(char* word,unsigned long len)
{
    char* flipped = (char*)malloc(sizeof (char) * (len+1));
    if(flipped == NULL)
    {
        exit(1);
    }
    for(int i =0; i < len;i++)
    {
        if(word[i] <= 'z' && word[i] >= 'a')
        {
            int gimValue = word[i]-96;
            char c = ('z' -gimValue  + 1);
            flipped[i] = c;
        }
        else if(word[i] <= 'Z' && word[i] >= 'A')
        {
            int gimValue = word[i]-64;
            char c = ('z' -gimValue  + 1);
            flipped[i] = c;
        }
        else
        {
            flipped[i] = word[i];
        }
    }
    flipped[len] = '\0';
    return flipped;
}
char* reverseString(const char* word,unsigned long len)
{
    char* flipped = (char*)malloc(sizeof (char) * (len+1));
    if(flipped == NULL)
    {
        exit(1);
    }
    for(int i = 0;i < len;i++)
    {
        flipped[i] = word[len-i-1];
    }
    flipped[len] = '\0';
    return flipped;
}

int checkIdenctical(char* word1, char* word2)
{
    int i =0;
    int j =0;
    while(i != strlen(word1) || j != strlen(word2)){
        if(word2[j] == ' ' || word2[j] == '\n' || word2[j] == '\t')
        {
            j++;
        }
        if(word2[j] != word1[i])
        {
            return 1;
        }
        i++;
        j++;
    }
    return 0;
}

void secondFunction(char* word, char* text)
{
    char* bashed = atBash(word,strlen(word));
    char* flipped = reverseString(bashed, strlen(word));
    int counter = 0;
    int baseValue = calcGimatricValue(bashed);
    for(int i = 0; i < strlen(text); i++)
    {

        char* first = (text+i);
        if((*(first) > 'Z' || *(first) < 'A')  && (*(first) > 'z' || *(first) < 'a'))
        {
            continue;
        }
        for(int j = strlen(first); j > 0;j--)
        {
            char* currString = (char*)malloc(sizeof (char) * (j+1));
            if(currString == NULL)
            {
                break;
            }
            strncpy(currString,first,j);
            currString[j] = '\0';
            if((*(currString) > 'Z' || *(currString) < 'A')  && (*(currString) > 'z' || *(currString) < 'a'))
            {
                free(currString);
                continue;
            }
            if((*(currString + j-1) > 'Z' || *(currString+ j-1) < 'A')  && (*(currString+ j-1) > 'z' || *(currString+ j-1) < 'a'))
            {
                free(currString);
                continue;
            }
            int currValue = calcGimatricValue(currString);
            if(currValue == baseValue)
            {
                if(checkIdenctical(bashed,currString) == 0 || checkIdenctical(flipped,currString) == 0)
                {
                    if(counter == 0)
                    {
                        printf("%s",currString);
                        counter++;
                    }
                    else
                    {
                        printf("~%s",currString);
                    }
                }
            }
            free(currString);
        }
    }
    free(bashed);
    free(flipped);
}

int checkSortIdentical(char* word,char* toCheck)
{
    int sort1[128] = {0};
    int sort2[128] = {0};
    for(int i =0; i < strlen(word);i++)
    {
        if(word[i] != ' ' && word[i] != '\n' && word[i] != '\t')
        {
            int index = (int)word[i];
            sort1[index]++;
        }
    }
    for(int i =0; i < strlen(toCheck);i++)
    {
        if(toCheck[i] != ' ' && toCheck[i] != '\n' && toCheck[i] != '\t')
        {
            int index = (int)toCheck[i];
            sort2[index]++;
        }
    }
    for(int i =0; i < 128;i++)
    {
        if(sort1[i] != sort2[i])
        {
            return 0;
        }
    }

    return 1;
}
void thirdFunction(char* word, char* text)
{
    int baseValue = calcGimatricValue(word);
    int counter = 0;
    for(unsigned long i = 0; i < strlen(text); i++)
    {
        char* first = (text+i);
        if((*(first) > 'Z' || *(first) < 'A')  && (*(first) > 'z' || *(first) < 'a'))
        {
            continue;
        }
        for(unsigned long j = strlen(first); j > 0;j--)
        {
            char* currString = (char*)malloc(sizeof(char) * (j+1));
            if(currString == NULL)
            {
                break;
            }
            strncpy(currString,first,j);
            currString[j] = '\0';
            if((*(currString) > 'Z' || *(currString) < 'A')  && (*(currString) > 'z' || *(currString) < 'a'))
            {
                free(currString);
                continue;
            }
            if((*(currString + j-1) > 'Z' || *(currString+ j-1) < 'A')  && (*(currString+ j-1) > 'z' || *(currString+ j-1) < 'a'))
            {
                free(currString);
                continue;
            }
            int currValue = calcGimatricValue(currString);
            if(currValue == baseValue)
            {
                if(checkSortIdentical(word,currString) == 1)
                {
                    if(counter == 0)
                    {
                        printf("%s",currString);
                        counter++;
                    }
                    else
                    {
                        printf("~%s",currString);
                    }
                }
            }
            free(currString);
        }
    }

}

void firstFunction(char* word, char* text)
{
    int baseValue = calcGimatricValue(word);
    int counter = 0;
    for(unsigned long i = 0; i < strlen(text); i++)
    {
        char* first = (text+i);
        if((*(first) > 'Z' || *(first) < 'A')  && (*(first) > 'z' || *(first) < 'a'))
        {
            continue;
        }
        for(unsigned long j = strlen(first); j > 0;j--)
        {
            char* currString = (char*)malloc(sizeof (char) * (j+1));
            if(currString == NULL)
            {
                break;
            }
            strncpy(currString,first,j);
            if((*(currString) > 'Z' || *(currString) < 'A')  && (*(currString) > 'z' || *(currString) < 'a'))
            {
                free(currString);
                continue;
            }
            if(((currString[j-1] > 'Z' || currString[j-1] < 'A'))  && ((currString[j-1] > 'z' || currString[j-1] < 'a')))
            {
                free(currString);
                continue;
            }
            currString[j] = '\0';
            int currValue = calcGimatricValue(currString);
            if(currValue == baseValue)
            {
                if(counter == 0)
                {
                    printf("%s",currString);
                    counter++;
                }
                else
                {
                    printf("~%s",currString);
                }
            }
            free(currString);
        }
    }
}


int main() {

    char* word = (char*)malloc(WORD);
    if(word == NULL)
    {
        return 0;
    }
    int counter = 0;
    for(int i =0; i < WORD;i++)
    {
        char c = getc(stdin);
        if(c == '\n' || c == ' ' || c == '\t')
        {
            break;
        }
        else
        {
            word[i] = c;
            counter++;
        }
    }
    word[counter] = '\0';


    char* txt = (char*)malloc(TXT);
    if(txt == NULL)
    {
        return 0;
    }
    counter = 0;
    for(int i =0; i < TXT;i++)
    {
        char c = getc(stdin);
        if(c == '~')
        {
            break;
        }
        else
        {
            txt[i] = c;
            counter++;
        }
    }
    txt[counter] = '\0';

    printf("Gematria Sequences: ");
    firstFunction(word,txt);
    printf("\n");
    printf("Atbash Sequences: ");
    secondFunction(word,txt);
    printf("\n");
    printf("Anagram Sequences: ");
    thirdFunction(word,txt);

    free(txt);
    free(word);
    return 0;
}
