#ifndef TERM_H
#define TERM_H

#include "../computorv.h"

using namespace std;

class term {
    private:
        float       constant;
        string      variable;
        int         exponent;
        bool        isConstant;
        bool        isVariable;
        bool        isExponent;
        bool        afterBracket;
        char        bracketOperator;
        int         order;
        char        operand;
        int         termSide;
        static int  priorityLevel;
        static int  maxPriority;
        void        fillTerm(string str);

    public:
        term(int termSide);
        term(string str, char operand, int termSide);
        term(void);
        term(term const & rhs);
        term & operator=(term const & rhs);
        bool    setConstant(float constant);
        void    addConstant(term leftConstant, term rightConstant);
        bool    setVariable(char variable);
        bool    setExponent(int exponent);
        void    addExponent(int leftExponent, int rightExponent);
        void    addVariable(term rightVariable, term leftVariable);
        bool    setOperand(char operand);
        void    setSide(int side);
        void    replaceTerm(term tempTerm);
        bool    isVar() const;
        bool    isConst() const;
        bool    isExp() const;
        void    toString();
        int     getExponent() const;
        int     getSide() const;
        float   getConstant() const;
        string  getVariable() const;
        char    getOperand() const;
        char    getOrder() const ;
        bool    sameAs(term compareTerm);
        bool    addTerm(term addTerm);
        void    removeVariable();
        void    swapTerm(term rightTerm);
        void    matchTerm(term rhs);
        float   getCorrectValue() const;
        void    replaceVariable(float value);
        static void    updatePriority(char bracketType);
        void    setAfterBracket();
        void    setOperatorBracket(char bracketOperator);
        bool    isAfterBracket();
        char    getBracketOperator();
};
#endif
