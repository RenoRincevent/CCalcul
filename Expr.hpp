#ifndef EXPR_HPP
#define EXPR_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <locale>
#include <list>
#include <map>
#include "ExprToken.hpp"
#include <exception>

class Expr{
  public:
    // struct ExprToken {
    //   int type; //1 pour operateur, 2 pour operande, 3 pour paranthese
    //   float val;
    //   char op;
    // };
    // Construit une expression a partir du texte
    Expr ( const char * str );
    // Retourne la valeur de l'expression
    float eval(std::map<std::string,float>& memoire, std::map<std::string,FunSpeToken>& memoireSpe,std::map<std::string,FunPHToken>& memoireDyn);
    // Affiche la représentation interne
    void print();
    //evalue si un char est un operateur
    bool isOp(const char& c);

    bool isNum(const std::string& s);
    bool isVariable(const std::string& s);
    //Evalue si une chaine de caractere est une fonction
    bool isFun(const std::string& fct);
    bool isFunSpe (const std::string& fct);
    bool isLerp (const std::string& fct);
    bool isPolynome (const std::string& fct);
    //Utiliser pour prendre tout les arguments d'une fonction dans le bon ordre
    std::vector<float> reverseArgs(std::vector<float> v);
    std::vector<std::string> reverseStr(std::vector<std::string> v);
    //Separe la chaine de caractere passee en entree selon le delimiteur specifie
    std::vector<std::string> split(const std::string& s);
    // std::vector<std::string> split(const std::string& s, char delim);
    //creer l'expression en notaton polonaise inversee
    std::stack<ExprToken*> rpn(std::vector<std::string> chaine);
  private:
    const char * str;
    std::stack<ExprToken*> reversePolish;

};

#endif
