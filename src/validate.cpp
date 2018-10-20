#include "../computorv.h"

char	Validate::oneVar = ' ';

bool	isOperandCharector(string ch) {
	return (ch[0] == '+' || ch[0] == '-' || ch[0] == '*' || ch[0] == '/');
}

bool	isOperand(string ch) {
	return (!ch.compare("+") || !ch.compare("-") || !ch.compare("*") || !ch.compare("/"));
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

bool	Validate::checkPolynomialAuthentacity() {
	int index = -1;

	if (!correctStrings[0].compare("*") || !correctStrings[0].compare("/"))
		return (false);
	if (correctStrings[0][0] == '*' || correctStrings[0][0] == '/')
		return (false);
	if (correctStrings[0][0] == '^')
		return (false);
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
		if (term[i] == '+' || term[i] == '-' || term[i] == '*' || term[i] == '/') {
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

bool	foundNumber(string str) {
	int index = -1;
	
	if (str.length() < 1) {
		return (false);
	}
	while (++index < (int)str.length()) {
		if (isdigit(str[index])) {
			return (true);
		}
	}
	return (false);
}

bool	foundAlpha(string str) {
	int index = -1;
	
	if (str.length() < 1) {
		return (false);
	}
	while (++index < (int)str.length()) {
		if (isalpha(str[index])) {
			return (true);
		}
	}
	return (false);
}

bool	foundEqualSign(string str) {
	if (str.length() < 1) {
		return (false);
	}
	if ((str.find("=") > 0) && (str.find("=") < str.length())) {
		return (true);
	}
	return (false);
}

int	returnIndexOfOperand(string str) {
	int		index = -1;
	string	temp;

	while (++index < (int)str.length()) {
		if (str[index] == '+' || str[index] == '-' || str[index] == '*' || str[index] == '/') {
			return (index);
		}
	}
	return (0);
}

int	returnIndexOfNumber(string str) {
	int		index = -1;
	string	temp;

	while (++index < (int)str.length()) {
		if (isdigit(str[index])) {
			return (index);
		}
	}
	return (0);
}

int	returnIndexOfAlpha(string str) {
	int		index = -1;
	string	temp;

	while (++index < (int)str.length()) {
		if (isalpha(str[index])) {
			return (index);
		}
	}
	return (0);
}

int		Validate::lastIndexOfAlpha(string str) {
	int	bracketsCount = 0;
	int	i = -1;
	int	len = (int)str.length();

	while (++i < len) {
		if (!isalpha(str[i])) {
			if ((str[i] == '(' || str[i] == ')') && bracketsCount < 2) {
				bracketsCount++;
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
		if (!isOperandCharector(str.substr(this->lastIndexOfAlpha(str)))) {
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

	while (++i < len) {
		if (!isdigit(str[i])) {
			if (str[i] == '.' && periodCounter < 1) {
				periodCounter++;
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

void	Validate::splitMixedTerm(string str) {
	// cout << "Splitting in mixed term >>>" << str << endl;
	if (isalpha(str[0])) {
		return (splitForAlpha(str));
	}
	else if (isdigit(str[0])) {
		return (splitForDigit(str));
	}
	else if (str[0] == '+' || str[0] == '-' || str[0] == '*'
		|| str[0] == '/' || str[0] == '(' || str[0] == ')') {
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

void	Validate::addexpression(polynomial *equation) {
	int	index = 0;
	int	termSide = 0;

	if (correctStrings[0][0] == '+' || correctStrings[0][0] == '-') {
		term *termClass = new term(correctStrings[1], correctStrings[0][0], termSide);
		equation->addTerm(termClass);
		index = 2;
	}
	else {
		term *termClass = new term(correctStrings[0], '+', termSide);
		equation->addTerm(termClass);
		index = 1;
	}
	while (index < ((int)correctStrings.size() - 1)) {
		// cout << "index at (" << correctStrings[index] << ")" << endl;
		if (isOperand(correctStrings[index])) {
			if (!correctStrings[index + 1].compare("(")) {
				term::updatePriority(correctStrings[index + 1][0]);
				if (isOperand(correctStrings[index + 2])) {
					term *termClass = new term(correctStrings[index + 3], correctStrings[index + 2][0], termSide);
					termClass->setAfterBracket();
					termClass->setOperatorBracket(correctStrings[index][0]);
					equation->addTerm(termClass);
					index += 4;
				}
				else {
					term *termClass = new term(correctStrings[index + 2], '+', termSide);
					termClass->setAfterBracket();
					termClass->setOperatorBracket(correctStrings[index][0]);
					equation->addTerm(termClass);
					index += 3;
				}
			}
			else {
				term *termClass = new term(correctStrings[index + 1], correctStrings[index][0], termSide);
				equation->addTerm(termClass);
				index += 2;
			}
		}
		else if (correctStrings[index][0] == ')') {
			term::updatePriority(correctStrings[index][0]);
			if (isOperand(correctStrings[index + 1])) {
				term *termClass = new term(correctStrings[index + 2], correctStrings[index + 1][0], termSide);
				equation->addTerm(termClass);
				index += 3;
			}
			else {
				term *termClass = new term(correctStrings[index + 1], '+', termSide);
				termClass->setAfterBracket();
				termClass->setOperatorBracket(correctStrings[index][0]);
				equation->addTerm(termClass);
				index += 2;
			}
		}
		else if (correctStrings[index][0] == '(') {
			term::updatePriority(correctStrings[index][0]);
			if (isOperand(correctStrings[index + 1])) {
				term *termClass = new term(correctStrings[index + 2], correctStrings[index + 1][0], termSide);
				termClass->setAfterBracket();
				termClass->setOperatorBracket('*');
				equation->addTerm(termClass);
				index += 3;
			}
			else {
				term *termClass = new term(correctStrings[index + 1], '+', termSide);
				termClass->setAfterBracket();
				termClass->setOperatorBracket('*');
				equation->addTerm(termClass);
				index += 2;
			}
		}
	}
}

//negative exponents
//variable that have multiple characters
//

bool	Validate::checkVariables(polynomial *equation, Instruction instructions) {
	int		index = -1;
	int		len = (int)equation->counter;
	term	*tempTerm;
	bool	isImaginary;
	int		unknownCount = 0;
	string	unknownVar;

	while (++index < len) {
		isImaginary = false;
		if (equation->getTerm(index)->isVar()) {
			if (instructions.findInstruction(equation->getTerm(index)->getVariable()) == NULL) {
				if (equation->getTerm(index)->getVariable().compare("i")) {
					if (unknownCount >= 1) {
						return (false);
					}
					unknownCount++;
					unknownVar = equation->getTerm(index)->getVariable();
				}
				else {
					isImaginary = true;
				}
			}
			if (!isImaginary && unknownVar.compare(equation->getTerm(index)->getVariable())) {
				tempTerm = equation->getTerm(index);
				tempTerm->replaceVariable(instructions.findInstruction(tempTerm->getVariable())->getfloatValue());
			}
		}
	}
	return (true);
}

bool	Validate::isPolynomialValid(string poly, polynomial *equation, Instruction instructions) {
	// cout << "String received :: " << poly << endl; 
	if (!this->bracketsOk(poly)) {
		return (false);
	}
	splitString(poly);
	correctSplit();
	// for (size_t i = 0; i < correctStrings.size(); i++) {
	// 	cout << "String :: " << correctStrings.at(i) << endl;
	// }
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

	if ((str[0] == '-') || (str[0] == '+')) {
		index = 0;
	}
	while (++index < len) {
		if (!isdigit(str[index]) && str[index] != '.' && periodCount < 1) {
			return (false);
		}
		if (str[index] == '.') {
			periodCount++;
		}
	}
	return (true);
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
			if (compareClose.at(compareClose.size() - 1) != str[i]) {
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
