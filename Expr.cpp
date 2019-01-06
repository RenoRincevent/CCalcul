#include "Expr.hpp"
#include "BadExpressionException.hpp"

Expr::Expr ( const char * str ){
  Expr::str = str;
  Expr::reversePolish = Expr::rpn(Expr::split(str));
}

float Expr::eval(std::map<std::string,float>& memoire,std::map<std::string,FunSpeToken>& memoireSpe,std::map<std::string,FunPHToken>& memoireDyn){
  std::stack<ExprToken*> leRpn;
  std::stack<ExprToken*> li;

  leRpn = Expr::reversePolish;
  while(!leRpn.empty()){
    if(leRpn.top()->getType() == 2 || leRpn.top()->getType() == 4){//cas ou c'est un literral ou alpha
      if (leRpn.top()->getType() == 4 && memoireSpe.find(leRpn.top()->getVar()) != memoireSpe.end() && !li.empty()){ //test si cette clé existe dans memoireSpe
        std::vector<float> x;
        while(!li.empty() && li.top()->getType() != 1 && li.top()->getOp() != '$'){
          if(!li.empty() && li.top()->getType() == 2){
            x.push_back(li.top()->getVal());
            li.pop();
          }
          else if(!li.empty()){
            x.push_back(memoire[li.top()->getVar()]);
            li.pop();
          }
        }
        li.pop(); //suppression du $, on a recupere tout les argument de la fonction
        auto x2 = memoireSpe.at(leRpn.top()->getVar());
        auto x3 = x2.getArg();
        x.insert(x.end(), x3.begin(), x3.end());
        li.push(new EntToken(2, leRpn.top()->operFun(x2.getFun(),Expr::reverseArgs(x)) ) );
        leRpn.pop();
      }
      else if(leRpn.top()->getType() == 4 && memoireDyn.find(leRpn.top()->getVar()) != memoireDyn.end() && !li.empty()){ //test si cette clé existe dans memoireDyn
        std::vector<float> x;
        while(!li.empty() && li.top()->getType() != 1 && li.top()->getOp() != '$'){
          if(!li.empty() && li.top()->getType() == 2){
            x.push_back(li.top()->getVal());
            li.pop();
          }
          else if(!li.empty()){
            x.push_back(memoire[li.top()->getVar()]);
            li.pop();
          }
        }
        li.pop();
        FunPHToken x2 = memoireDyn.at(leRpn.top()->getVar());
        auto x3 = x2.getArg();
        x3 = reverseStr(x3);

        std::string fct = x2.getFunPH();
        std::vector<float> resFinalArgs;
        for (std::vector<std::string>::iterator it = x3.begin() ; it != x3.end(); ++it){
            if(isNum(*it)){
              resFinalArgs.push_back(std::stof(*it));
            }
            else{
              resFinalArgs.push_back(x.back());
              x.pop_back();
            }
        }
        //
        // for (std::vector<float>::iterator it = resFinalArgs.begin() ; it != resFinalArgs.end(); ++it){
        //   std::cout << *it << ' ';
        // }
        li.push(new EntToken(2, leRpn.top()->operFun(fct,resFinalArgs) ));
        leRpn.pop();
      }
      else{
        li.push(leRpn.top());
        leRpn.pop();
      }
    }
    else if(leRpn.top()->getType() == 1){//cas ou c'est un operateur
      if(leRpn.top()->getOp() == '$'){
        li.push(leRpn.top());
      }
      else{
        float elem1,elem2;
        std::string nomVar;
        if(li.top()->getType() == 2){ //le premier elem est une valeur
          elem1 = li.top()->getVal();
          li.pop();
        }
        else { //le premier elem est une variable
          elem1 = memoire[li.top()->getVar()];
          li.pop();
        }
        if(li.top()->getType() == 2){ // le second elem est une valeur
          elem2 = li.top()->getVal();
          li.pop();
        }
        else { // le second elem est une variable
          elem2 = memoire[li.top()->getVar()];
          nomVar = li.top()->getVar();
          li.pop();
        }

        if(leRpn.top()->getOp() == '+'){ li.push(new EntToken(2,elem2 + elem1)); }
        else if(leRpn.top()->getOp() == '-'){ li.push(new EntToken(2,elem2 - elem1)); }
        else if(leRpn.top()->getOp() == '*'){ li.push(new EntToken(2,elem2 * elem1)); }
        else if(leRpn.top()->getOp() == '/'){
          if(elem1 == 0){ throw BadExpressionException("Division par zero"); }
          else{li.push(new EntToken(2,elem2 / elem1));}
        }
        else if(leRpn.top()->getOp() == '='){
          memoire[nomVar] = elem1;
          li.push(new EntToken(2,elem1));
        }
      }
      leRpn.pop();
    }
    else if(leRpn.top()->getType() == 5){//cas ou c'est une fonction
      std::vector<float> x;
      std::vector<std::string> args;
      bool containUnderScore = false;
      while(li.top()->getType() != 1 && li.top()->getOp() != '$'){
        if(!li.empty() && li.top()->getType() == 2){
          x.push_back(li.top()->getVal());
          args.push_back(std::to_string(li.top()->getVal()));
          li.pop();
          if(li.top()->getType() == 7){
            containUnderScore = true;
            args.pop_back();
            args.push_back("_");
            li.pop();
          }
        }
        else if(!li.empty() && li.top()->getType() == 4){
          x.push_back(memoire[li.top()->getVar()]);
          args.push_back(li.top()->getVar());
          li.pop();
          if(li.top()->getType() == 7){
            containUnderScore = true;
            args.pop_back();
            args.push_back("_");
            li.pop();
          }
        }
      }
      li.pop(); //suppression du $, on a recupere tout les argument de la fonction
      std::string fct = leRpn.top()->getFun();
      leRpn.pop();
      if(!leRpn.empty() && leRpn.top()->getOp() == '=' && !containUnderScore){ //Affectation variable a fonction partiel
        memoireSpe.erase(li.top()->getVar());
        memoireSpe.insert(std::make_pair<std::string, FunSpeToken>(li.top()->getVar(), FunSpeToken(6,fct,x)) );
        leRpn.pop();
      }
      else if(!leRpn.empty() && leRpn.top()->getOp() == '=' && containUnderScore){ //Affectation variable a fonction partiel avec underscore
        memoireDyn.erase(li.top()->getVar());
        memoireDyn.insert(std::make_pair<std::string, FunPHToken>(li.top()->getVar(), FunPHToken(fct,args)) );
        leRpn.pop();
      }
      else{
        li.push(new EntToken(2, leRpn.top()->operFun(fct,Expr::reverseArgs(x)) ) );
      }
    }
    else if(leRpn.top()->getType() == 7){ //Cas ou il y a un underscore (eval partiel) dans le rpn
      li.push(leRpn.top());
      leRpn.pop();
    }
  }
  while(li.size() != 1){
    float elem1,elem2;
    std::string nomVar;
    if(li.top()->getType() == 2){ //le premier elem est une valeur
      elem1 = li.top()->getVal();
      li.pop();
    }
    else { //le premier elem est une variable
      elem1 = memoire[li.top()->getVar()];
      li.pop();
    }
    if(li.top()->getType() == 2){ // le second elem est une valeur
      elem2 = li.top()->getVal();
      li.pop();
    }
    else { // le second elem est une variable
      elem2 = memoire[li.top()->getVar()];
      nomVar = li.top()->getVar();
      li.pop();
    }
    li.push(new EntToken(2, elem1 + elem2 ) );
  }

  // return 1;
  if(li.top()->getType() == 4){
    return memoire[li.top()->getVar()];
  }

  return li.top()->getVal();
}

void Expr::print(){
  std::stack<ExprToken*> li = Expr::reversePolish;
  while(!li.empty()){
    if(li.top()->getType() == 1){
      std::cout << li.top()->getOp() << " ";
      li.pop();
    }
    else if(li.top()->getType() == 2){
      std::cout << li.top()->getVal() << " ";
      li.pop();
    }
    else if(li.top()->getType() == 4){
      std::cout << li.top()->getVar() << " ";
      li.pop();
    }
    else if(li.top()->getType() == 5){
      std::cout << li.top()->getFun() << " ";
      li.pop();
    }
    else if(li.top()->getType() == 7){
      std::cout << "_" << " ";
      li.pop();
    }
  }
}

bool Expr::isFun (const std::string& fct){
  if (fct == "sin" || fct == "cos" || fct == "tan" || fct == "sqrt" || fct == "log" || fct == "exp"){
    return true;
  }
  return false;
}

bool Expr::isFunSpe (const std::string& fct){
  if (fct == "pow" || fct == "hypot"){
    return true;
  }
  return false;
}

bool Expr::isLerp (const std::string& fct){
  if(fct == "lerp"){ return true; }
  return false;
}

bool Expr::isPolynome (const std::string& fct){
  if(fct == "polynome"){return true;}
  return false;
}

bool Expr::isOp(const char& c){
  if(c == '+' || c == '-' || c == '*' || c == '/' || c== '='){
    return true;
  }
  return false;
}

std::vector<float> Expr::reverseArgs(std::vector<float> v) {
  std::vector<float> res;
  for (int i = v.size()-1; i >= 0; i--)
    res.push_back(v[i]);
  return res;
}

std::vector<std::string> Expr::reverseStr(std::vector<std::string> v){
  std::vector<std::string> res;
  for (int i = v.size()-1; i >= 0; i--)
    res.push_back(v[i]);
  return res;
}

bool Expr::isNum(const std::string& s){
  if((s.at(0) >= '0' && s.at(0) <= '9') || (s.size()>=2 && s.at(1) >= '0' && s.at(1) <= '9')){
    return true;
  }
  return false;
}

bool Expr::isVariable(const std::string& s){//A FAIRE !!!!
  return false;
}

std::vector<std::string> Expr::split(const std::string& s){
  std::vector<std::string> chaine;
  std::string mot="";
  for(auto i=0; i<s.size()-1; i++){
    if(isdigit(s.at(i)) || s.at(i) == '.'){
      mot.push_back(s.at(i));
      if(!isdigit(s.at(i+1)) && s.at(i+1)!= '.'){
        if(chaine.size()>=1 && chaine.back() == "-"){//cas ou la valeur est négative
          chaine.pop_back();
          if(chaine.size()>=2 && Expr::isNum(chaine.at(chaine.size()-1))){
            chaine.push_back("+");
          }
          mot = "-"+mot;
        }
        chaine.push_back(mot);
        mot="";
      }
    }
    else if(isOp(s.at(i)) || s.at(i)=='(' || s.at(i)==')' || s.at(i)=='=' || s.at(i) == ','){
      if(s.at(i)=='(' && chaine.size()==1 && chaine.back() == "-"){ //cas ou on a -(expression)
        chaine.pop_back();
        chaine.push_back("-1");
        chaine.push_back("*");
      }
      mot.push_back(s.at(i));
      chaine.push_back(mot);
      mot="";
    }
    else if(isalpha(s.at(i))){
      mot.push_back(s.at(i));
      if(!isalpha(s.at(i+1))){
        if(chaine.size()>=1 && chaine.back() == "-"){//cas ou la variable est négative
          chaine.pop_back();
          chaine.push_back("-1");
          chaine.push_back("*");
        }
        if ((Expr::isFun(mot) || Expr::isFunSpe(mot) || Expr::isLerp(mot) || Expr::isPolynome(mot)) &&
          ((chaine.size()==1 && chaine.back() == "-") || (chaine.size()>1 && chaine.back() == "-" &&
            (chaine.at(chaine.size()-2)=="(" || chaine.at(chaine.size()-2)==",") ))) {
            chaine.pop_back();
            chaine.push_back("-1");
            chaine.push_back("*");
        }
        chaine.push_back(mot);
        mot="";
      }
    }
    else if(s.at(i) == '_'){
      chaine.push_back(mot);
      mot="";
      mot.push_back(s.at(i));
      chaine.push_back(mot);
      mot="";
    }
  }

  if(isdigit(s.at(s.size()-1)) || s.at(s.size()-1)=='(' || s.at(s.size()-1)==')' || isalpha(s.at(s.size()-1))){
    if(isdigit(s.at(s.size()-1)) && chaine.size()>=1 && chaine.back() == "-"){//cas ou la valeur est négative
      chaine.pop_back();
      mot = "-"+mot;
    }
    if(isalpha(s.at(s.size()-1)) && chaine.size()>=1 && chaine.back() == "-"){//cas ou la variable est négative
      chaine.pop_back();
      chaine.push_back("-1");
      chaine.push_back("*");
    }
    mot.push_back(s.at(s.size()-1));
    chaine.push_back(mot);
  }

  // for (std::vector<std::string>::iterator it = chaine.begin() ; it != chaine.end(); ++it){
  //     std::cout << *it << " ";
  // }
  return chaine;
}

std::stack<ExprToken*> Expr::rpn(std::vector<std::string> chaine){
  std::stack<ExprToken*> pile;
  std::stack<ExprToken*> sortie;

  bool egalExist = false;

  for (std::vector<std::string>::iterator it = chaine.begin() ; it != chaine.end(); ++it){
    std::string str= *it;
    if(isdigit(str[0])){//std::cout << " operande " << *it;
      sortie.push(new EntToken(2,std::stof(*it)));
    }
    if(isalpha(str[0])){
      if(Expr::isFun(*it) || Expr::isFunSpe(*it) || Expr::isLerp(*it) || Expr::isPolynome(*it)){
        sortie.push(new OpToken(1,'$'));
        pile.push(new FunToken(5,*it));
      }
      else{
        sortie.push(new AlphaToken(4,*it));
      }
    }
    else if(Expr::isOp(str[0])){
      if(str[0] == '-' && isdigit(str[1])){ //Cas pour les valeur negative
        sortie.push(new EntToken(2,std::stof(*it)));
      }
      else{
        if(pile.empty()){ pile.push(new OpToken(1,str[0])); }
        else if(str[0] == '='){ egalExist = true; }
        else if(str[0] == '*' || str[0] == '/'){
          while(!pile.empty() && pile.top()->getType() == 5){
            sortie.push(pile.top());
            pile.pop();
          }
          pile.push(new OpToken(1,str[0]));
        }
        else{ // cas ou op est un plus ou un moins
          while((!pile.empty()) && (pile.top()->getOp() == '*' || pile.top()->getOp() == '/' || pile.top()->getType() == 5)){
            sortie.push(pile.top());
            pile.pop();
          }
          pile.push(new OpToken(1,str[0]));
        }
      }
    }
    else if(str[0] == '('){
      if(!sortie.empty() && sortie.top()->getType() == 4){ //Cas ou c'est une funSpe : l(0.5)
        pile.push(sortie.top());
        sortie.pop();
        sortie.push(new OpToken(1,'$'));
      }
      pile.push(new ParToken(3,str[0]));
    }
    else if(str[0] == ')'){
      while(!pile.empty() && pile.top()->getType() != 3){
        sortie.push(pile.top());
        pile.pop();
      }
      pile.pop();
      if(!pile.empty() && (pile.top()->getType() == 5 || pile.top()->getType()) ){
        sortie.push(pile.top());
        pile.pop();
      }
    }
    else if(str[0] == ','){
      while(!pile.empty() && pile.top()->getType() != 3){
        sortie.push(pile.top());
        pile.pop();
      }
    }
    else if(str[0] == '_'){
      sortie.push(new UnderScoreToken());
    }
  }

  while(!pile.empty()){
    sortie.push(pile.top());
    pile.pop();
  }
  if(egalExist){sortie.push(new OpToken(1,'='));}

  std::stack<ExprToken*> vraiSortie;
  while(!sortie.empty()){
    vraiSortie.push(sortie.top());
    sortie.pop();
  }
  return vraiSortie;
}
