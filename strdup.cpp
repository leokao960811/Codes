#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strdup(const char *s)
{
    char *ptr = (char*) malloc(sizeof(char)*1000);
    if (ptr==nullptr) return ptr;

    strcpy(ptr,s);

    return ptr;
}

int main()
{
    char *name=strdup("tcchiang");

    if(name) //Check if sduplication is successful
    {
        printf("%s",name);
    }

    free(name);
    name = nullptr;
}
