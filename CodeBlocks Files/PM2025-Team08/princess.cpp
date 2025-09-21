#include "princess.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <iomanip>

void Attribute::Create(const char *attr_name, int value)
{
    if (attr_name != nullptr && value >= 0 && value <= 999)
    {
        strncpy(name, attr_name, MaxLenTitleName - 1);
        name[MaxLenTitleName - 1] = '\0';
        val = value;
    }
}

void Attribute::Print() const
{
    std::cout << std::right << std::setw(18) << name << "  " << std::setw(3) << val << "  ";
    int stars = val / 10;
    for (int i = 0; i < stars; ++i)
    {
        std::cout << "*";
    }
    std::cout << std::endl;
}

void Attribute::AddValue(int increment)
{
    int newVal = val + increment;
    if (newVal >= 0 && newVal <= 9999999)
    {
        val = newVal;
    }
    else if (newVal > 9999999)
    {
        val = 9999999;
        std::cout << "Value capped at 9999999!" << std::endl;
    }
    else
    {
        val = 0;
        std::cout << "Value cannot go below 0!" << std::endl;
    }
}

void Princess::AddAttribute(Attribute attr)
{
    if (num_attrs < MaxNumAttributes)
    {
        attributes[num_attrs] = attr;
        num_attrs++;
    }
    else
    {
        std::cout << "Maximum number of attributes reached!" << std::endl;
    }
}

void remove_newlines(char* str) {
    char* dst = str;  // Pointer to write to
    while (*str) {
        if (*str != '\n' && *str != '\r') {
            *dst++ = *str;  // Copy the character without newlines
        }
        str++;  // Move to the next character in the original string
    }
    *dst = '\0';  // Null-terminate the new string
}

Attribute *Princess::GetAttribute(const char *attr_name)
{
    for (int i = 0; i < num_attrs; i++)
    {
        char newAttrName[20] = {};
        strcpy(newAttrName, attr_name);
        remove_newlines(newAttrName);
        // printf("%d  %s | %s\n", i, newAttrName, attributes[i].name);
        if (strcmp(attributes[i].name, newAttrName) == 0)
        {
            return &attributes[i];
        }
    }
    return nullptr;
}

void Princess::Print() const
{
    for (int i = 0; i < num_attrs; i++)
    {
        attributes[i].Print();
    }
}

void Princess::LoadAttributesFromFile(const char *filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line) && num_attrs < MaxNumAttributes)
        {
            if (!line.empty())
            {
                Attribute attr;
                attr.Create(line.c_str(), 0);
                AddAttribute(attr);
            }
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}
