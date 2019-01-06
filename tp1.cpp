/* g++ -std=c++11 tp1.cpp -o tp1*/
#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <locale>
#include <string>
#include "Expr.hpp"

void testAutomatique(std::map<std::string,float>& memoire,std::map<std::string,FunSpeToken>& memoireSpe,std::map<std::string,FunPHToken>& memoireDyn){
  const char* test ("17 - 24 / 4 * 3 ");
  const char* test2 ("17-24/4*3");
  const char* test3 ("17 - 24/4    *3");
  const char* test4 ("(17-24) / 4 * 3");
  const char* deuxpi ("deuxpi = 2*3.1415926536;");
  const char* rayon ("rayon = 3*8;");
  const char* circonference ("circonference = deuxpi * rayon;");
  const char* flottant("(-1.7 + 1.7)*3");
  const char* funct("-(-cos(0) * lerp(2,5,0.1)) + pow(2,2)");
  const char* poly("polynome(3, cos(0), 2, 3, 4, -1)");
  const char* funSpe1("l = lerp(2,3);");
  const char* funSpe2("l(0.1)");
  const char* funSpe3("p = polynome(3,1,2,3,4);");
  const char* funSpe4("p(5)");
  const char* funSpe5("p = polynome(3);");
  const char* funSpe6("p(1,2,3,4,5)");
  const char* square1("square = pow(_1, 2);");
  const char* square2("square(3)");
  const char* pOfTwo("powoftwo = pow(2, _1);");
  const char* pOfTwo2("powoftwo(3)");

  std::cout << "Test automatique:" << std::endl;

  {Expr x(test);
  std::cout << "test 1 (avec espace):" << std::endl;
  std::cout << std::endl;
  std::cout << "resultat de [" << test << "] = " << x.eval(memoire,memoireSpe,memoireDyn) << std::endl;
  std::cout << "notation polonaise : ";
  x.print();
  std::cout << "\n-------------\n";}

  {Expr x(test2);
  std::cout << "test 2 (sans espace):" << std::endl;
  std::cout << std::endl;
  std::cout << "resultat de [" << test2 << "] = " << x.eval(memoire,memoireSpe,memoireDyn) << std::endl;
  std::cout << "notation polonaise : ";
  x.print();
  std::cout << "\n-------------\n";}

  {Expr x(test3);
  std::cout << "test 3 (avec et sans espace):" << std::endl;
  std::cout << std::endl;
  std::cout << "resultat de [" << test3 << "] = " << x.eval(memoire,memoireSpe,memoireDyn) << std::endl;
  std::cout << "notation polonaise : ";
  x.print();
  std::cout << "\n-------------\n";}

  {Expr x(test4);
  std::cout << "test 4 (avec paranthese):" << std::endl;
  std::cout << std::endl;
  std::cout << "resultat de [" << test4 << "] = " << x.eval(memoire,memoireSpe,memoireDyn) << std::endl;
  std::cout << "notation polonaise : ";
  x.print();
  std::cout << "\n-------------\n";}

  {Expr x(deuxpi);
  Expr x2(rayon);
  Expr x3 (circonference);
  std::cout << "test 5 (memoire):" << std::endl;
  std::cout << deuxpi << std::endl;
  x.eval(memoire,memoireSpe,memoireDyn);
  std::cout << rayon << std::endl;
  x2.eval(memoire,memoireSpe,memoireDyn);
  std::cout << circonference << std::endl;
  std::cout << "circonference" << std::endl;
  std::cout << "resultat = " << x3.eval(memoire,memoireSpe,memoireDyn) << std::endl;
  std::cout << "\n-------------\n\n";}

  {Expr x(flottant);
  std::cout << "test avec flottant :" << std::endl;
  std::cout << std::endl;
  std::cout << "resultat de [" << flottant << "] = " << x.eval(memoire,memoireSpe,memoireDyn) << std::endl;
  std::cout << "notation polonaise : ";
  x.print();
  std::cout << "\n-------------\n";}

  {Expr x(funct);
  std::cout << "test avec fonction :" << std::endl;
  std::cout << std::endl;
  std::cout << "resultat de [" << funct << "] = " << x.eval(memoire,memoireSpe,memoireDyn) << std::endl;
  std::cout << "notation polonaise : ";
  x.print();
  std::cout << "\n-------------\n";}

  {Expr x(poly);
  std::cout << "test avec polynome :" << std::endl;
  std::cout << std::endl;
  std::cout << "resultat de [" << poly << "] = " << x.eval(memoire,memoireSpe,memoireDyn) << std::endl;
  std::cout << "notation polonaise : ";
  x.print();
  std::cout << "\n-------------\n";}

  {Expr x1(funSpe1); Expr x2(funSpe2); Expr x3(funSpe3); Expr x4(funSpe4); Expr x5(funSpe5); Expr x6(funSpe6);
    std::cout << "test fonctions avec n-p parametres :" << std::endl;
    std::cout << funSpe1 << std::endl;
    x1.eval(memoire,memoireSpe,memoireDyn);
    std::cout << funSpe2 << std::endl;
    std::cout << "resultat de [" << funSpe2 << "] = " << x2.eval(memoire,memoireSpe,memoireDyn) << std::endl;
    std::cout << funSpe3 << std::endl;
    x3.eval(memoire,memoireSpe,memoireDyn);
    std::cout << funSpe4 << std::endl;
    std::cout << "resultat de [" << funSpe4 << "] = " << x4.eval(memoire,memoireSpe,memoireDyn) << std::endl;
    std::cout << funSpe5 << std::endl;
    x5.eval(memoire,memoireSpe,memoireDyn);
    std::cout << funSpe6 << std::endl;
    std::cout << "resultat de [" << funSpe6 << "] = " << x6.eval(memoire,memoireSpe,memoireDyn) << std::endl;
    std::cout << "\n-------------\n";
  }

  {Expr x1(square1); Expr x2(square2); Expr x3(pOfTwo); Expr x4(pOfTwo2);
    std::cout << "test fonctions partiel :" << std::endl;
    std::cout << square1 << std::endl;
    x1.eval(memoire,memoireSpe,memoireDyn);
    std::cout << square2 << std::endl;
    std::cout << "resultat de [" << square2 << "] = " << x2.eval(memoire,memoireSpe,memoireDyn) << std::endl;
    std::cout << pOfTwo << std::endl;
    x3.eval(memoire,memoireSpe,memoireDyn);
    std::cout << pOfTwo2 << std::endl;
    std::cout << "resultat de [" << pOfTwo2 << "] = " << x4.eval(memoire,memoireSpe,memoireDyn) << std::endl;
  }
}

int main(){
  std::map<std::string,float> memoire;
  std::map<std::string,FunSpeToken> memoireSpe;
  std::map<std::string,FunPHToken> memoireDyn;

  testAutomatique(memoire,memoireSpe,memoireDyn);

  std::string str;
  std::cout << "Test manuel, entrez ce que vous desirez tester :" << std::endl;
  while(true){
    getline (std::cin,str);

    const char* test = str.c_str();

    Expr x(test);
    if(str.back() != ';'){
      std::cout << "Expression :" << test << std::endl;
      std::cout << "notation polonaise : ";
      x.print();
      std::cout << std::endl;
      std::cout << "resultat de [" << test << "] = " << x.eval(memoire,memoireSpe,memoireDyn) << std::endl;
    }
    else{
      x.eval(memoire,memoireSpe,memoireDyn);
    }

    std::cout << "\n-------------\n\n";

  }

  return 0;
}
