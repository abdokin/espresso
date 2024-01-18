#include <iostream>
#include <string>
#include "expression.h"
using namespace std;

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
    string value;
};

class Tokenizer
{
public:
    Tokenizer(const string &input) : input(input), position(0) {}

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
            string numberValue;
            numberValue += currentChar;
            while (position < input.length() && isdigit(input[position]))
            {
                numberValue += input[position++];
            }
            return {NUMBER, numberValue};
        }
        else if (isalpha(currentChar))
        {
            string variableValue;
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

private:
    string input;
    size_t position;
};

class Parser
{
public:
    Parser(const string &input) : tokenizer(input), currentToken(tokenizer.nextToken()) {}

    void parse()
    {
        expression();
    }

private:
    void expression()
    {
        // expression  → term ( '+' term | '-' term )*
        term();
        while (currentToken.type == PLUS || currentToken.type == MINUS)
        {
            Token op = currentToken;
            match(currentToken.type);

            cout << " " << op.value << " ";
            term();
        }
    }

    void term()
    {
        // term        → factor ( '*' factor | '/' factor )*
        factor();
        while (currentToken.type == MULTIPLY || currentToken.type == DIVIDE)
        {
            Token op = currentToken;
            match(currentToken.type);
            cout << " " << op.value << " ";
            factor();
        }
    }
    void factor()
    {
        // factor      → base ( '^' exponent )?
        base();
        if (currentToken.type == EXP)
        {
            match(EXP);
            exponent();
        }
    }
    void number()
    {
        Number numb(currentToken.value);
        match(NUMBER);
        numb.print();
    }
    void variable()
    {
        Variable var(currentToken.value);
        match(VARIABLE);
        var.print();
    }

    void base()
    {
        // base  → number | variable | '(' expression ')'
        switch (currentToken.type)
        {
        case NUMBER:
            number();
            break;
        case VARIABLE:
            variable();
            break;
        // case LPARE:
        //     expression();
        //     break;
        default:
            cout << "(";

            match(LPARE);
            expression();
            match(RPARE);
            cout << ") ";
            break;
        }
    }
    void exponent()
    {
        // exponent → number | variable
        switch (currentToken.type)
        {
        case NUMBER:
            number();
            break;
        default:
            variable();
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
            cout << "Error: Expected " << tokenTypeToStr(expectedType) << " but got " << tokenTypeToStr(currentToken.type) << endl;
            // Handle error as needed (throw exception, exit program, etc.)
        }
    }

    string tokenTypeToStr(TokenType type)
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

    Tokenizer tokenizer;
    Token currentToken;
};

int main()
{
    string input = "(3 + 5) * x - 2 / (y + 4)";
    Parser parser(input);
    parser.parse();

    return 0;
}
