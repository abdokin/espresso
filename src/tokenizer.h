#pragma once
#include <iostream>
#include <string>

enum TokenType
{
    END,
    LPARE,
    RPARE,
    NUMBER,
    VARIABLE,
    PLUS,
    MINUS,
    MULTIPLY,
    EXP,
    DIVIDE
};

struct Token
{
    TokenType type;
    std::string value;
};

class Tokenizer
{
public:
    Tokenizer(const std::string &input) : input(input), position(0) {}

    Token nextToken()
    {
        if (position >= input.length())
        {
            return {END, ""};
        }

        char currentChar = input[position++];

        if (currentChar == '(')
        {
            return {LPARE, ""};
        }
        else if (currentChar == ')')
        {
            return {RPARE, ""};
        }
        else if (isdigit(currentChar))
        {
            std::string numberValue;
            numberValue += currentChar;
            while (position < input.length() && isdigit(input[position]))
            {
                numberValue += input[position++];
            }
            return {NUMBER, numberValue};
        }
        else if (isalpha(currentChar))
        {
            std::string variableValue;
            variableValue += currentChar;
            while (position < input.length() && isalnum(input[position]))
            {
                variableValue += input[position++];
            }
            return {VARIABLE, variableValue};
        }
        else if (currentChar == '+')
        {
            return {PLUS, "+"};
        }
        else if (currentChar == '-')
        {
            return {MINUS, "-"};
        }
        else if (currentChar == '*')
        {
            return {MULTIPLY, "*"};
        }
        else if (currentChar == '/')
        {
            return {DIVIDE, "/"};
        }
        else if (currentChar == '^')
        {
            return {EXP, "^"};
        }
        // Ignore other characters
        return nextToken();
    }

    static std::string tokenTypeToStr(TokenType type)
    {
        switch (type)
        {
        case END:
            return "END";
        case LPARE:
            return "LPARE";
        case RPARE:
            return "RPARE";
        case NUMBER:
            return "NUMBER";
        case VARIABLE:
            return "VARIABLE";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case MULTIPLY:
            return "MULTIPLY";
        case DIVIDE:
            return "DIVIDE";
        case EXP:
            return "DIVIDE";
        default:
            return "UNKNOWN";
        }
    }

private:
    std::string input;
    size_t position;
};