#include "ExprToken.hpp"
#include "BadExpressionException.hpp"


const float ExprToken::operFun (std::string fct, std::vector<float> x){
	if (fct == "sin")
	{
		if(x.size() == 1){return sin(x[0]);}
		else{throw BadExpressionException("Mauvais arguments dans la fonction sinus \n Usage: sin(a)");}
	}
	else if (fct == "cos")
	{
		if(x.size() == 1){return cos(x[0]);}
		else{throw BadExpressionException("Mauvais arguments dans la fonction cosinus \n Usage: cos(a)");}
	}
	else if (fct == "tan")
	{
		if(x.size() == 1){return tan(x[0]);}
		else {throw BadExpressionException("Mauvais arguments dans la fonction tangente \n Usage: tan(a)");}
	}
	else if (fct == "sqrt")
	{
		if(x.size() == 1){return sqrt(x[0]);}
		else{throw BadExpressionException("Mauvais arguments dans la fonction square root \n Usage: sqrt(a)");}
	}
	else if (fct == "log")
	{
		if(x.size() == 1){return log(x[0]);}
		else{throw BadExpressionException("Mauvais arguments dans la fonction logarithme \n Usage: log(a)");}
	}
	else if (fct == "exp")
	{
		if(x.size()==1){return exp(x[0]);}
		else{throw BadExpressionException("Mauvais arguments dans la fonction exponnentiel \n Usage: exp(a)");}
	}
	else if(fct == "pow"){
		if(x.size()==2){return pow(x[0],x[1]);}
		else{throw BadExpressionException("Mauvais arguments dans la fonction puissance \n Usage: pow(a,b)");}
	}
	else if(fct == "hypot"){
		if(x.size()==2){return hypot(x[0],x[1]);}
		else{throw BadExpressionException("Mauvais arguments dans la fonction hypotenuse \n Usage: hypot(a,b)");}
	}
	else if(fct == "lerp"){
		if(x[2] < 0 || x[2] > 1){
			throw BadExpressionException("Mauvais arguments dans la fonction interpolation lineaire \n Usage: lerp(b,e,t) 0<=t<=1");
		}
		return ((1 - x[2]) * x[0] + x[2] * x[1]);
	}
	else if(fct == "polynome"){
		if (!x.empty() && (x[0] == x.size()-3)) {
	    float res = 0;
	    float t = x[x.size()-1];
	    for (int i = 1; i < x.size() - 1; i++) {
	        res += x[i] * pow(t, i-1);
	    }
	    return res;
	  }
		else{
			throw BadExpressionException("Mauvais arguments dans la fonction polynome \n Usage: polynome(degres,liste_coeff,x)");
		}
	}
}
