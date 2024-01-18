#include <iostream>
#include <optional> // Add this line for optional
#include <cctype>
using namespace std;

enum TokenType
{
    PLUS,
    MINUS,
    DIVID,
    MULTI,
    POWER,
    NUMBE,
    VARIA,
    DOT,
    LPARE,
    RPARE,
    END,

};

string tokenTypeToStr(TokenType t)
{
    switch (t)
    {
    case PLUS:
        return "PLUS";
    case MINUS:
        return "MINUS";
    case DIVID:
        return "DIVID";
    case MULTI:
        return "MULTI";
    case POWER:
        return "POWER";
    case NUMBE:
        return "NUMBE";
    case VARIA:
        return "VARIA";
    case DOT:
        return "DOT";
    case LPARE:
        return "LPARE";
    case RPARE:
        return "RPARE";
    case END:
        return "END";
    default:
        return "unkownToken";
    }
}
struct Token
{
    TokenType type;
    string value;
};

struct Tokenizer
{
    string input;
    size_t position;
    Tokenizer(string s) : input(s), position(0){};
    bool next(char &c)
    {
        if (position < input.size())
        {
            c = input[position++];
            return true;
        }
        return false;
    }

    bool peek(char &c)
    {
        if (position < input.size())
        {
            c = input[position];
            return true;
        }
        return false;
    }
    Token advance(Token &t)
    {
        char v;
        if (peek(v) && v != t.value[0])
        {
            cout << "[error] Unexpected token advance [expected] char=" << v << "got=" << t.value << endl;
            exit(EXIT_FAILURE);
        }
        next(v);
        return t;
    }
    Token nextToken()
    {
        char currentChar;

        // skip whitespaces
        while (peek(currentChar) && isspace(currentChar))
        {
            next(currentChar);
        }
        Token token;
        token.value = currentChar;

        // Tokenize based on the current character
        switch (currentChar)
        {
        case '+':
            token.type = PLUS;
            break;
        case '-':
            token.type = MINUS;
            break;

        case '*':
            token.type = MULTI;
            break;

        case '/':
            token.type = DIVID;
            break;

        case '^':
            token.type = POWER;
            break;

        case '.':
            token.type = DOT;
            break;

        case '(':
            token.type = LPARE;
            break;

        case ')':
            token.type = RPARE;
            break;

        default:
            // Check for numbers
            if (isdigit(currentChar))
            {
                while (peek(currentChar) && (isdigit(currentChar) || currentChar == '.'))
                {
                    token.value += currentChar;
                    next(currentChar);
                }
                token.type = NUMBE;
                return token;
            }
            // Check for variables
            else if (isalpha(currentChar) || currentChar == '_')
            {
                while (peek(currentChar) && (isalpha(currentChar) || isdigit(currentChar) || currentChar == '_'))
                {
                    token.value += currentChar;
                    next(currentChar);
                }
                token.type = VARIA;
                return token;
            }
            else
            {
                if (position != input.length())
                {
                    // Invalid character
                    cout << "[error]: Invalid character '" << currentChar << "'"
                         << "at " << position << endl;
                }
                else
                {
                    token.type = END;
                    token.value = (char)0;
                    return token;
                }
            }
            break;
        }
        return advance(token);
    }
};


struct Lexer
{
    
};


int main(int argc, char **argv)
{
    char *programm = argv[0];
    if (argc < 2)
    {
        cout << "usage \n"
             << programm << " <input-file> \n";
        exit(EXIT_FAILURE);
    }
    cout << "Expression parser:\n";

    Tokenizer tokenizer("3 + 4 * (5 - 2)");
    Token token = tokenizer.nextToken();
    while (token.type != END)
    {
        // Process the character
        cout << "[token] type=" << tokenTypeToStr(token.type) << " value=" << token.value << endl;
        token = tokenizer.nextToken();
    }
    return 0;
}

