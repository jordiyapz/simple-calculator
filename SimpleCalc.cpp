#include <iostream>
#include <string>
#include <math.h>
#include "SimpleCalc.h"
using namespace std;

//###############################
//###          stack          ##
//#############################

//constructor and destructor
template <class T>
stack<T>::stack() {
    head = nullptr;
}
template <class T>
stack<T>::~stack() 
{
    T c;
    while (head != nullptr)
        c = pop();
}

//push and pop
template <class T>
void stack<T>::push(T param)
{
    Node<T>* newNode = new Node<T>(param);
    newNode -> next = head;
    head = newNode;
}
template <class T>
T stack<T>::pop()
{
    // if (head == nullptr)
    //     cerr << "Warning: Empty stack!\n";
    T out = 0;
    Node<T>* temp = nullptr;
    if (head != nullptr)
    {
        temp = head;
        head = temp -> next;
        temp -> next = nullptr;
    }
    if (temp != nullptr)
    {
        out = temp -> value;
        delete temp;        
    }
    else 
    {
        //cout << "Stack kosong";
        // throw 20;
    }
    return out;
}

//display
template <class T>
void stack<T>::traverse()
{
    Node<T>* p = head;
    
    while (p != nullptr)
    {
        cout << p -> value;
        p = p -> next;
        if (p != nullptr)
            cout << "->";
    }
    cout << "\n";
}

//conditionCheck
template <class T>
inline bool stack<T>::isEmpty()
{
    return (head == nullptr);
}
template <class T>
inline T stack<T>::lastValue()
{
    return head -> value;
}


//###############################
//###          Node           ##
//#############################

template <class T>
Node<T>::Node()
{
    next = nullptr;
}
template <class T>
Node<T>::Node(T val)
{
    value = val;
    next = nullptr;
}
template <class T>
Node<T>::~Node()
{
    next = nullptr;
}


//###############################
//###        functions        ##
//#############################

inline bool isNum (const char& param)
{
    return (param >= 48 && param <= 57);
}
inline bool isAlphabet (const char& param)
{
    return (param >= 65 && param <= 90 || param >= 97 && param <= 122);
}

string toLowerCase(string param)
{
    for(uint_16 i = 0; i < param.length(); i++)
		if (param[i] <= 90) param[i] += 32;
    return param;
}
string toUpperCase(string param)
{
    for(uint_16 i = 0; i < param.length(); i++)
		if (param[i] >= 97) param[i] -= 32;
    return param;
}

template <class T>
T toNum (const string& param)
{
    if (param.length() == 1 && isNum(param[0])) return param[0]-48;
	T temp = 0;
	bool neg = false;
	bool dot = false;
	uint_16 ct = 0;
	for (uint_16 i = 0; i < param.length(); i++) {
		if (param[i] == '-') neg = true; 
		if (param[i] == '.') dot = true; 
		else if (isNum(param[i])) {
			if (dot) ct++;
			temp = temp*10 + toNum<T>(param.substr(i,1));;
		}
	}
	if (neg) temp *= -1;
	for (uint_16 i = 0; i < ct; i++) {
		temp /= 10;
	}
	return temp;
}

template <class T>
T eval (T opand1, const char& optor, T opand2)
{
    switch(optor) {
		case '+' : return opand1 + opand2;
		case '-' : return opand1 - opand2;
		case '*' : return opand1 * opand2;
		case '/' : return opand1 / opand2;
		case '^' : return pow(opand1, opand2);
	}
}
char precLevel(const char& a)
{
    const char precedence[][2] = {{'+',1},{'-',1},{'*',2},{'/',2},{'^',3}};
	char level;
	for(uint_16 i = 0; i < 5; i++)
		if(a == precedence[i][0]) 
            level = precedence[i][1];
	return level;
}

template <class T>
void calc (stack<T>* operandStr, stack<char>* operatorStr)
{
    if (!operandStr -> isEmpty() && !operatorStr -> isEmpty())
    {
        T temp = operandStr -> pop();
        temp = eval<T>(operandStr -> pop(), operatorStr -> pop(), temp);
        operandStr -> push(temp);
    }
}

template <class T> T calculator (const string& formula)
{
    stack<T>* operandStr = new stack<T> (); //operand storage
	stack<char>* operatorStr = new stack<char> (); //operator storage
	string buff; 
	bool start = true;
	bool lastIsOperand = false;
	T result = 0;
	for (uint_16 i = 0; i < formula.length(); i++)
	{
		if (formula[i] == ' ') //Eliminate whitespaces
            continue; 
		else if (formula[i] == '(') { //Open bracket
			if (lastIsOperand) {
				operatorStr -> push('*');
				lastIsOperand = false;
			}
			operatorStr -> push(formula[i]);
			start = true;
		}
		else if (formula[i] == ')') { //Close bracket
			while (operatorStr -> lastValue() != '(') 
				calc(operandStr, operatorStr);	
			buff = operatorStr->pop();
		}
		else if (isAlphabet(formula[i])) { //Get Variable
			buff = "";
			while (isAlphabet(formula[i])) {
				buff += formula[i];
				i++;
			}
			i--;
			buff = toLowerCase(buff);
			if(buff.compare("pi") == 0) {
				if (lastIsOperand) 
                    operatorStr -> push('*');
				operandStr->push(PI);                
				lastIsOperand = true;
                if (start) 
                    start = false;
			}
		}
		else if (start || isNum(formula[i])) { //Get number
			if (lastIsOperand) {
				cerr << "Error input!\n";
				return 0;
			}
			buff = "";
			if (start) {
				if (formula[i] == '-') {
					buff += '-';
					i++;
				}
				start = !start;
			}
			while (isNum(formula[i]) || formula[i] == '.') { //extract number
				buff = buff + formula[i];
				i++;
			}
			i--;
			operandStr -> push( toNum<T>(buff) );
			lastIsOperand = true;
			// operandStr->traverse();
		}
		else if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' || formula[i] == '^') {
			
            if (!lastIsOperand) {
				cerr << "Error input!\n";
				return 0;
			}
			char pl = precLevel(formula[i]);
			if (operatorStr -> isEmpty() || operatorStr -> lastValue() == '(' || pl > precLevel( operatorStr -> lastValue() )) 
                operatorStr -> push( formula[i] );
			else {
				while (!operatorStr -> isEmpty() && pl <= precLevel( operatorStr -> lastValue() )) 
					calc (operandStr, operatorStr);	
				operatorStr -> push(formula[i]);
			}
			lastIsOperand = false;
			// operatorStr->traverse();
		}
		// cout << "opd: "; operandStr->traverse();
		// cout << "opr: "; operatorStr->traverse();

        //end of loop
	}
	while (!operatorStr->isEmpty()) 
		calc(operandStr, operatorStr);
	result = operandStr -> pop();

    delete operatorStr;
    delete operandStr;

	return result;
}

template <typename T> void continuousCalculator (const string& formula)
{
    static T answer = nanf(""); //float NaN
	string buff;
	bool startWithOperand = true;
	for (uint_16 i = 0; i < formula.length(); i++) {
		if (formula[i] == ' ') 
            continue;
		else 
        {
            if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' || formula[i] == '^') 
                startWithOperand = false;			
            break;
        }
	}
	if (startWithOperand || answer == nanf("")) {
		answer = calculator<T> (formula);
	} else {
		buff = to_string(answer) + formula;
		answer = calculator<T> (buff);
	}
	cout << ">> " << answer << "\n";
}

void credit() 
{
    cout << "\n~~~~~~~~~~~~~~~~~ Simple Calculator ~~~~~~~~~~~~~~~~~~\n";
    cout << ">> Written by Jordi Yaputra (1301180353)\n";
    cout << ">> Re-write : 16/02/2019 (First made: 25/10/2018)\n";
    cout << ">> Version : 1.5.0\n";
    cout << ">> Taught by the power of Otodidak (Self-Learning)\n\n";
    cout << ">> type \"help\" for more information\n";
    cout << ">> type \"exit\" to quit program\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

void help() 
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~ HELP ~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << ">> You may type in any number (0 - 9) [float type]\n";
    cout << ">> and/or any operator of ( + , - , * , / , ^ )\n";
    cout << ">> For example: 2.54 + 4 * (3 + 2) ^ 2 - 17 / 2\n";
    cout << ">> output: " << calculator<float>("2.54 + 4 * (3 + 2) ^ 2 - 17 / 2") << "\n";
    cout << ">> This program also support \"PI\"\n";
    cout << ">> Also, after performing first calculation, you can \n";
    cout << ">> type in the next calculation starting with an operator\n";
    cout << ">> For example:\n";
    cout << ":  -5 + (-4)PI^2\n";
    cout << ":  >> " << calculator<float>("-5 + (-4)PI^2") << "\n";
    cout << ":  * 9 ^ 2\n";
    cout << ":  >> " << calculator<float>("5 + (-4)PI^2 * 9 ^ 2") << "\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}