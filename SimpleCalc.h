#ifndef SIMPLE_CALC_H
#define SIMPLE_CALC_H

#include <string>

#define PI 3.141592653589793238462643
#ifndef nullptr
#define nullptr NULL
#endif
#ifndef uint_16
#define uint_16 unsigned short int
#endif

template <class T> class Node;

template <class T>
class stack {
    Node<T>* head;
public:
    stack();
    ~stack();

    void push(T param);
    T pop();

    void traverse();

    inline bool isEmpty();
    inline T lastValue();
};



template <class T> 
class Node {
    friend class stack<T>;

    T value;
    Node<T>* next;

    Node();
    Node(T val);
    ~Node();
};


using namespace std;

inline bool isNum (const char& param);
inline bool isAlphabet (const char& param);

string toLowerCase (string param);
string toUpperCase (string param);
template <class T>
T toNum (const string& param);

template <class T>
T eval (T opand1, const char& optor, T opand2);
char precLevel(const char& a);

template <class T>
void calc (stack<T>* operandStr, stack<char>* operatorStr);

template <class T> 
T calculator (const string& formula);

template <typename T> 
void continuousCalculator (const string& formula);

void credit();
void help();

#endif