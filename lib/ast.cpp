// Thomas O'Neill
#ifndef AST_CPP
#define AST_CPP
#include <iostream> 



	class Expr;
	class Integer;
	class Add;
	class Multiply;
	class Subtract;
	class Divide;
	class Mod;
	class Visitor;

	// Visitor class that will be used to evaluate and translate to posfix and sexpressions
	struct Visitor{
		virtual void visit(Integer const *e)=0;
		virtual void visit(Add const *e)=0;
		virtual void visit(Multiply const *e)=0;
		virtual void visit(Subtract const *e)=0;
		virtual void visit(Divide const *e)=0;
		virtual void visit(Mod const *e)=0;
	};

	// Base class that everything will derive from.
	struct Expr{
		virtual  ~Expr(){}
		// Pure vitural function inorder for all expressions to work with our visitor pattern
		virtual void accept(Visitor&)=0;
	};

	// Integer represents a single digit 0-9 and holds its value
	struct Integer:Expr{
		int n;
		Integer(int n):n(n){}
		void accept(Visitor &v){
			v.visit(this);
			return;
		}
	};

	// Add represents addion of 2 expressions (which will be evaluated down to the Integer class
	struct Add:Expr{
		Expr *e1, *e2;
		Add(Expr *e, Expr *ee ):e1(e), e2(ee){}
		void accept(Visitor &v){
			v.visit(this);
			return;
		}
	};

	// Multiply takes 2 expressions
	struct Multiply:Expr{
		Expr *e1, *e2;
		Multiply(Expr* e, Expr* ee):e1(e), e2(ee){}
		void accept(Visitor &v){
			v.visit(this);
			return;
		}
	};

	// Subtractions represents the subtraction of 2 expressions
	struct Subtract:Expr{
		Expr *e1, *e2;
		Subtract(Expr* e, Expr* ee):e1(e), e2(ee){}
		void accept(Visitor &v){
			v.visit(this);
			return;
		}
	};

	// Divide represents the division of 2 expressions
	struct Divide:Expr{
		Expr *e1, *e2;
		Divide(Expr* e, Expr* ee):e1(e), e2(ee){}
		void accept(Visitor &v){
			v.visit(this);
			return;
		}
	};

	// Mod is the modulous of 2 expressions
	struct Mod:Expr{
		Expr *e1, *e2;
		Mod(Expr* e, Expr* ee):e1(e), e2(ee){}
		void accept(Visitor &v){
			v.visit(this);
			return;
		}
	};


#endif
