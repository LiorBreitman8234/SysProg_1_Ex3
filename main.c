#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define TXT 1024
#define WORD 30

/* in this assignment we need to write a program which receives
a word (can be up to 30 letter), until it receives an empty char
text is finished at the char ~ (max length for text is 256)*/


/* calculates gematric value of string */
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
    char* flipped = (char*)malloc(sizeof (char) * (len+1)); //will be the atbeshed word
    if(flipped == NULL)
    {
        exit(1);
    }
    for(int i =0; i < len;i++)
    {
        if(word[i] <= 'z' && word[i] >= 'a') //lower case letter
        {
            int gimValue = word[i]-96; //the gimatric value of the letter, using Ascii table
            char c = ('z' -gimValue  + 1); //the oposite letter of the current letter
            flipped[i] = c;
        }
        else if(word[i] <= 'Z' && word[i] >= 'A') //upper case letter
        {
            int gimValue = word[i]-64; //the gimatric value of the letter, using Ascii table
            char c = ('z' -gimValue  + 1); //the oposite letter of the current letter
            flipped[i] = c;
        }
        else
        {
            flipped[i] = word[i]; //not a letter
        }
    }
    flipped[len] = '\0';
    return flipped;
}

//reverse a string 
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

//check whether two strings are the same
int checkIdenctical(char* word1, char* word2)
{
    int i =0;
    int j =0;
    while(i != strlen(word1) || j != strlen(word2)){
        //end of word
        if(word2[j] == ' ' || word2[j] == '\n' || word2[j] == '\t')
        {
            j++;
        }
        //not identical
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
    char* bashed = atBash(word,strlen(word)); //the word in Atbash
    char* flipped = reverseString(bashed, strlen(word)); //the word in reversed Atbash
    int counter = 0;
    int baseValue = calcGimatricValue(bashed); //calculates the gematric value of the string
    //going throgh the chars in the text string
    for(int i = 0; i < strlen(text); i++)
    {

        char* first = (text+i); //first char at the text string
        // if the char isn't a letter --> don't calculate it
        if((*(first) > 'Z' || *(first) < 'A')  && (*(first) > 'z' || *(first) < 'a'))
        {
            continue;
        }
        //running over the current text
        //index i defines the current text "first" to start from index i,
        //index j defines the current text "first" to end at index j.
        for(int j = strlen(first); j > 0;j--)
        {
            char* currString = (char*)malloc(sizeof (char) * (j+1));
            if(currString == NULL)
            {
                break;
            }
            strncpy(currString,first,j); //curr receives the string "first" values until index j
            currString[j] = '\0';
            // if the char isn't a letter --> don't calculate it
            if((*(currString) > 'Z' || *(currString) < 'A')  && (*(currString) > 'z' || *(currString) < 'a'))
            {
                free(currString);
                continue;
            }
            // if the last char isn't a letter --> don't calculate it
            if((*(currString + j-1) > 'Z' || *(currString+ j-1) < 'A')  && (*(currString+ j-1) > 'z' || *(currString+ j-1) < 'a'))
            {
                free(currString);
                continue;
            }
            int currValue = calcGimatricValue(currString); //the gematric value of string "curr"
            //checking if the gematric values of the word and the current string are equal
            if(currValue == baseValue)
            {
                if(checkIdenctical(bashed,currString) == 0 || checkIdenctical(flipped,currString) == 0) //if not identical ( 0 == false )
                {
                    if(counter == 0) //prints at first the current string
                    {
                        printf("%s",currString);
                        counter++;
                    }
                    //if we have more than one compatible string we print them with ~ between to seperate the words
                    else
                    {
                        printf("~%s",currString);
                    }
                }
            }
            free(currString); //in order to free the space we used
        }
    }
    free(bashed); //in order to free the space we used
    free(flipped); //in order to free the space we used
}

//counting sort
int checkSortIdentical(char* word,char* toCheck)
{
    //there are 128 ascii values
    int sort1[128] = {0};
    int sort2[128] = {0};
    for(int i =0; i < strlen(word);i++)
    {
        //if it's not empty char
        if(word[i] != ' ' && word[i] != '\n' && word[i] != '\t')
        {
            int index = (int)word[i];
            sort1[index]++;
        }
    }
    for(int i =0; i < strlen(toCheck);i++)
    {
        //if it's not empty char
        if(toCheck[i] != ' ' && toCheck[i] != '\n' && toCheck[i] != '\t')
        {
            int index = (int)toCheck[i];
            sort2[index]++;
        }
    }
    for(int i =0; i < 128 ;i++)
    {
        //not identical
        if(sort1[i] != sort2[i])
        {
            return 0; // false
        }
    }
    return 1; //true
}

void thirdFunction(char* word, char* text)
{
    int baseValue = calcGimatricValue(word); //calculates the gematric value of the string
    int counter = 0;
    //going throgh the chars in the text string
    for(unsigned long i = 0; i < strlen(text); i++)
    {
        char* first = (text+i); //first char at the text string
        // if the char isn't a letter --> don't calculate it
        if((*(first) > 'Z' || *(first) < 'A')  && (*(first) > 'z' || *(first) < 'a'))
        {
            continue;
        }
        //running over the current text
        //index i defines the current text "first" to start from index i,
        //index j defines the current text "first" to end at index j.
        for(unsigned long j = strlen(first); j > 0;j--)
        {
            char* currString = (char*)malloc(sizeof(char) * (j+1)); //the string part we want to check
            if(currString == NULL)
            {
                break;
            }
            strncpy(currString,first,j); //curr receives the string "first" values until index j
            currString[j] = '\0';
            // if the char isn't a letter --> don't calculate it
            if((*(currString) > 'Z' || *(currString) < 'A')  && (*(currString) > 'z' || *(currString) < 'a'))
            {
                free(currString);
                continue;
            }
            // if the char isn't a letter --> don't calculate it
            if((*(currString + j-1) > 'Z' || *(currString+ j-1) < 'A')  && (*(currString+ j-1) > 'z' || *(currString+ j-1) < 'a'))
            {
                free(currString);
                continue;
            }
            int currValue = calcGimatricValue(currString); //the gematric value of string "curr"
            if(currValue == baseValue) //checking if the gematric values of the word and the current string are equal
            {
                if(checkSortIdentical(word,currString) == 1) //identical ( 1 == true )
                {
                    if(counter == 0) //prints at first the current string
                    {
                        printf("%s",currString);
                        counter++;
                    }
                    //if we have more than one compatible string we print them with ~ between to seperate the words
                    else
                    {
                        printf("~%s",currString);
                    }
                }
            }
            free(currString); //in order to free the space we used
        }
    }

}

void firstFunction(char* word, char* text)
{
    int baseValue = calcGimatricValue(word); //calculates the gematric value of the word
    int counter = 0;
    //going through all the chars in the text
    for(unsigned long i = 0; i < strlen(text); i++)
    {
        char* first = (text+i); //first char in the string text, i moves the pointer by 1 to the next char at every iteration
        // if the char isn't a letter --> don't calculate it
        if((*(first) > 'Z' || *(first) < 'A')  && (*(first) > 'z' || *(first) < 'a'))
        {
            continue;
        }
        //running over the current text
        //index i defines the current text "first" to start from index i,
        //index j defines the current text "first" to end at index j.
        for(unsigned long j = strlen(first); j > 0;j--)
        {
            char* currString = (char*)malloc(sizeof (char) * (j+1)); //the string part we want to check
            if(currString == NULL)
            {
                break;
            }
            strncpy(currString,first,j); //curr receives the string "first" values until index j
            // if the char isn't a letter --> don't calculate it
            if((*(currString) > 'Z' || *(currString) < 'A')  && (*(currString) > 'z' || *(currString) < 'a'))
            {
                free(currString);
                continue;
            }
            // if the char isn't a letter --> don't calculate it
            if(((currString[j-1] > 'Z' || currString[j-1] < 'A'))  && ((currString[j-1] > 'z' || currString[j-1] < 'a')))
            {
                free(currString);
                continue;
            }
            currString[j] = '\0';
            int currValue = calcGimatricValue(currString); //the gematric value of string "curr"
            if(currValue == baseValue) //checking if the gematric values of the word and the current string are equal
            {
                if(counter == 0) //prints at first the current string
                {
                    printf("%s",currString);
                    counter++;
                }
                //if we have more than one compatible string we print them with ~ between to seperate the words
                else
                {
                    printf("~%s",currString);
                }
            }
            free(currString); //in order to free the space we used
        }
    }
}


int main() {

    char* word = (char*)malloc(WORD); //will hold the String that represents the input word
    if(word == NULL)
    {
        return 0;
    }
    int counter = 0;
    for(int i =0; i < WORD;i++)
    {
        char c = getc(stdin);
        if(c == '\n' || c == ' ' || c == '\t') //end of word
        {
            break;
        }
        else //not the end of the word
        {
            word[i] = c; //getting the input values of the word into the string "word"
            counter++;
        }
    }
    word[counter] = '\0'; //the end of the string "word"


    char* txt = (char*)malloc(TXT); //will hold the String that represents the input text
    if(txt == NULL)
    {
        return 0;
    }
    counter = 0;
    for(int i =0; i < TXT;i++)
    {
        char c = getc(stdin);
        if(c == '~') //the end of the string "text"
        {
            break;
        }
        else //not the end of the text
        {
            txt[i] = c; //getting the input values of the text into the string "text"
            counter++;
        }
    }
    txt[counter] = '\0'; //the end of the string "text"

    //first question:
    printf("Gematria Sequences: ");
    firstFunction(word,txt);
    printf("\n");

    //second question:
    printf("Atbash Sequences: ");
    secondFunction(word,txt);
    printf("\n");

    //third question:
    printf("Anagram Sequences: ");
    thirdFunction(word,txt);

    free(txt);
    free(word);
    return 0;
}
