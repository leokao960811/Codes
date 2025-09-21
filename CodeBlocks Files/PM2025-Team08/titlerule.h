#ifndef TITLERULE_H
#define TITLERULE_H
#include "princess.h"

constexpr int MaxLenTName = 17;
constexpr int MaxNumRules = 17;

struct Condition
{
    char lhs[MaxLenTName] = {}, rhs[MaxLenTName] = {};
    char relation = ' '; // either '>' or '<'
};

struct TitleRule
{
    char title_[18] = {};
    Condition conditions_[10] = {};
    int num_conditions_ = 0;
};

struct TitleRuleSet
{
    TitleRule rules[MaxNumRules] = {};
    int num_rules = 0;
};

TitleRuleSet *init_rule(const char filename[]);
//void Print(TitleRuleSet *ts);
int GetValue(const Princess *p, const char str[]);
bool Satisfy(const Princess *p);
char* Profession(const Princess *p, const TitleRuleSet *Ts);
const Attribute *GetAttribute(const Princess *p, const char name[]);
#endif
