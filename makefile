CC = g++ -std=c++11
CFLAG = -c

all: tp1.o Expr.o ExprToken.o
	$(CC) tp1.o Expr.o ExprToken.o -o tp1

tp1.o: tp1.cpp Expr.hpp
	$(CC) $(CFLAG) tp1.cpp -o tp1.o

Expr.o: Expr.cpp Expr.hpp ExprToken.hpp BadExpressionException.hpp
	$(CC) $(CFLAG) Expr.cpp -o Expr.o

ExprToken.o: ExprToken.cpp ExprToken.hpp BadExpressionException.hpp
	$(CC) $(CFLAG) ExprToken.cpp -o ExprToken.o
clean:
	rm *.o
	rm tp1
