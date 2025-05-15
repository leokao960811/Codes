#include <stdio.h>
#include <string.h>

int main()
{

    int n=0, ch_case=1;

    while (scanf("%d", &n)==1)
    {
        int ans=0;

        for (int i=0; i<n; i+=1)
        {

            char str[31]= {};
            scanf("%30s", str);

            int cnt[26]= {};
            for (int i=0, sz=strlen(str); i<sz; i+=1)
            {
                cnt[str[i]-'a']+=1;
            }

            int flag=0;
            int inword=0;
            for (int i=0; i<26; i+=1)
            {
                if(cnt[i]==0) continue;
                inword+=1;

                for (int j=(i+1); j<26; j+=1)
                {
                    if(cnt[j]==0) continue;
                    if(cnt[i]==cnt[j]) flag=1;
                }
            }
            if (flag==0 && inword>1) ans+=1;
            //Remainder

            //for(int i=0; i<26; i+=1)
            //{
                //printf("%d ",cnt[i]);
            //}
            //printf("\n");
        }



        printf("Case %d: %d\n", ch_case, ans);
        ch_case+=1;

    }
}
