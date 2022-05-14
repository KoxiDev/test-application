// calc.cpp
// provides the <Calculate> function.

#include <string>

bool ValidateNumber(std::string n) {
	if (n.empty())
		return false;
	for (char c : n)
		if (c < 48 || c > 57)
			return false;
	return true;
}

std::string Calculate(std::string input) {
	if (input == "huge")
		return std::to_string(INTMAX_MAX);
	std::string s1 = "", s2 = "";
	char op;
	bool secn = false;
	for (char c : input) {
		switch (c) {
			case '+': case '-': case '*': case '/':
				op = c;
				secn = true;
				break;
			default:
				if (!secn)
					s1 += c;
				else
					s2 += c;
		}
	}
	
	if (ValidateNumber(s1) && s2 == "" && op == 0)
		return s1;
	if (s1 == "" || s2 == "")
		return "error: cannot compute null.";
	if (!(ValidateNumber(s1) && ValidateNumber(s2)))
		return "error: malformed number.";
		
	int result;
	int n1 = stoi(s1);
	int n2 = stoi(s2);
	switch (op) {
		case '+':
			result = n1 + n2;
			break;
		case '-':
			result = n1 - n2;
			break;
		case '*':
			result = n1 * n2;
			break;
		case '/':
			result = n1 / n2;
			break;
		default:
			return "error: invalid operator.";
	}
	return std::to_string(result);
}
