/*PROGRAM COMMENTS*/

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

//Access the file
//fstream input("Data.txt");
////Display error if it doesn't work
//
//if (input.fail())
//{
//     cerr << "Error opening input file.";
//     exit(1);
//};
struct strStorage 
{
public:
     string strArr[8];
};

// First we need to define our node class as that is the class we'll need in order to create our linked chain
class Node
{
private:
     int item = 0;
     Node* next; // next is a class pointer, next has access to all objects members and functions
     Node* prev;
public:
     Node() : next(nullptr), prev(nullptr) { }
     Node(const int& anItem): next(nullptr), prev(nullptr), item(anItem) { }
     Node(const int& anItem, Node* nextNodePtr, Node* prevNodePtr) : next(nextNodePtr), prev(prevNodePtr), item(anItem) { }
     void setItem(const int& anItem) { item = anItem; }
     void setNext(Node* nextNodePtr) { next = nextNodePtr; }
     void setPrev(Node* prevNodePtr) { prev = prevNodePtr; }
     int getItem() const { return item; }
     Node* getNext() const { return next; }
     Node* getPrev() const { return prev; }
}; // End of the Node class

// Beginning of lkdBN class
class lkdBN 
{
private:
     Node* headPtr; // headPtr is a pointer of class Node for the lkdBN class
     Node* tailPtr;
     int itemCount;
public:
     lkdBN(): itemCount(0), headPtr(nullptr), tailPtr(nullptr) {}
     //~lkdBN() { delete [];}
     int getCurrentSize() const { return itemCount; }
     void insertStrVal(const string& strex);
     bool addFH(const int& newItem);
     vector<int> toVector() const;
     string addBN(const lkdBN& BN2);
     bool mulBN(const lkdBN& BN2);
};
// beginning of ldkBN function definitions
void lkdBN::insertStrVal(const string& strex) // breaks the string up and converts it to an int
{
     int i = 0;
     while (i < strex.length())
     {
          char charArr[5];
          string str = strex.substr(i, 4);
          strcpy_s(charArr, str.c_str());
          int n = atoi(charArr);
          this->addFH(n); 
          /* everytime this loop executes, the object of class lkdBN should create a chain of new nodes, 
             where each new node will have their item equal to a 0-4 digit number that is taken from the string*/
          i = i + 4;
     }
}
bool lkdBN::addFH(const int& newItem)
{
     Node* newNodePtr = new Node();     // create a new Node object
     newNodePtr->setItem(newItem);      // set the item in this new node to equal to newItem
     if (headPtr == nullptr)
     {
          headPtr = newNodePtr;
          tailPtr = newNodePtr;
     }
     else
     {
          newNodePtr->setNext(headPtr);      // have this node's pointer point to whatever the head pointer was pointing too before this node came to existence
          headPtr->setPrev(newNodePtr);              // Have the headPtr now point to our new Node object
          headPtr = newNodePtr;
     }
     itemCount++;
     return true;
}
vector<int> lkdBN::toVector() const
{
     vector<int> BNVec;
     Node* curPtr = headPtr;
     int counter = 0;
     while ((curPtr!=nullptr) && (counter < itemCount))
     {
          BNVec.push_back(curPtr->getItem());
          curPtr = curPtr->getNext();
          counter++;
     }
     for (int i = 0; i < counter; i++)
     {
          cout <<BNVec[i] <<" ";
     }
     return BNVec;
}
string lkdBN::addBN( const lkdBN& BN2)
/*
The add function so that it can create a new lkdBN object that stores the sum of two lkdBN objects
This is a function meant for a third object to access two previous objects items and to add them together.*/
{
     lkdBN AddBN;
     Node* curPtr1 = this->headPtr;
     Node* curPtr2 = BN2.headPtr;
     int counter = 0;
     int BN1size = this->getCurrentSize(), BN2size = BN2.getCurrentSize(), size;
     if (BN1size < BN2size)
          size = BN1size;
     else
          size = BN2size;
     while (counter < size)
     {
          int a = curPtr1->getItem();
          int b = curPtr2->getItem();
          int c = a + b;
          AddBN.addFH(c);
          curPtr1 = curPtr1->getNext();
          curPtr2 = curPtr2->getNext();
          counter++;
     }
     if (BN1size > BN2size)
     {
          while (counter < BN1size)
          {
               int a = curPtr1->getItem();
               AddBN.addFH(a);
               curPtr1 = curPtr1->getNext();
               counter++;
          }
     }
     else
     {
          while (counter < BN2size)
          {
               int b = curPtr2->getItem();
               AddBN.addFH(b);
               curPtr2 = curPtr2->getNext();
               counter++;
          }
     }
     Node* curPtr = AddBN.tailPtr;
     while (curPtr != nullptr)
     {
          if (curPtr->getItem() > 9999)
          {
               // cout << "The Bad value is: " << curPtr->getItem();
               curPtr->setItem(curPtr->getItem() - 10000);
               curPtr = curPtr->getPrev();
               // cout << "\nThe Value we want to increment by 1 is: " << curPtr->getItem();
               curPtr->setItem(curPtr->getItem() + 1);
          }
          curPtr = curPtr->getPrev();
     }
     cout << "\nThe sum of the two large numbers is\n";
     string strBN;
     curPtr = AddBN.tailPtr;
     while (curPtr != nullptr)
     {
          int n = curPtr->getItem();
          char filler[5];
          _itoa_s(n, filler, 10);
          strBN.insert(0, filler);
          curPtr = curPtr->getPrev();
     }
     cout << strBN;
     return strBN;
}
bool lkdBN::mulBN(const lkdBN& BN2)
{
     lkdBN MulBN;
     Node* curPtr1 = this->headPtr;
     Node* curPtr2 = BN2.headPtr;
     int BN1size = this->getCurrentSize(), BN2size = BN2.getCurrentSize();
     vector<vector<int>> storageVec2D(BN1size, vector<int>(BN2size)); // this creates a 2D vector of size BN1Size x BN2Size
     // nested loop to store the products of each node item into a 2D vector
     for (int i = 0; i < BN1size; i++)
     {
          int n = curPtr1->getItem(); // setting n to equal to the current Node of the "this" chain
          for (int j = 0; j < BN2size; j++)
          {
               int m = curPtr2->getItem(); // setting m to equal to the current Node of the BN2 chain
               int prod = n * m;
               storageVec2D[i][j] = prod;
               curPtr2 = curPtr2->getNext();
          }
          curPtr2 = BN2.headPtr; // we need to reset the node position everytime the second for loop finishes b/c at the end of the second for loop, curPtr2 points to the null ptr
          curPtr1 = curPtr1->getNext();
     } // end nested loop
     for (int i = 0; i < BN1size-1; i++) // This is a waterfall nested loop that adds all of the products into the (i,0) value and (BN1size-1,j) row, since all the base powers of 10^{0,4,8,12...n) are all located in these two specific areas
     {
          for (int j = 1; j < BN2size; j++)
          {
               storageVec2D[i + 1][j - 1] = storageVec2D[i + 1][j - 1] + storageVec2D[i][j];
          }
     }// end of storageVec2D nested loop for addition waterfall

     // Nested loop to take the contents from storageVec2D and add them into our linked chain object MulBN
     for (int i = 0; i < BN1size; i++)
     {
          for (int j = 0; j < BN2size; j++)
          {
               if ((j == 0) or (i == BN1size - 1))
                    MulBN.addFH(storageVec2D[i][j]);
          }
     }
     // All of the summed products should now be in the MulBN node chain
     /*So now here is the code to fix the large numbers by taking the ones that are larger than 4 digits long,
     by dividing each node by 10000, setting that as rem, subtracting rem * 10000 by the current item and then 
     taking the rem and adding it to the next node item.*/
     Node* curPtr = MulBN.tailPtr;
     int rem = 0, mulItem = 0;
     while (curPtr != MulBN.headPtr)
     {
          if (curPtr->getItem() > 9999)
          {
               mulItem = curPtr->getItem();
               rem = mulItem / 10000;
               curPtr->setItem(curPtr->getItem() - (rem * 10000));
               curPtr = curPtr->getPrev();
               curPtr->setItem(curPtr->getItem() + rem);
          }
     }
     // This command is literally here because we can't leave Node 0, which contains the highest power larger than 4 digits, so we have to take it's remainder, subtract it and create a new node with the remainder
     if (MulBN.headPtr->getItem() > 9999)
     {
          mulItem = curPtr->getItem();
          rem = mulItem / 10000;
          curPtr->setItem(curPtr->getItem() - (rem * 10000));
          MulBN.addFH(rem);
     }
     // Code for the output of the product
     cout << "The product of the two large numbers is\n";
     string strBN;
     curPtr = MulBN.tailPtr;
     while (curPtr != nullptr)
     {
          int n = curPtr->getItem();
          char filler[5];
          _itoa_s(n, filler, 10);
          strBN.insert(0, filler);
          curPtr = curPtr->getPrev();
     }
     cout << strBN;
     return true;
}

// Independent function that is not related to the classes whatsoever
string strManip(string& strex);

int main()
{
     string str1 = "400568", str2 = "55789456";
     strManip(str1);
     strManip(str2);
     lkdBN BigNum1;
     lkdBN BigNum2;
     BigNum1.insertStrVal(str1);
     BigNum2.insertStrVal(str2);
     BigNum1.mulBN(BigNum2);
     cout << endl << "Yay my program worked!" << endl;
     return 0;
}

string strManip(string& strex) 
{
     // Code to make string have length = multiple of 4
     string zero = "0";
     while (strex.length() % 4 != 0)
     {
          strex.insert(0, zero);
     }
     return strex;
}

