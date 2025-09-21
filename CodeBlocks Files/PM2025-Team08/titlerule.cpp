#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "titlerule.h"
#include "princess.h"
#include "place.h"

TitleRuleSet *init_rule(const char filename[]){
    static TitleRuleSet rule_set;
    rule_set.num_rules = 0;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: cannot open rule file \"%s\"\n", filename);
        return nullptr;
    }

    char line[100];
    TitleRule *current_rule = nullptr;

    while (fgets(line, sizeof(line), fp)) {
        size_t len = strlen(line);
        while (len > 0 && isspace(line[len - 1])) {
            line[--len] = '\0';
        }

        if (strlen(line) == 0) continue;


        if (line[strlen(line) - 1] == ':') {
            if (rule_set.num_rules >= MaxNumRules) break;

            current_rule = &rule_set.rules[rule_set.num_rules++];
            line[strlen(line) - 1] = '\0'; // 蝘駁膄 ':'
            strncpy(current_rule->title_, line, MaxLenTName);
            current_rule->num_conditions_ = 0;
        }
        else if (line[0] == '#') {
            current_rule = nullptr;
        }
        else if (current_rule != nullptr) {
            if (current_rule->num_conditions_ >= 10) continue;

            Condition *cond = &current_rule->conditions_[current_rule->num_conditions_++];
            sscanf(line, "%s %c %s", cond->lhs, &cond->relation, cond->rhs);
        }
    }

    fclose(fp);
    return &rule_set;
}

//void Print(TitleRuleSet *ts)
//{
//    printf("%d\n", ts->num_rules);
//    for(int i=0;i<ts->num_rules;i+=1)
//    {
//        printf("%s ",ts->rules[i].title_);
//        printf("%d\n", ts->rules[i].num_conditions_);
//        for(int j=0; j<ts->rules[i].num_conditions_; j+=1)
//        {
//            printf("%s %c %s\n", ts->rules[i].conditions_[j].lhs, ts->rules[i].conditions_[j].relation, ts->rules[i].conditions_[j].rhs);
//        }
//        printf("\n");
//    }
//}

// �ế�𪃾value or string
int GetValue(const Princess *p, const char str[])
{
    if (isdigit(str[0]))
    {
        return atoi(str); // �𥅾�糓�彍摮梹�𣬚凒�𦻖頧㗇��
    }
    else
    {
        // �𥅾�糓撅祆�批�滨迂嚗䔶蝙�鍂 GetAttribute() �𪄳撠齿�匧惇�批��
        const Attribute *attr = GetAttribute(p, str);
        //printf("%s ",attr);
        if (attr != nullptr)
        {
            return attr->val;
        }
        else
        {
            // �𥅾撅祆�找�滚�睃銁嚗屸�鞱身�� 0 ��硋虾�𥼚�𥲤
            return 0;
        }
    }
}

const Attribute *GetAttribute(const Princess *p, const char name[])
{
    for (int i = 0; i < p->num_attrs; i++)
    {
        if (strcmp(p->attributes[i].name,name)==0) //別給我用 if(p->attributes[i].name==name !!!
        {
            return &(p->attributes[i]);
        }
    }
    return nullptr;
}

// return true if the condition is satisfied; otherwise, return false
bool Satisfy(const Princess *p, const Condition *cond)
{
    // remember that a condition, Charm < 50 is stored as
    // cond->lhs "Charm" -> the line of text!
    // cond->relation '<'
    // cond->rhs "50"

    int lhs = GetValue(p, cond->lhs);
    int rhs = GetValue(p, cond->rhs);

    //printf("%s %d, %s %d\n", cond->lhs, lhs, cond->rhs, rhs);

    if (cond->relation == '>')
    {
        if (lhs > rhs)
        {
            return true;
        }
    }
    else if (cond->relation == '<')
    {
        if (lhs < rhs)
        {
            return true;
        }
    }
    return false;
}

char* Profession(const Princess *p, const TitleRuleSet *Ts) {
    for (int i = 0; i < Ts->num_rules; ++i) {
        const TitleRule* rule = &Ts->rules[i];
        bool ok = true;

        for (int j = 0; j < rule->num_conditions_; ++j) {
            if (!Satisfy(p, &rule->conditions_[j])) {
                ok = false;
                break;
            }
        }

        if (ok) {
            return (char*)rule->title_;  // �𪄳��蝚砌��讠泵�����瑟平撠勗�𧼮��
        }
    }

    return (char*)"Nobody";  // �𥅾瘝埝�厩泵���遙雿閗�瑟平
}
