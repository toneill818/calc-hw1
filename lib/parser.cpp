#ifndef PARSER_CPP
#define PARSER_CPP

#include <string>
#include <cctype>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include "ast.cpp"

	struct Parser{
	private:
		std::string equation;
		int lookAhead;
		int numOpenParen;

		// Clear all whitespace (spaces and tabs) from the string.
		void removeSpaces(std::string &input){
			input.erase(std::remove(input.begin(),input.end(),' '),input.end());
			input.erase(std::remove(input.begin(),input.end(),'\t'),input.end());
		}

		// Increments the lookAhead to the next character
		void next(){
			lookAhead++;
		}

	public:
		// Prepare the parser by removing the whitespaces from the equation and setting the lookahead to 0
		Parser(std::string e):equation(e), lookAhead(0), numOpenParen(0){
			removeSpaces(equation);
		}

		Parser():equation(""),lookAhead(0), numOpenParen(0){}

		// An expr is a + or - operation or a factor. This give us proper order of operations by splitting
		// + and - from *, % and /.
		Expr* expr(){
			// Get e1 which cannot be a nullptr
			Expr* e1 = Factor();

			// Continue to loop until we are out of expressions
			while(true){
				if(equation[lookAhead] == '+'){
					next();
					Expr* e2 = Factor();
					e1 = new Add(e1,e2);
				}else if(equation[lookAhead] == '-'){
					next();
					Expr* e2 = Factor();
					e1 = new Subtract(e1,e2);
				}else{
					break;
				}
			}
			return e1;
		}

		// A factor is *, /, % or a term.
		Expr* Factor(){
			// Get the first term in the factor. e1 cannot be a nullptr
			Expr* e1 = T();

			// Loop while we still have factors
			while(true){
				if(equation[lookAhead] == '*'){
					next();
					Expr* e2 = T();
					e1 = new Multiply(e1,e2);
				}else if(equation[lookAhead] == '/'){
					next();
					Expr* e2 = T();
					e1 = new Divide(e1,e2);
				}else if(equation[lookAhead] == '%') {
					next();
					Expr* e2 = T();
					e1 = new Mod(e1,e2);
				// Check for a closing parenthesis. If detected check that there was an open parenthesis and return
				// the factor/expression.
				}else if(equation[lookAhead] == ')') {
					if(numOpenParen == 0){
						std::cout << "Error extra ) found\n";
						exit(-3);
					}
					numOpenParen--;
					next();
					return e1;
				}else{
					break;
				}
			}
			return e1;
		}

		// Term is simply a digit 0-9
		Expr* T(){
			// Check if we have an open Parenthesis and begin a new expression parse
			// This will build the entire expression ast that will then get passed back
			// up when the closing parenthesis is found.
			if(equation[lookAhead] == '('){
				numOpenParen++;
				next();
				return(expr());
			}

			if(std::isdigit(equation[lookAhead])){
				return new Integer(atoi(&equation[lookAhead++]));
			}else{
				std::cout << "Error: expected a digit but got " << equation[lookAhead] << std::endl;
				exit(-4);
			}
		}
	};

#endif
