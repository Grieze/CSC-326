/*PROGRAM COMMENTS*/

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class PrecondViolatedExcept : public logic_error
{
public:
     PrecondViolatedExcept(const string& message = "");
};
PrecondViolatedExcept::PrecondViolatedExcept(const string& message) :
     logic_error("Precondition Violated Exception: " + message)
{
}

template<class T>
class dynArrStack {
     static const int deCap = 30;
     int top;
     T* items; // array in the dynamic memory storage
public:
     dynArrStack() : top(-1) { items = new T[deCap]; }           // defualt constructor
     dynArrStack(const dynArrStack<T>& rhs);                     // copy constructor
     ~dynArrStack() { delete[] items; top = -1; }                // destructor
     //dynArrStack<T>& operator=(const dynArrStack<T>& rhs);       // operator= overload
     bool isEmpty() const;                                       // accessor function
     bool push(const T& nEntry);
     bool pop();
     T peek() const throw(PrecondViolatedExcept);
     T peek2() const throw(PrecondViolatedExcept);
     int size() const { return top + 1; }
     T postFixCalc(string& postFixStr);
};


//template <class T>
//dynArrStack<T>& dynArrStack<T>:: operator=(const dynArrStack<T>& rhs)
//{
//     
//}
template <class T>
bool dynArrStack<T>::isEmpty() const
{
     return top < 0;
}
template <class T>
bool dynArrStack<T>::push(const T& nEntry)
{
     bool result = false;
     if (top < deCap - 1) // deCap - 1 = 29, the largest index element in stack
     {
          top++;
          items[top] = nEntry;
          result = true;
     }
     return result;
}
template <class T>
bool dynArrStack<T>::pop()
{
     bool result = false;
     if (!isEmpty())
     {
          top--;
          result = true;
     }
     return result;
}
template <class T>
T dynArrStack<T>::peek() const throw(PrecondViolatedExcept)
{
     if (isEmpty())
     {
          cout << "peek() called with empty stack";
          throw PrecondViolatedExcept("peek() called with empty stack");
     };

     return items[top];
}
template <class T>
T dynArrStack<T>::peek2() const throw(PrecondViolatedExcept)
{
     if (this->size()<1)
          throw PrecondViolatedExcept("peek2() called with stack missing 1 or more items");
     else
          cout <<"One below top\n" << items[top - 1] << "\nTop Item\n" << items[top];
    
     return items[top];
}
template <class T>
T dynArrStack<T>::postFixCalc(string& floats)
{
     int n = floats.length();
     string str;
     for (int i = 0; i < n; i++)
     {
          if (isdigit(floats[i]))
          {
               str = floats[i];
               double val = atof(str.c_str());
               this->push(val);
          }
          else if (floats[i] == '.')
          {
               double x = .1;
               do
               {
                    i++;
                    str = floats[i];
                    double val = atof(str.c_str());
                    val = val * x;
                    double stkval = this->peek();
                    this->pop();
                    stkval = stkval + val;
                    this->push(stkval);
                    x = x * x;
               } while (floats[i] != ' ');
          }
          else if (floats[i] == '+')
          {
               double topVal = this->peek();
               this->pop();
               double btmVal = this->peek();
               this->pop();
               this->push(btmVal + topVal);
          }
          else if (floats[i] == '*')
          {
               double topVal = this->peek();
               this->pop();
               double btmVal = this->peek();
               this->pop();
               this->push(btmVal * topVal);
          }
          else if (floats[i] == '-')
          {
               double topVal = this->peek();
               this->pop();
               double btmVal = this->peek();
               this->pop();
               this->push(btmVal - topVal);
          }
          else if (floats[i] == '/')
          {
               double topVal = this->peek();
               this->pop();
               double btmVal = this->peek();
               this->pop();
               this->push(btmVal / topVal);
          }
     }
     return this->peek();
};

int main()
{
     dynArrStack<double> dblStack; // initialize dynArrStack of type double which has default cap of 30 units
     string floats = "5.2 3.3 2.5 * + 4.1 - 5.5 +";
     dblStack.postFixCalc(floats);
     cout << dblStack.peek();
     return 0;
}
