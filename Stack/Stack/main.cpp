#include <iostream>
#include <string>
#include <vector>

using namespace std;

__interface FormularUnit {
public:
	bool IsChar() = 0;
	double GetDValue() = 0;
	char GetCValue() = 0;
};

class Num : public FormularUnit {
private:
	double _value;
public:
	Num(double c) {
		_value = c;
	}
	double GetDValue() override {
		return _value;
	}
	char GetCValue() override { return ' '; }
	bool IsChar() override { return false; }


};

class Char : public FormularUnit {
private:
	char _value;
public:
	Char(char c) {
		_value = c;
	}
	double GetDValue() override { return 0; }
	char GetCValue() override { return _value; }
	bool IsChar() override { return true; }
	static bool Compare(Char* C1, Char* C2) {
		char c1 = C1->GetCValue();
		char c2 = C2->GetCValue();

		if (c2 == '(') return false;
		if (c2 == ')' || c2 == '+' || c2 == '-') return true;
		if (c1 == '*' || c1 == '/') return true;

		return false;
	}
};

bool CheckChar(char value) {
	if (value >= 48 && value <= 57) return false;
	return true;
}

double Calc(double d2, double d1, char op) {
	if (op == '+')
		return d1 + d2;
	if (op == '-')
		return d1 - d2;
	if (op == '*')
		return d1 * d2;
	if (op == '/')
		return d1 / d2;

}

int main() {

	char c = ' ';
	bool beforeNum = false;
	double numValue = 0;

	vector<FormularUnit *> formular;
	vector<Char*> chars;

	while (c != '=') {
		c = getc(stdin);
		if (c == '=') {
			if (beforeNum) {
				formular.push_back(new Num(numValue));
			}
			break;
		}
		if (c == ' ' || c == '\n')
			continue;
		if (!CheckChar(c)) {
			numValue *= 10;
			numValue += c - 48;
			beforeNum = true;
			continue;
		}
		if (beforeNum) {
			formular.push_back(new Num(numValue));
			numValue = 0;
		}
		beforeNum = false;

		Char* t1 = new Char(c);
		while (!chars.empty() && Char::Compare(chars.back(), t1)) {
			Char* t = chars.back();
			chars.pop_back();
			if (t->GetCValue() == '(') break;
			formular.push_back(t);
		}
		if (c == ')') continue;
		chars.push_back(t1);

	}

	while (!chars.empty()) {
		formular.push_back(chars.back());
		chars.pop_back();
	}
	vector<FormularUnit*>::iterator iter = formular.begin();

	/*
	for (; iter != formular.end(); iter++) {
		if ((*iter)->IsChar()) {
			cout << (*iter)->GetCValue() << ' ';
			continue;
		}
		cout << (*iter)->GetDValue() << ' ';
	}
	*/
	vector<FormularUnit*> numbers;
	iter = formular.begin();

	double retval = 0;

	for (; iter != formular.end(); iter++) {
		if ((*iter)->IsChar()) {
			double d1 = numbers.back()->GetDValue();
			numbers.pop_back();
			double d2 = numbers.back()->GetDValue();
			numbers.pop_back();
			
			numbers.push_back(new Num(Calc(d1, d2, (*iter)->GetCValue())));
			continue;
		}
		numbers.push_back(*iter);
	}

	cout << numbers.back()->GetDValue() << endl;

	return 0;
}
