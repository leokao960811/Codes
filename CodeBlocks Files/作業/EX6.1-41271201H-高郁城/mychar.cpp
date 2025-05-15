#include <stdio.h>

//ch-'a'+'A'
int isupper2(int ch)
{
    return (ch-'A'>=0 && ch-'A'<26);
}

int islower2(int ch)
{
    return (ch-'a'>=0 && ch-'a'<26);
}

int isalpha2(int ch)
{
    return (isupper2(ch) || islower2(ch));
}

int isdigit2(int ch)
{
    return (ch-'0'>=0 && ch-'0'<10);
}

int toupper2(int ch)
{
    if (islower2(ch)) return (ch-'a'+'A');
    else return ch;
}

int tolower2(int ch)
{
    if (isupper2(ch)) return (ch-'A'+'a');
    else return ch;
}
