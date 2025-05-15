#include <stdio.h>
#include <string.h>
#include <ctype.h>
//Hardest question imo...


int ConvertToDigit(const char str[]){
    // Please convert to lowercase first
    char eng[10][20] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (int i = 0; i < 10; i++){
        if (strcmp(str, eng[i]) == 0) return i;
    }
    return 0;
}

int main(){
    int n = 0;
    scanf("%d", &n);

    if (n < 1 || n > 10) return 0;
    getchar();

    for (int line = 0; line < n; line+=1){

        char s[1000] = {'\0'};
        char words[100][20] = {'\0'};

        char ch;
        int charIndex = 0;
        int wordIndex = 0;

        while (scanf("%c", &ch) == 1 && ch != '\n'){
            if (ch != ' '){
                words[wordIndex][charIndex] = tolower(ch);
                charIndex += 1;
            } else {
                charIndex = 0;
                wordIndex += 1;
            }
        }
        int wordsLength = wordIndex + 1;

        for (int word = 0; word < wordsLength; word+=1){
            printf("%d", ConvertToDigit(words[word]));
        }
        printf("\n");
    }
}

