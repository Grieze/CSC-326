/*PROGRAM NOTES
This program has two classes created within it. One being a class called Cat while the other is a template class
that allows you to create a Safe Array of any class type.
*/

#include <iostream>
#include <map>
using namespace std;

const int dSize = 10; // default size

// definition of Cat class
// Cat class works with template class, we're good on this end
class Cat {
private:
     int size;

public:
     Cat(int n);         // 1 parameter constructor
     Cat();              // defualt constructor
     ~Cat();             // destructor
     int GetSize() const { return size; } // function that returns the class' size
     void SetSize(int theSize) { size = theSize; }
     void Display() const { cout << size; }
     friend ostream& operator<< (ostream&, const Cat&);
};

// implemintations of Cat constructors

Cat::Cat(int n) : // custom constructor
     size(n)
{}

Cat::Cat() :        // set default weight to 0
     size(dSize)
{}
Cat::~Cat()
{}
ostream& operator<<
(ostream& theStream, const Cat& theCat)
{
     theStream << theCat.GetSize();
     return theStream;
}

template <class T> // definition of our template
class SA 
{
private:
     T *pT;         // pointer of T type
     int lIdx = 0;      // low index
     int hIdx = 0;     // high index
     int itsSize = dSize;
     
public:
     // constructors and destructors
     SA();                                                        // default constructor
     SA(int n);                                                   // 1 parameter constructor
     SA(int l, int h);                                            // 2 parameter constructor
     SA(const SA& arr);                                           // copy constructor
     ~SA() { delete[] pT; }                                       // destructor

     // operators
     SA& operator=(const SA& rhs);                                // assignment operator
     T& operator[](int offSet) { return pT[offSet]; }             // writer operator
     const T& operator[](int offSet) const { return pT[offSet]; } // reader operator
     
     // accessor
     int getSize() const { return itsSize; }  // member function that returns number of elements in SA

     // friend funtion
     template <class T>
     friend ostream& operator<< (ostream&, SA<T>&);
};


// implementations
// default constructor
template <class T>
SA<T>::SA() :
     itsSize(dSize)
{
     pT = new T[dSize];
}
// 1 parameter constructor
template <class T>
SA<T>::SA(int n) :
     itsSize(n)
{
     pT = new T[n];
}
// 2 parameter constructor
template <class T>
SA <T>::SA(int l, int h) :
     itsSize(h - l + 1) 
{
     lIdx = l;
     hIdx = h;
     pT = new T[itsSize]; // this tells our template classes pointer to create a new array
     pT = pT + lIdx; // shift the pointer offset by lIdx
}
// copy constructor
template <class T>
SA<T>::SA(const SA &rhs)
{
     itsSize = rhs.getSize();
     pT = new T[itsSize];
     for (int i = 0; i < itsSize; i++)
     {
          pT[i] = rhs[i];
     }
}
// operator=
template <class T>
SA<T>& SA<T>::operator=(const SA& rhs)
{
     if (this == &rhs)
     {
          return *this;
     }
     delete[] pT;
     itsSize = rhs.getSize();
     pT = new T[itsSize];
     for (int i = 0; i < itsSize; i++)
     {
          pT[i] = rhs[i];
     }
     return *this;
}
// operator<<
template <class T>
ostream& operator<< (ostream& output, SA<T>& theArray)
{
     output << theArray;
     return output;
}


// Driver code
int main()
{
     SA<int> intArr(12);           // create SA of type int
     SA<int> intArr2 = intArr;     // invoke copy constructor
     SA<Cat> catArr(12);           // create SA of type Cat
     SA<double> dblArr(12);        // create SA of type double
     cout << "intArr\tintArr2\tcatArr\tdblArr" << endl;
     for (int i = 0; i < intArr.getSize(); i++)
     {
          intArr[i] = i;
          intArr2[i] = i * 3;
          catArr[i] = i * i;
          dblArr[i] = i * 1.245;
          cout << intArr[i] << "\t" << intArr2[i] << "\t" << catArr[i] << "\t" << dblArr[i] << endl;
     }
     SA <int> intArr3(2, 6);       // create SA of type int using 2 parameter constructor, allowing me to index from offset base 2 to 6
     cout << intArr3.getSize() <<endl;
     for (int i = 2; i < 2+intArr3.getSize(); i++)
     {
          intArr3[i] = i + 4;
          cout << intArr3[i] << " ";
     }
     
     return 0;
}

