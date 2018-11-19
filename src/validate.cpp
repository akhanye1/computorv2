#include "../computorv.h"

char	Validate::oneVar = ' ';

bool	isOperandCharector(string ch) {
	return (ch[0] == '+' || ch[0] == '-' || ch[0] == '*' || ch[0] == '/' || ch[0] == '%');
}

bool	isOperand(string ch) {
	return (!ch.compare("+") || !ch.compare("-") || !ch.compare("*") || !ch.compare("/") || !ch.compare("%"));
}

bool	Validate::isNextOperand(string ch) {
	return (!ch.compare("+") || !ch.compare("-") || !ch.compare("*") || !ch.compare("/") || !ch.compare("%") ||
		!ch.compare("(") || !ch.compare(")"));
}

bool	Validate::foundOperator(string str) {
	int index = -1;

	if (str.length() < 1) {
		return (false);
	}
	while (++index < (int)str.length()) {
		if (str[index] == '+' || str[index] == '-' || str[index] == '*' || str[index] == '/' ||
            str[index] == '%') {
			return (true);
		}
	}
	return (false);
}

void	Validate::splitString(string poly) {
	string	temp;
	size_t	pos;

	while ((pos = poly.find("\t")) != string::npos) {
		poly[pos] = ' ';
	}
	while ((pos = poly.find(" ")) != string::npos) {
		temp = poly.substr(0, pos);
		poly = poly.substr(pos + 1);
		if (temp.length() > 0) {
			tempStrings.push_back(temp);
		}
	}
	if (temp.length() > 0) {
		tempStrings.push_back(poly);
	}
	else if (poly.length() > 0) {
		tempStrings.push_back(poly);
	}
}

bool	Validate::isExponentCorrect() {
	return (correctStrings[0][0] != '^' && correctStrings[correctStrings.size() - 1][0] != '^' &&
		correctStrings[correctStrings.size() - 1][correctStrings[correctStrings.size() - 1].length() - 1] != '^');
}

bool	Validate::checkPolynomialAuthentacity() {
	int index = -1;

	if (!correctStrings[0].compare("*") || !correctStrings[0].compare("/") || !correctStrings[0].compare("%"))
		return (false);
	if (correctStrings[0][0] == '*' || correctStrings[0][0] == '/' || correctStrings[0][0] == '%')
		return (false);
	if (!isExponentCorrect())
		return (false);
	if (isOperand(correctStrings[correctStrings.size() - 1]) ||
		isOperandCharector(correctStrings[correctStrings.size() - 1])) {
		return (false);
	}
	while (++index < ((int)correctStrings.size() - 1)) {
		if (correctStrings[index][0] == '^' || correctStrings[index][correctStrings[index].length() - 1] == '^')
			return (false);
		if (isOperand(correctStrings[index]) && isOperand(correctStrings[index + 1]))
			return (false);
	}
	return (true);
}

bool	mixedTerm(string term) {
	int i = -1;
	bool isConst, isVar, isOp, isequal, isBracket;

	if (term.length() < 1) {
		return (false);
	}
	isConst = isVar = isOp = isequal = isBracket = false;
	while (++i < (int)term.length()) {
		if (isalpha(term[i])) {
			isVar = true;
		}
		if (isdigit(term[i])) {
			isConst = true;
		}
		if (term[i] == '+' || term[i] == '-' || term[i] == '*' || term[i] == '/' || term[i] == '%') {
			isOp = true;
		}
		if (term[i] == '=') {
			isequal = true;
		}
		if (term[i] == '(' || term[i] == ')') {
			isBracket = true;
		}
	}
	if (isConst && isVar) {
		return (true);
	}
	return ((isConst || isVar) && (isOp || isequal || isBracket));
}

int		Validate::lastIndexOfAlpha(string str) {
	int	bracketsCount = 0;
	int	i = -1;
	int	len = (int)str.length();
	int	powerCount = 0;

	while (++i < len) {
		if (!isalpha(str[i])) {
			if (str[i] == '(') {
				bracketsCount++;
			}
			else if (str[i] == ')' && bracketsCount > 0) {
				bracketsCount--;
			}
			else if (str[i] == '^' && powerCount < 1) {
				if (isdigit(str[i + 1])) {
					cout << "next item :: " << str[i + 1] << " | text :: " << str.substr(i + 1) << endl;
					i += 1 + (this->lastIndexOfFloat(str.substr(i + 1)) + 1);
					cout << "i @ :: " << str[i] << endl;
				}
			}
			else if (bracketsCount > 0 && isdigit(str[i])) {

			}
			else {
				return (i);
			}
		}
	}
	return (-1);
}

void	Validate::splitForAlpha(string str) {
	if (this->lastIndexOfAlpha(str) > -1) {
		correctStrings.push_back(str.substr(0, this->lastIndexOfAlpha(str)));
		if (!isOperandCharector(str.substr(this->lastIndexOfAlpha(str))) &&
			str[lastIndexOfAlpha(str)] != ')') {
			correctStrings.push_back("*");
		}
		return (splitMixedTerm(str.substr(this->lastIndexOfAlpha(str))));
	}
	if (str.length() > 0) {
		correctStrings.push_back(str);
	}
}

int		Validate::lastIndexOfFloat(string str) {
	int	i = -1;
	int	periodCounter = 0;
	int len = (int)str.length();
	int	powerCounter = 0;

	while (++i < len) {
		if (!isdigit(str[i])) {
			if (str[i] == '.' && periodCounter < 1) {
				periodCounter++;
			}
			else if (str[i] == '^' && powerCounter < 1) {
				powerCounter++;
			}
			else {
				return (i);
			}
		}
	}
	return (-1);
}

void	Validate::splitForDigit(string str) {
	if (this->lastIndexOfFloat(str) > -1) {
		correctStrings.push_back(str.substr(0, this->lastIndexOfFloat(str)));
		if (!isOperandCharector(str.substr(this->lastIndexOfFloat(str)))) {
			if (str[this->lastIndexOfFloat(str)] != ')') {
				correctStrings.push_back("*");
			}
		}
		return (splitMixedTerm(str.substr(this->lastIndexOfFloat(str))));
	}
	if (str.length() > 0) {
		correctStrings.push_back(str);
	}
}

void	Validate::splitForOneChar(string str) {
	if (str[1]) {
		correctStrings.push_back(str.substr(0, 1));
		return (splitMixedTerm(str.substr(1)));
	}
	if (str.length() > 0) {
		correctStrings.push_back(str);
	}
}

void	Validate::splitForClosingBracket(string str) {
	if (this->lastIndexOfFloat(&str[1]) > -1) {
		correctStrings.push_back(str.substr(0, this->lastIndexOfFloat(&str[1]) + 1));
		if (!isOperandCharector(str.substr(this->lastIndexOfFloat(&str[1]) + 1))) {
			if (str[this->lastIndexOfFloat(&str[1]) + 1] != ')') {
				correctStrings.push_back("*");
			}
		}
		return (splitMixedTerm(str.substr(this->lastIndexOfFloat(&str[1]) + 1)));
	}
	if (str.length() > 0) {
		correctStrings.push_back(str);
	}
}

void	Validate::splitMixedTerm(string str) {
	cout << "Splitting in mixed term >>>" << str << endl;
	if (isalpha(str[0])) {
		return (splitForAlpha(str));
	}
	else if (isdigit(str[0])) {
		return (splitForDigit(str));
	}
	else if (str[0] == ')') {
		if (str[1] == '^') {
			return (splitForClosingBracket(str));
		}
		return (splitForOneChar(str));	
	}
	else if (str[0] == '+' || str[0] == '-' || str[0] == '*'
		|| str[0] == '/' || str[0] == '(' || str[0] == ')' || str[0] == '%') {
		return (splitForOneChar(str));
	}
	if (str.length() > 0) {
		correctStrings.push_back(str);
	}
}

bool	Validate::foundMixedTerm(string str) {
	int 	numCount, alphaCount;
	size_t	maxLength;

	numCount = alphaCount = 0;
	maxLength = str.length();
	if (str.find("^") != string::npos) {
		return (true);
	}
	for (size_t i = 0; i < maxLength; i++) {
		if (isalpha(str[i])) {
			alphaCount++;
		}
		else if (isdigit(str[i])) {
			numCount++;
		}
	}
	return (numCount > 0 && alphaCount > 0);
}

void	Validate::correctSplit() {
	int	index = -1;

	while (++index < (int)tempStrings.size()) {
		// cout << "Temp String >> " << tempStrings.at(index) << endl;
		if (mixedTerm(tempStrings[index])) {
			// cout << "Is mixed string" << endl;
			splitMixedTerm(tempStrings[index]);
		}
		else if (tempStrings[index].length() > 0) {
			// cout << "Not Mixed string" << endl;
			correctStrings.push_back(tempStrings[index]);
		}
	}
}

int		Validate::findNextOperand(int index) {
	int cnt = 0;

	if (isNextOperand(correctStrings[index])) {
		cnt += 1;
		index++;
	}
	while (index < (int)correctStrings.size() - 1) {
		if (this->isNextOperand(correctStrings[index++])) {
			return (cnt);
		}
		cnt++;
	}
	return (cnt);
}

bool	Validate::isValidExpression(int index) {
	// cout <<  "Is numberic :: " << this->isNumeric(correctStrings[index]) << endl;
	// cout <<  "Is valid variable :: " << this->isValidVariable(correctStrings[index], false) << endl;
	// cout <<  "Is valid function :: " << this->isValidFunction(correctStrings[index]) << endl;
	return (this->isNumeric(correctStrings[index]) ||
			this->isValidVariable(correctStrings[index], false) ||
			this->isValidFunction(correctStrings[index]));
}

int		Validate::addTermForOpenBracket(polynomial *equation, int index, int termSide, 
		string bracketOperand) {
	term::updatePriority(correctStrings[index][0]);
	// Check for operand and if valid number or variable
	if (isOperand(correctStrings[index + 1]) && this->isValidExpression(index + 2)) {
		term *termClass = new term(correctStrings[index + 2], correctStrings[index + 1][0], termSide);
		termClass->setAfterBracket();
		termClass->setOperatorBracket(bracketOperand[0]);
		equation->addTerm(termClass);
		return (3);
	}
	else if (this->isValidExpression(index + 1)) {
		term *termClass = new term(correctStrings[index + 1], '+', termSide);
		termClass->setAfterBracket();
		termClass->setOperatorBracket(bracketOperand[0]);
		equation->addTerm(termClass);
		return (2);
	}
	else {
		cout << "Term was not add to polynomial (1)" << endl;
	}
	return (this->findNextOperand(index));
}

int		Validate::addTermForOperand(polynomial *equation, int index, int termSide) {
	int cnt = 0;
	if (!correctStrings[index + 1].compare("(")) {
		cnt++;
		cnt += addTermForOpenBracket(equation, index + 1, termSide, correctStrings[index]);
		return (cnt);
	}
	else if (isValidExpression(index + 1) && isOperand(correctStrings[index])) {
		term *termClass = new term(correctStrings[index + 1], correctStrings[index][0], termSide);		equation->addTerm(termClass);
		return (2);
	}
	else {
		cout << "Term was not add to polynomial (2)" << endl;
	}
	return (findNextOperand(index));
}

int		Validate::addTermForClosingBracket(polynomial *equation, int index, int termSide) {
	term::updatePriority(correctStrings[index][0]);
	if (isOperand(correctStrings[index + 1]) && isValidExpression(index + 2)) {
		term *termClass = new term(correctStrings[index + 2], correctStrings[index + 1][0], termSide);
		equation->addTerm(termClass);
		return (3);
	}
	else if (isValidExpression(index + 1)) {
		term *termClass = new term(correctStrings[index + 1], '+', termSide);
		termClass->setAfterBracket();
		termClass->setOperatorBracket(correctStrings[index][0]);
		equation->addTerm(termClass);
		return (2);
	}
	else {
		cout << "Term was not add to the polynomial (3)" << endl;
	}
	return (findNextOperand(index));
}

void	Validate::addexpression(polynomial *equation) {
	int	index = 0;
	int	termSide = 0;

	if (correctStrings[0][0] == '+' || correctStrings[0][0] == '-') {
		term *termClass = new term(correctStrings[1], correctStrings[0][0], termSide);
		equation->addTerm(termClass);
		index = findNextOperand(index);
	}
	else if (correctStrings[0][0] != '(') {
		term *termClass = new term(correctStrings[0], '+', termSide);
		equation->addTerm(termClass);
		index = findNextOperand(index);
	}
	while (index < ((int)correctStrings.size() - 1)) {
		// cout << "index at (" << correctStrings[index] << ")" << endl;
		if (isOperand(correctStrings[index])) {
			index += addTermForOperand(equation, index, termSide);
			// cout << "After adding for operand " << endl;
		}
		else if (correctStrings[index][0] == ')') {
			index += addTermForClosingBracket(equation, index, termSide);
			// cout << "After adding for close Bracket " << endl;
		}
		else if (correctStrings[index][0] == '(') {
			index += addTermForOpenBracket(equation, index, termSide, "*");
			// cout << "After adding for open Barcket " << endl;
		}
		// equation->showAll();
	}
}

//negative exponents
//variable that have multiple characters
//

bool	Validate::foundUnknown(polynomial *equation, int index) {
	if (equation->getTerm(index)->getVariable().compare("i")) {
		if (this->unknownCount >= 1) {
			if (equation->getTerm(index)->getVariable().compare(this->unknownVar)) {
				return (false);
			}
		}
		this->unknownCount++;
		this->unknownVar = equation->getTerm(index)->getVariable();
	}
	else {
		isImaginary = true;
	}
	return (true);
}

bool	Validate::replaceFunctionVar(polynomial *equation, Instruction instructions,
		int index, term *tempTerm, Instruction *savedInstruction) {
	Instruction	*savedInstruction1;
	// cout << "Instruction type :: FUNCTION" << endl;
	// cout << "Variable name :: " << equation->getTerm(index)->getVariable() << endl;
	// cout << "Parameter :: " << instructions.getVariableName(equation->getTerm(index)->getVariable()) << endl;
	if (this->isNumeric(instructions.getVariableName(equation->getTerm(index)->getVariable()))) {
		tempTerm->replaceVariable(savedInstruction->getFunction()->getFunctionValue(atof(instructions.getVariableName(equation->getTerm(index)->getVariable()).c_str())));
	}
	else {
		if ((savedInstruction1 = instructions.findInstruction(instructions.getVariableName(equation->getTerm(index)->getVariable()))) == NULL) {
			return (false);
		}
		if (savedInstruction1->getType() != VARIABLE) {
			return (false);
		}
		// tempTerm->replaceVariable(savedInstruction->getfloatValue());
		tempTerm->replaceVariable(savedInstruction->getFunction()->getFunctionValue(savedInstruction1->getfloatValue()));
	}
	return (true);
}

bool	Validate::varIsOkay(polynomial *equation, Instruction instructions, int index) {
	Instruction	*savedInstruction;
	term		*tempTerm;

	if ((savedInstruction = instructions.findInstruction(equation->getTerm(index)->getVariable())) == NULL) {
		if (!this->foundUnknown(equation, index)) {
			return (false);
		}
	}
	if (!this->isImaginary && this->unknownVar.compare(equation->getTerm(index)->getVariable()) && savedInstruction != NULL) {
		tempTerm = equation->getTerm(index);
		if (savedInstruction->getType() == VARIABLE) {
			tempTerm->replaceVariable(instructions.findInstruction(tempTerm->getVariable())->getfloatValue());
		}
		else if (savedInstruction->getType() == FUNCTION) {
			return (this->replaceFunctionVar(equation, instructions, index, tempTerm, savedInstruction));
		}
	}
	return (true);
}

bool	Validate::checkVariables(polynomial *equation, Instruction instructions) {
	int			index = -1;
	int			len = equation->getMaxTerms();

	this->unknownVar = "";
	this->unknownCount = 0;
	this->isImaginary = false;
	while (++index < len) {
		isImaginary = false;
		if (equation->getTerm(index)->isVar()) {
			if (!this->varIsOkay(equation, instructions, index)) {
				return (false);
			}
		}
	}
	// equation->showAll();
	return (true);
}

// 5 ( 10 - x + ( x * 5 ) + 5 ) + 5 ( x )

bool	Validate::isPolynomialValid(string poly, polynomial *equation, Instruction instructions) {
	// cout << "String received :: " << poly << endl;
	term::resetPriority();
	if (!this->bracketsOk(poly)) {
		return (false);
	}
	splitString(poly);
	correctSplit();
	for (size_t i = 0; i < correctStrings.size(); i++) {
		cout << "String :: " << correctStrings.at(i) << endl;
	}
	if (!this->checkPolynomialAuthentacity()) {
		cout << "Authentication failed" << endl;
		return (false);
	}
	addexpression(equation);
	equation->showAll();
	return (checkVariables(equation, instructions));
}

bool	Validate::isValidVariable(string str, bool strict) {
	int index = -1;
	int	len = (int)str.length();

	if (strict) {
		while (++index < len) {
			if (!isalpha(str[index])) {
				return (false);
			}
		}
	}
	else {
		while (++index < len && isalpha(str[index]));
		if (index < len) {
			if (str[index] != '^') {
				return (false);
			}
		}
	}
	return (true);
}

bool	Validate::isValidFunction(string str) {
	size_t	index;
	size_t	lastIndex;
	string	variableTemp;
	int		i = -1;

	if (!isalpha(str[0])) {
		return (false);
	}
	index = str.find("(");
	if (index == string::npos) {
		return (false);
	}
	while (++i < (int)index) {
		if (!isalpha(str[i])) {
			return (false);
		}
	}
	lastIndex = str.find(")");
	if (lastIndex == string::npos) {
		return (false);
	}
	if (lastIndex - index == 1) {
		return (false);
	}
	variableTemp = str.substr(index + 1, (lastIndex - index) - 1);
	return (isValidVariable(variableTemp, true));
}

bool	Validate::isNumeric(string str) {
	int		index = -1;
	int		len = (int)str.length();
	int		periodCount = 0;
	int		exponentCount = 0;
	bool	gotInWhileLoop = false;

	if ((str[0] == '-') || (str[0] == '+')) {
		index = 0;
	}
	while (++index < len) {
		gotInWhileLoop = true;
		if (!isdigit(str[index]) && str[index] != '.' && periodCount < 1 &&
			str[index] != '^' && exponentCount < 1) {
			return (false);
		}
		if (str[index] == '.') {
			periodCount++;
		}
		if (str[index] == '^') {
			exponentCount++;
		}
	}
	return (gotInWhileLoop);
}

Validate::Validate(void) {
}

bool	Validate::bracketsOk(string str) {
	vector<char> compareClose;
	int i;
	int len;

	i = -1;
	len = (int)str.length();
	while (++i < len) {
		if (str[i] == '[') {
			compareClose.push_back(']');
		}
		else if (str[i] == '(') {
			compareClose.push_back(')');
		}
		else if (str[i] == ']' || str[i] == ')') {
			if (compareClose.size() > 0 && compareClose.at(compareClose.size() - 1) != str[i]) {
				return (false);
			}
			compareClose.erase(compareClose.end() - 1);
		}
	}
	return (compareClose.size() == 0);
}

string  Validate::trimString(string str) {
    string  temp = str;
    int     startPos = -1;
    int     endPos = str.length();

    while (str[++startPos] && str[startPos] == ' ');
    while (--endPos > 0 && str[endPos] == ' ');
    temp = temp.substr(startPos, (endPos - startPos) + 1);
    return (temp);
}
