#include "../computorv.h"

char	Validate::oneVar = ' ';

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
		// if (!isOperand(correctStrings[index]) && !isOperand(correctStrings[index + 1])) {
		// 	if (correctStrings[index].compare("=") && correctStrings[index + 1].compare("=")) {
		// 		cout << "failed here (" << correctStrings[index] << ") (" << correctStrings[index + 1] << ")" << endl;
		// 		return (false);
		// 	}
		// }
	}
	return (true);
}

bool	mixedTerm(string term) {
	int i = -1;
	bool isterm, isOp, isequal;

	if (term.length() < 1) {
		return (false);
	}
	isterm = isOp = isequal = false;
	while (++i < (int)term.length()) {
		if (isalpha(term[i]) || isdigit(term[i]) || term[i] == '^') {
			isterm = true;
		}
		if (term[i] == '+' || term[i] == '-' || term[i] == '*' || term[i] == '/') {
			isOp = true;
		}
		if (term[i] == '=') {
			isequal = true;
		}
	}
	return (isterm && (isOp || isequal));
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

void	Validate::splitForAlpha(string str) {
	if (foundEqualSign(str) && foundNumber(str)) {
		if (returnIndexOfOperand(str) < foundNumber(str)) {
			correctStrings.push_back(str.substr(0, returnIndexOfOperand(str)));
			return splitMixedTerm(str.substr(returnIndexOfOperand(str)));
		}
		else {
			correctStrings.push_back(str.substr(0, returnIndexOfNumber(str)));
			return (splitMixedTerm(str.substr(returnIndexOfNumber(str))));
		}
	}
	else if (foundOperator(str)) {
		correctStrings.push_back(str.substr(0, returnIndexOfOperand(str)));
		return splitMixedTerm(str.substr(returnIndexOfOperand(str)));
	}
	else if (foundNumber(str)) {
		correctStrings.push_back(str.substr(0, returnIndexOfNumber(str)));
		return (splitMixedTerm(str.substr(returnIndexOfNumber(str))));
	}
	if (str.length() > 0) {
		correctStrings.push_back(str);
	}
}

void	Validate::splitForDigit(string str) {
	if (foundEqualSign(str) && foundAlpha(str)) {
		if (returnIndexOfOperand(str) < foundAlpha(str)) {
			correctStrings.push_back(str.substr(0, returnIndexOfOperand(str)));
			return splitMixedTerm(str.substr(returnIndexOfOperand(str)));
		}
		else {
			correctStrings.push_back(str.substr(0, returnIndexOfAlpha(str)));
			return (splitMixedTerm(str.substr(returnIndexOfAlpha(str))));
		}
	}
	else if (foundOperator(str)) {
		correctStrings.push_back(str.substr(0, returnIndexOfOperand(str)));
		return splitMixedTerm(str.substr(returnIndexOfOperand(str)));
	}
	else if (foundAlpha(str)) {
		correctStrings.push_back(str.substr(0, returnIndexOfAlpha(str)));
		return (splitMixedTerm(str.substr(returnIndexOfAlpha(str))));
	}
	if (str.length() > 0) {
		correctStrings.push_back(str);
	}
}

// void	Validate::splitForAlphaAndDigit(string str) {
// 	if (foundOperator(str) && foundEqualSign(str)) {
// 		if (returnIndexOfOperand(str) < (int)str.find("=")) {
// 			correctStrings.push_back(str.substr(0, returnIndexOfOperand(str)));
// 			return splitMixedTerm(str.substr(returnIndexOfOperand(str)));
// 		}
// 		else {
// 			correctStrings.push_back(str.substr(0, str.find("=")));
// 			return splitMixedTerm(str.substr(str.find("=")));	
// 		}
// 	}
// 	else if (foundOperator(str)) {
// 		correctStrings.push_back(str.substr(0, returnIndexOfOperand(str)));
// 		return splitMixedTerm(str.substr(returnIndexOfOperand(str)));
// 	}
// 	else if (foundEqualSign(str)) {
// 		correctStrings.push_back(str.substr(0, str.find("=")));
// 		return splitMixedTerm(str.substr(str.find("=")));
// 	}
// 	if (str.length() > 0) {
// 		correctStrings.push_back(str);
// 	}
// }

// void	Validate::splitForEqualSign(string str) {
// 	if (foundNumber(str) && foundOperator(str)) {
// 		if (returnIndexOfNumber(str) < returnIndexOfOperand(str)) {
// 			correctStrings.push_back(str.substr(0, returnIndexOfNumber(str)));
// 			return (splitMixedTerm(str.substr(returnIndexOfNumber(str))));	
// 		}
// 		else {
// 			correctStrings.push_back(str.substr(0, returnIndexOfOperand(str)));
// 			return splitMixedTerm(str.substr(returnIndexOfOperand(str)));	
// 		}
// 	}
// 	else if (foundNumber(str)) {
// 		correctStrings.push_back(str.substr(0, returnIndexOfNumber(str)));
// 		return (splitMixedTerm(str.substr(returnIndexOfNumber(str))));
// 	}
// 	else if (foundOperator(str)) {
// 		correctStrings.push_back(str.substr(0, returnIndexOfOperand(str)));
// 		return splitMixedTerm(str.substr(returnIndexOfOperand(str)));
// 	}
// 	if (str.length() > 0) {
// 		correctStrings.push_back(str);
// 	}
// }

void	Validate::splitForOperand(string str) {
	if (foundNumber(str) && foundEqualSign(str)) {
		if (returnIndexOfNumber(str) < (int)str.find("=")) {
			correctStrings.push_back(str.substr(0, returnIndexOfNumber(str)));
			return (splitMixedTerm(str.substr(returnIndexOfNumber(str))));
		}
		else {
			correctStrings.push_back(str.substr(0, str.find("=")));
			return splitMixedTerm(str.substr(str.find("=")));
		}
	}
	else if (foundNumber(str)) {
		correctStrings.push_back(str.substr(0, returnIndexOfNumber(str)));
		return (splitMixedTerm(str.substr(returnIndexOfNumber(str))));
	}
	else if (foundEqualSign(str)) {
		correctStrings.push_back(str.substr(0, str.find("=")));
		return splitMixedTerm(str.substr(str.find("=")));
	}
	if (str.length() > 0) {
		correctStrings.push_back(str);
	}
}

void	Validate::splitMixedTerm(string str) {
	if (isalpha(str[0]) || isdigit(str[0])) {
		return (splitForAlpha(str));
	}
	else if (isdigit(str[0])) {
		return (splitForDigit(str));
		// return (splitForDigit(str));
	}
	// else if (str[0] == '=') {
	// 	return (splitForEqualSign(str));
	// }
	else if (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/') {
		return (splitForOperand(str));
	}
	if (str.length() > 0) {
		correctStrings.push_back(str);
	}
}

void	Validate::correctSplit() {
	int	index = -1;

	while (++index < (int)tempStrings.size()) {
		if (mixedTerm(tempStrings[index])) {
			splitMixedTerm(tempStrings[index]);
		}
		else if (tempStrings[index].length() > 0) {
			correctStrings.push_back(tempStrings[index]);
		}
	}
	for (size_t i = 0; i < correctStrings.size(); i++) {
		cout << "Split String >> " << correctStrings[i] << endl;
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
		if (correctStrings[index][0] != '=') {
			term *termClass = new term(correctStrings[index + 1], correctStrings[index][0], termSide);
			equation->addTerm(termClass);
			index += 2;
		}
		else {
			termSide++;
			if (correctStrings[index + 1][0] != '+' && correctStrings[index + 1][0]!= '-') {
				term *termClass = new term(correctStrings[index + 1], '+', termSide);
				equation->addTerm(termClass);
				index += 2;
			}
			else {
				index++;
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

	while (++index < len) {
		if (equation->getTerm(index)->isVar()) {
			if (instructions.findInstruction(equation->getTerm(index)->getVariable()) == NULL) {
				return (false);
			}
			tempTerm = equation->getTerm(index);
			tempTerm->replaceVariable(instructions.findInstruction(tempTerm->getVariable())->getfloatValue());	}
	}
	return (true);
}

bool	Validate::isPolynomialValid(string poly, polynomial *equation, Instruction instructions) {
	splitString(poly);
	correctSplit();

	if (!checkPolynomialAuthentacity()) {
		return (false);
	}
	addexpression(equation);
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
