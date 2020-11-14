#include <iostream>
#include <string>
using namespace std;

class Node
{
private:
     char item = ' ';
     Node* next; // next is a class pointer, next has access to all objects members and functions
     Node* prev;

public:
     Node() : next(nullptr), prev(nullptr) { }
     Node(char& anItem) : next(nullptr), prev(nullptr), item(anItem) { }
     Node(char& anItem, Node* nextNodePtr) : next(nextNodePtr), prev(nextNodePtr), item(anItem) { }
     void setItem(const int& anItem) { item = anItem; }
     void setNext(Node* nextNodePtr) { next = nextNodePtr; }
     void setPrev(Node* prevNodePtr) { prev = prevNodePtr; }
     char getItem() const { return item; }
     Node* getNext() const { return next; }
     Node* getPrev() const { return prev; }
}; // End of the Node class


// CLASS LINKED STACK BEGINS ////////////////////////////////////////////////////////////////////////////////////////
class Stack
{
private:
     Node* topPtr;
public:
     Stack() { topPtr = nullptr; }
     ~Stack();
     bool isEmpty() const;
     bool push(char str);
     bool pop();
     char peek() const;
};

Stack::~Stack()
{
     while (!isEmpty())
          pop();
}
bool Stack::isEmpty() const
{
     return topPtr == nullptr;
}
bool Stack::push(char ltr)
{
     Node* newNodePtr = new Node(ltr, topPtr);
     topPtr = newNodePtr;
     newNodePtr = nullptr;
     return true;
}
bool Stack::pop()
{
     bool result = false;
     if (!isEmpty())
     {
          Node* nodeToDeletePtr = topPtr;
          topPtr = topPtr->getNext();
          nodeToDeletePtr->setNext(nullptr);
          delete nodeToDeletePtr;
          nodeToDeletePtr = nullptr;
          result = true;
     }
     return result;
}
char Stack::peek() const
{
     return topPtr->getItem();
}
// CLASS LINKED STACK ENDS   ////////////////////////////////////////////////////////////////////////////////////////


// CLASS LINKED QUEUE BEGINS ////////////////////////////////////////////////////////////////////////////////////////
class LinkedQueue
{
private:
     Node* backPtr;
     Node* frontPtr;
public:
     LinkedQueue() {frontPtr = nullptr, backPtr = nullptr;}
     ~LinkedQueue() {;}
     bool isEmpty() const;
     bool enqueue(char newEntry);
     bool dequeue();
     char peekFront();
     char peekBack();
     void displayQueue();
};
bool LinkedQueue::isEmpty() const
{
     return frontPtr == nullptr;
}
bool LinkedQueue::enqueue(char newEntry)
{
     Node* newNodePtr = new Node(newEntry);
     if (isEmpty())
          frontPtr = newNodePtr;
     else
          backPtr->setNext(newNodePtr);
     backPtr = newNodePtr;
     return true;
}
bool LinkedQueue::dequeue()
{
     bool result = false;
     if (!isEmpty())
     {
          Node* nodeToDeletePtr = frontPtr;
          if (frontPtr == backPtr)
          {
               frontPtr = nullptr;
               backPtr = nullptr;
          }
          else
               frontPtr = frontPtr->getNext();
          nodeToDeletePtr->setNext(nullptr);
          delete nodeToDeletePtr;

          result = true;
     }
     return result;
}
char LinkedQueue::peekFront()
{
     return frontPtr->getItem();
}
char LinkedQueue::peekBack()
{
     return backPtr->getItem();
}

void LinkedQueue::displayQueue()
{
     Node* curPtr = frontPtr;
     while (curPtr != nullptr)
     {
          cout << curPtr->getItem();
          curPtr = curPtr->getNext();
     }
}
// CLASS LINKED QUEUE ENDS ////////////////////////////////////////////////////////////////////////////////////////

// CLASS LINKED DEQUEUE BEGINS ////////////////////////////////////////////////////////////////////////////////////
class LinkedDequeue
{
private:
     Node* backPtr;
     Node* frontPtr;
public:
     LinkedDequeue() { frontPtr = nullptr, backPtr = nullptr; }
     ~LinkedDequeue() { ; }
     bool isEmpty() const;
     bool enqueue(char newEntry);
     bool dequeue();
     char peekFront();
     char peekBack();
     void displayQueue();
     bool dequeueBack();
     Node* returnBackPtr() { return backPtr; }
};
bool LinkedDequeue::isEmpty() const
{
     return frontPtr == nullptr;
}
bool LinkedDequeue::enqueue(char newEntry)
{
     Node* newNodePtr = new Node(newEntry);
     if (isEmpty())
          frontPtr = newNodePtr;
     else
          backPtr->setNext(newNodePtr);
     backPtr = newNodePtr;
     return true;
}
bool LinkedDequeue::dequeue()
{
     bool result = false;
     if (!isEmpty())
     {
          Node* nodeToDeletePtr = frontPtr;
          if (frontPtr == backPtr)
          {
               frontPtr = nullptr;
               backPtr = nullptr;
          }
          else
               frontPtr = frontPtr->getNext();
          nodeToDeletePtr->setNext(nullptr);
          delete nodeToDeletePtr;

          result = true;
     }
     return result;
}
char LinkedDequeue::peekFront()
{
     return frontPtr->getItem();
}
char LinkedDequeue::peekBack()
{
     return backPtr->getItem();
}

void LinkedDequeue::displayQueue()
{
     Node* curPtr = frontPtr;
     while (curPtr != nullptr)
     {
          cout << curPtr->getItem();
          curPtr = curPtr->getNext();
     }
}
bool LinkedDequeue::dequeueBack()
{
     bool result = false;
     if (!isEmpty())
     {
          Node* nodeToDeletePtr = backPtr;
          if (backPtr == frontPtr)
          {
               frontPtr = nullptr;
               backPtr = nullptr;
          }
          else
               backPtr = backPtr->getPrev();
          nodeToDeletePtr->setPrev(nullptr);
          delete nodeToDeletePtr;
          result = true;
     }
     return result;
}
// CLASS LINKED DEQUEUE ENDS //////////////////////////////////////////////////////////////////////////////////////

// LETTERPALINDROME1 BEGINS////////////////////////////////////////////////////////////////////////////////////////
bool letterPalindrome1(const string& str)
{
     // Get length of string
     int len = str.length();
     // Initialize a stack and queue object
     Stack stack;
     LinkedQueue queue;
     // Push the palindrome onto the stack and queue it onto the queue
     for (int i = 0; i < len; i++)
     {
          stack.push(tolower(str[i]));
          queue.enqueue(tolower(str[i]));
     }
     // Create Stack Ptr and Queue Ptr so that we can access their private members
     Stack* stackPtr = &stack;
     LinkedQueue* queuePtr = &queue;
     // Check if it's a palindrome
     bool isPalindrome = true;
     while (!stack.isEmpty() && !queue.isEmpty())
     {
          // Peek at stack's top value and queue's front value and see if they are =
          if (stack.peek() != queue.peekFront())
          {
               cout << "Not a palindrome.";
               isPalindrome = false;
               return isPalindrome;
          }
          stack.pop();
          queue.dequeue();
     }
     cout << "It is a palindrome.";
     return isPalindrome;
}
// LETTERPALINDROME1 ENDS ///////////////////////////////////////////////////////////////////////////////////////
// LETTERPALINDROME2 BEGINS /////////////////////////////////////////////////////////////////////////////////////
bool letterPalindrome2(const string& str)
{
     LinkedDequeue dequeue;
     bool isPalindrome = true;
     for (int i = 0; i < str.length(); i++)
          dequeue.enqueue(tolower(str[i]));
     // Check if front of queue is = to back of queque
     while ((dequeue.returnBackPtr() != nullptr))
     {
          if (dequeue.peekFront() != dequeue.peekBack())
          {
               cout << "Not a palindrome.";
               isPalindrome = false;
               return isPalindrome;
          }
          dequeue.dequeue();
          dequeue.dequeueBack();
     }
     cout << "It is a palindrome.";
     return isPalindrome;
}
// LETTERPALINDROME2 ENDS ///////////////////////////////////////////////////////////////////////////////////////

// LETTERPALINDROME3 BEGINS /////////////////////////////////////////////////////////////////////////////////////
bool letterPalindrome3(const string& str)
{
     bool isPalindrome = true;
     Stack stack;
     LinkedQueue queue;
     for (int i = 0; i < str.length(); i++)
     {
          if (str[i] == ' ' or str[i] == '.' or str[i] == ',' or str[i] == ':' or str[i] == '’' or str[i] == '!' or str[i] == '?')
               continue;
          else
          {
               stack.push(tolower(str[i]));
               queue.enqueue(tolower(str[i]));
          }
     }
     while (!stack.isEmpty() && !queue.isEmpty())
     {
          // Peek at stack's top value and queue's front value and see if they are =
          if (stack.peek() != queue.peekFront())
          {
               cout << "Not a palindrome.";
               isPalindrome = false;
               return isPalindrome;
          }
          stack.pop();
          queue.dequeue();
     }
     cout << "It is a palindrome.";
     return isPalindrome;
}
// LETTERPALINDROME3 ENDS ///////////////////////////////////////////////////////////////////////////////////////

// LETTERPALINDROME4 BEGINS /////////////////////////////////////////////////////////////////////////////////////
bool letterPalindrome4(const string& str)
{
     bool isPalindrome = true;
     LinkedDequeue dequeue;
     for (int i = 0; i < str.length(); i++)
     {
          if (str[i] == ' ' or str[i] == '.' or str[i] == ',' or str[i] == ':' or str[i] == '’' or str[i] == '!' or str[i] == '?')
               continue;
          else
               dequeue.enqueue(tolower(str[i]));
     }
     // Check if front of queue is = to back of queque
     while ((dequeue.returnBackPtr() != nullptr))
     {
          if (dequeue.peekFront() != dequeue.peekBack())
          {
               cout << "Not a palindrome.";
               isPalindrome = false;
               return isPalindrome;
          }
          dequeue.dequeue();
          dequeue.dequeueBack();
     }
     cout << "It is a palindrome.";
     return isPalindrome;
}
// LETTERPALINDROME4 ENDS ///////////////////////////////////////////////////////////////////////////////////////

int main()
{
     letterPalindrome1("radar");
     letterPalindrome2("RaDaR");
     letterPalindrome3("A Toyota’s a Toyota.");
     letterPalindrome4("A Toyota’s a Toyota.");
     return 0;
}
