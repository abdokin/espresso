#include <iostream>
#include <optional>  // Add this line for optional
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
};
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
    optional<Token> nextToken()
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
            }
            else
            {
                // Invalid character
                cout << "Error: Invalid character '" << currentChar << "'" << endl;
                return nullopt;
            }
            break;
        }

        return token;
    }
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
    char currentChar;
    while (tokenizer.next(currentChar))
    {
        // Process the character
        cout << "Current character: " << currentChar << endl;
    }
    return 0;
}
