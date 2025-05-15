#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "program.h"
#include "student.h"

int main(int argc, char *argv[])
{
    if(argc > 3 || argc == 1)
    {

//        ProgramList lst = {};
//        Program *pc = AddProgram(&lst, "ai");
//        AddCourse(pc,"computer programming");
//
//        pc = AddProgram(&lst, "digimusic");
//        AddCourse(pc,"music-history");
//
//        for(int i=0; i<lst.sz; i+=1)
//        {
//            Print(&lst.programs[i]);
//        }

//        University uni = {};
//        Student *stu = FindStudent(&uni, "001");
//        if(stu==nullptr)
//        {
//            stu=AddStudent(&uni,"001");
//            AddCourse(FindStudent(&uni, "001"), "computer programming");
//        }
//
//        stu = FindStudent(&uni, "002");
//        if(stu==nullptr)
//        {
//            stu=AddStudent(&uni,"002");
//            AddCourse(FindStudent(&uni, "002"), "computer programming");
//            AddCourse(FindStudent(&uni, "002"), "TEST");
//        }
//
//        for(int i=0; i<(uni.sz); i+=1)
//            {
//                if(uni.stu[i].sz==1)
//                {
//                    printf("%s -- %d course.\n", uni.stu[i].id, 1);
//                }
//                else
//                {
//                    printf("%s -- %d courses.\n", uni.stu[i].id, uni.stu[i].sz);
//                }
//
//            }
    }

    if(argc==2)
    {
        if(strcmp(argv[1], "-p") == 0)
        {
            FILE *profp = fopen("_programs-all.txt","r");
            if(profp == nullptr)
            {
                printf("File not found.\n");
                return -1;
            }
            char progname[30]= {};

            ProgramList p;

            while (fscanf(profp, "%s", progname)==1)
            {
                //printf("%s\n",progname);
                char filename[50]= {};
                sprintf(filename, "program-%s.txt", progname);

                FILE *infp = fopen(filename, "r");
                if(infp==nullptr)
                {
                    continue;
                }

                Program *pc = AddProgram(&p, progname);

                char coursename[30]= {};
                while(fscanf(infp, "%s", coursename)==1)
                {

                    //printf("%s\n",coursename);
                    AddCourse(pc, coursename);
                }

                fclose(infp);
            }
            for(int i=0; i<p.sz; i+=1)
            {
                Print(&p.programs[i]);
            }

            fclose(profp);
        }

        else if(strcmp(argv[1],"-s")==0)
        {
            FILE *coufp = fopen("_courses-all.txt","r");
            if(coufp == nullptr)
            {
                printf("File not found.\n");
                return -1;
            }
            char courname[30]= {};

            University uni;

            while (fscanf(coufp, "%s", courname)==1)
            {
                char filename[40]= {};
                sprintf(filename, "%s.txt", courname);

                FILE *infp = fopen(filename, "r");
                if(infp==nullptr)
                {
                    continue;
                }

                char stuid[30]= {};
                while(fscanf(infp, "%s", stuid)==1)
                {
                    if(FindStudent(&uni, stuid)==nullptr)
                    {
                        AddStudent(&uni, stuid);
                    }

                    AddCourse(FindStudent(&uni, stuid), courname);
                }

            }

            for(int i=0; i<(uni.sz); i+=1)
            {
                if(uni.stu[i].sz==1)
                {
                    printf("%s -- %d course.\n", uni.stu[i].id, 1);
                }
                else
                {
                    printf("%s -- %d courses.\n", uni.stu[i].id, uni.stu[i].sz);
                }

            }

            fclose(coufp);
        }

    }
    if(argc==3)
    {
        if(strcmp(argv[1],"-w")==0)
        {
            FILE *profp = fopen("_programs-all.txt","r");
            FILE *coufp = fopen("_courses-all.txt","r");
            FILE *outfp = fopen(argv[2],"a");

            if(profp == nullptr)
            {
                printf("Programs file not found.\n");
                return -1;
            }

            if(coufp == nullptr)
            {
                printf("Courses file not found.\n");
                return -1;
            }

            if(outfp == nullptr)
            {
                printf("Output file not creatable.\n");
                return -1;
            }

            char courname[30]= {};

            University uni;

            while (fscanf(coufp, "%s", courname)==1)
            {
                char filename[40]= {};
                sprintf(filename, "%s.txt", courname);

                FILE *infp = fopen(filename, "r");
                if(infp==nullptr)
                {
                    continue;
                }

                char stuid[30]= {};
                while(fscanf(infp, "%s", stuid)==1)
                {
                    if(FindStudent(&uni, stuid)==nullptr)
                    {
                        AddStudent(&uni, stuid);
                    }

                    AddCourse(FindStudent(&uni, stuid), courname);
                }

            }

            char progname[30]= {};

            ProgramList p;

            while (fscanf(profp, "%s", progname)==1)
            {
                //printf("%s\n",progname);
                char filename[50]= {};
                sprintf(filename, "program-%s.txt", progname);

                FILE *infp = fopen(filename, "r");
                if(infp==nullptr)
                {
                    continue;
                }

                Program *pc = AddProgram(&p, progname);

                char coursename[30]= {};
                while(fscanf(infp, "%s", coursename)==1)
                {

                    //printf("%s\n",coursename);
                    AddCourse(pc, coursename);
                }

                fclose(infp);
            }

            for (int stun = 0; stun < uni.sz; stun+=1)
            {
                Student *cstu = &uni.stu[stun];
                fprintf(outfp, "%s\n", cstu->id);

                for (int i = 0; i < p.sz; i+=1)
                {
                    Program *cp = &p.programs[i];
                    if (!cp->sz) break;

                    int cc = 0;
                    for (int j = 0; j < cp->sz; j+=1)
                    {
                        for (int stuc = 0; stuc < cstu->sz; stuc+=1)
                        {
                            if (strcmp(cstu->courses[stuc], cp->courses[j]) == 0)
                            {
                                cc+=1;
                                break;
                            }
                        }
                    }

                    fprintf(outfp, " %s: %d/%d\n", cp->name, cc, cp->sz);
                }
                fprintf(outfp, "\n");

            }

            fclose(profp);
            fclose(coufp);
            fclose(outfp);
        }
    }

    return 0;
}

