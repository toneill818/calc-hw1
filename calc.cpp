//
// Created by Thomas O'Neill on 9/24/15.
//
#include "lib/ast.cpp"
#include "lib/evaluate.cpp"
#include "lib/parser.cpp"

// Evaluates an equation from standard input
int main(){
    std::string equation;
    std::getline(std::cin,equation,'\n');
    Parser parser(equation);
    Expr* e ;
    e =parser.expr();
    Eval eval;
    e->accept(eval);
    std::cout<< std::endl << eval.value << std::endl;

    return 0;
}
