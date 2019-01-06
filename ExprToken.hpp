#ifndef EXPRTOKEN_HPP
#define EXPRTOKEN_HPP
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class ExprToken {
  private:
    int type;
  public:
    virtual float getVal() {return 1;};
    virtual char getOp() {return ' ';};
    virtual char getPar() {return ' ';};
    virtual std::string getVar() {return " ";}
    virtual std::string getFun() {return " ";}
    inline int getType(){return type;}
    inline void setType(int type){ExprToken::type = type;}
    ExprToken(int type):type(type) {};

    const float operFun (std::string fct, std::vector<float> x);
};

class EntToken: public ExprToken { // type 2
  private:
    float val;
  public:
    inline float getVal() override {return val;}
    inline void setVal(float val){EntToken::val = val;}
    EntToken(int type, float val):ExprToken(type),val(val) {};
};

class OpToken: public ExprToken { //type 1
  private:
    char op;
  public:
    inline char getOp() override {return op;}
    inline void setOp(char op){OpToken::op = op;}
    OpToken(int type, char op):ExprToken(type),op(op) {};
};

class ParToken: public ExprToken { //type 3
  private:
    char par;
  public:
    inline char getPar() override {return par;}
    inline void setPar(char par) {ParToken::par = par;}
    ParToken(int type,char par):ExprToken(type),par(par) {};
};

class AlphaToken: public ExprToken { //type 4
  private:
    std::string var;
  public:
    inline std::string getVar() override {return var;}
    AlphaToken(int type, std::string var):ExprToken(type),var(var) {};
};

class FunToken: public ExprToken { //type 5
  private:
    std::string fct;
  public:
    inline std::string getFun() override {return fct;}
    FunToken(int type, std::string fct):ExprToken(type),fct(fct) {};
};

class FunSpeToken: public ExprToken { //type 6
  private:
    std::string fct;
    std::vector<float> v;
  public:
    inline std::string getFun() override {return fct;}
    inline std::vector<float> getArg() {return v;}
    FunSpeToken(int type, std::string fct, std::vector<float> v):ExprToken(type),fct(fct),v(v){};
};

class UnderScoreToken: public ExprToken{ //type 7
  private:
    char underScore;
  public:
    inline char getUnderScore() {return underScore;}
    UnderScoreToken():ExprToken(7),underScore('_') {};
};

class FunPHToken: public ExprToken { //type 8
  private:
    std::string fct;
    std::vector<std::string> args;
  public:
    inline std::vector<std::string> getArg() {return args;}
    inline std::string getFunPH() {return fct;}
    FunPHToken(std::string fct, std::vector<std::string> args): ExprToken(8), fct(fct),args(args) {};
};


// struct FunSpeToken {
//   int type; //1 pour operateur, 2 pour operande
// 	std::string fct;
// 	std::vector<float> v;;};

#endif
