#include "parser.h"
using namespace std;

int main()
{
    string input = "(3 + 5) * x - 2 / (y + 4)";
    // string input = "(3 + 2)";

    Parser parser(input);
    auto expr =parser.parse();
    expr->print();

    return 0;
}
