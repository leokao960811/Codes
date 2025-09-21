#ifndef PRINCESS_H
#define PRINCESS_H

const int MaxLenTitleName = 18;
const int MaxNumAttributes = 10;

struct Attribute
{
  char name[MaxLenTitleName] = {};
  int val = 0;

  void Create(const char *attr_name, int value);
  void Print() const;
  void AddValue(int increment);
};

struct Princess
{
  char name[MaxLenTitleName] = {};
  int money = 1000;
  Attribute attributes[MaxNumAttributes] = {};
  int num_attrs = 0;

  void AddAttribute(Attribute attr);
  Attribute *GetAttribute(const char *attr_name);
  void Print() const;
  void LoadAttributesFromFile(const char *filename);
};

#endif