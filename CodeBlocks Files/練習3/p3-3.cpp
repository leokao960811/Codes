#include <stdio.h>
#include <string.h>

int main()
{
    char str1[101]= {};
    while (scanf("%100s", str1)==1) //下次記得看清楚題目...
    {
        char str2[101]= {};
        scanf("%100s", str2);

        int cnt1[26]= {};
        int cnt2[26]= {};

        for (int i=0, sz=strlen(str1); i<sz; i+=1)
        {
            cnt1[str1[i]-'A']+=1;
        }

        for (int i=0, sz=strlen(str2); i<sz; i+=1)
        {
            cnt2[str2[i]-'A']+=1;
        }

        int flag=0;
        for(int i=0; i<26; i+=1)
        {
            if(cnt1[i]<=0) continue;
            for(int j=0; j<26; j+=1)
            {
                if(cnt2[j]<=0) continue;
                if(cnt2[j]==cnt1[i])
                {
                    cnt1[i]=-1;
                    cnt2[j]=-1;
                }
            }

        }
            for(int i=0; i<26; i+=1)
            {
                //printf("%d ", cnt1[i]);
                if(cnt1[i]>0) flag=1;
            }

            //printf("\n");

            for(int i=0; i<26; i+=1)
            {
                //printf("%d ", cnt2[i]);
                if(cnt2[i]>0) flag=1;
            }

            //printf("\n");

            if(flag==0) printf("YES\n");
            else printf("NO\n");

    }
}
