#ifndef VALIDATE_H
#define VALIDATE_H

#include "../computorv.h"

class	Validate {
    private:
        void            splitString(char *poly);
        void            correctSplit();
        void            splitMixedTerm(string str);
        vector<string>  tempStrings;
        vector<string>  correctStrings;
        bool            checkPolynomialAuthentacity();
        void            splitForAlphaAndDigit(string str);
        void            splitForEqualSign(string str);
        void            splitForOperand(string str);
        void            addexpression(polynomial *equation);
        static char     oneVar;
        bool            sameVariables(char *poly);

	public:
        Validate(void);
		bool	isPolynomialValid(char *poly, polynomial *equation);
        bool    isTermValid(char *term, polynomial *equation, int *termValid);  
};
#endif
