#pragma once
#include <iostream>

struct Base
{
};

struct Exponent {

};

struct Number :public Base
{
    std::string v;
    Number(std::string value) : v(value){};
    void print() {
        std::cout << "<number="<<v<<">";
     }
};

struct Variable :public Base
{
    std::string name;
    Variable(std::string n) : name(n){};
    void print() {
        std::cout << "<variable='"<<name<<"'>";
     }
};




