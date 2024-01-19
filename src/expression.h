#pragma once
#include <iostream>
#include "tokenizer.h"
struct Base;
struct Exponent;

struct Base
{
    virtual ~Base() {} // Make the base class polymorphic
    virtual void print() const = 0;
};
struct Exponent
{
    virtual ~Exponent(){};
    virtual void print() const = 0;
};

struct Number : public Base, public Exponent
{
    std::string v;

    Number(std::string value) : v(value) {}

    // Implementing the print function for numbers
    void print() const override
    {
        std::cout << "<number=" << v << ">";
    }
};

struct Variable : public Base, public Exponent
{
    std::string name;

    Variable(std::string n) : name(n) {}

    // Implementing the print function for variables
    void print() const override
    {

        std::cout << "<variable='" << name << "'>";
    }
};

// Factor class representing a factor in your grammar
struct Factor : public Base
{
    std::shared_ptr<Base> base;
    std::shared_ptr<Exponent> exponent;

    Factor(std::shared_ptr<Base> b, std::shared_ptr<Exponent> exp = nullptr)
        : base(b), exponent(exp) {}

    // Implementing the print function for factors
    void print() const override
    {
        // std::cout << "[factor]\n";
        base->print(); 
        if (exponent != nullptr)
        {
            exponent->print();
        }
    }
};

struct Term
{
    // term        → factor ( '*' factor | '/' factor )*
    std::shared_ptr<Factor> lf;
    std::vector<std::shared_ptr<Factor>> rfs;
    std::vector<Token> ops;

    Term(std::shared_ptr<Factor> left_factor) : lf(left_factor){};
    void print()
    {
        // std::cout << "[term]\n";
        lf->print();
        if (!rfs.empty())
        {
            for (size_t i = 0; i < rfs.size(); i++)
            {
                std::cout << " " << ops[i].value << " ";
                rfs[i]->print();
            }
        }
    }
};

struct Expression : public Base
{
    // expression  → term ( '+' term | '-' term )*
    std::shared_ptr<Term> lt;
    std::vector<std::shared_ptr<Term>> rts;
    std::vector<Token> ops;
    bool with_parent =false;
    Expression(std::shared_ptr<Term> left_term) : lt(left_term){};
    void print() const override
    {
        // std::cout << "[expr]\n";
        if(with_parent) std::cout << "(";
        lt->print();
        if (!rts.empty())
        {
            for (size_t i = 0; i < rts.size(); i++)
            {
                std::cout << " " << ops[i].value << " ";
                rts[i]->print();
            }
        }
        if(with_parent)  std::cout << ")";

    }
};