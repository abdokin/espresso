#pragma once
#include <iostream>
#include <string>
#include "expression.h"
#include "tokenizer.h"

class Parser
{
public:
    Parser(const std::string &input) : tokenizer(input), currentToken(tokenizer.nextToken()) {}

    std::shared_ptr<Expression> parse()
    {
        return expression();
    }

private:
    std::shared_ptr<Expression> expression()
    {
        // expression  → term ( '+' term | '-' term )*
        auto exp = Expression(term());
        while (currentToken.type == PLUS || currentToken.type == MINUS)
        {
            exp.ops.push_back(currentToken);
            match(currentToken.type);
            exp.rts.push_back(term());
        }

        return std::make_shared<Expression>(exp);
    }

    std::shared_ptr<Term> term()
    {
        // term        → factor ( '*' factor | '/' factor )*
        auto term = Term(factor());
        while (currentToken.type == MULTIPLY || currentToken.type == DIVIDE)
        {
            term.ops.push_back(currentToken);
            match(currentToken.type);
            term.rfs.push_back(factor());
        }

        // term.print();
        return std::make_shared<Term>(term);
    }
    std::shared_ptr<Factor> factor()
    {
        // factor      → base ( '^' exponent )?
        auto b = base();
        if (currentToken.type == EXP)
        {
            match(EXP);
            auto exp = exponent();
            Factor f(b, exp);
            return std::make_shared<Factor>(f);
        }
        Factor f(b, nullptr);
        return std::make_shared<Factor>(f);
    }
    std::shared_ptr<Number> number()
    {
        auto numberPtr = std::make_shared<Number>(currentToken.value);
        match(NUMBER);
        return numberPtr;
    }
    std::shared_ptr<Variable> variable()
    {
        auto var = std::make_shared<Variable>(currentToken.value);
        match(VARIABLE);
        return var;
    }
    std::shared_ptr<Base> base()
    {
        std::shared_ptr<Expression> exp;
        switch (currentToken.type)
        {
        case NUMBER:
            return std::static_pointer_cast<Base>(number());
        case VARIABLE:
            return std::static_pointer_cast<Base>(variable());
        case LPARE:
            match(LPARE);
            exp = expression();
            exp->with_parent = true;
            match(RPARE);
            return std::static_pointer_cast<Expression>(exp);
        default:
            std::cerr << "Error: Unexpected token type " << currentToken.type << std::endl;
            exit(EXIT_FAILURE);
        }
        // UNREACHABLE
        return nullptr;
    }
    std::shared_ptr<Exponent> exponent()
    {
        // exponent → number | variable
        switch (currentToken.type)
        {
        case NUMBER:
            return std::static_pointer_cast<Exponent>(number());
        case VARIABLE:
            return std::static_pointer_cast<Exponent>(variable());
        default:
            std::cerr << "Error: Unexpected token type " << currentToken.type << std::endl;
            exit(EXIT_FAILURE);
            break;
        }
    }

    void match(TokenType expectedType)
    {
        if (currentToken.type == expectedType)
        {
            currentToken = tokenizer.nextToken();
        }
        else
        {
            std::cout << "Error: Expected " << tokenizer.tokenTypeToStr(expectedType) << " but got " << tokenizer.tokenTypeToStr(currentToken.type) << std::endl;
            // Handle error as needed (throw exception, exit program, etc.)
        }
    }

    Tokenizer tokenizer;
    Token currentToken;
};
