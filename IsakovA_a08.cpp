/*PROGRAM COMMENTS
Implementation of Binary Tree using linked nodes. All functions use recursion in order to fully operate this Binary Tree.
*/

#include <iostream>
#include <stdexcept>

using namespace std;

// NotFoundExcept class
class NotFoundExcept : public logic_error 
{
public:
     NotFoundExcept(const string& msg = "")
          : logic_error("Target not found: " + msg) { }
};

// PrecondViolatedExcept class
class PrecondViolatedExcept : public logic_error {
public:
     PrecondViolatedExcept(const string& msg = "")
          : logic_error("Precondition violated exceptn: " + msg) { }
};

// Binary tree node class BNode, or Binary Node 
template<class T>
class BNode {
public:
     T item;
     BNode<T>* lChild;
     BNode<T>* rChild;
     BNode() : lChild(NULL), rChild(NULL) { }
     BNode(const T& anItem) : item(anItem), lChild(NULL), rChild(NULL) { } 
     BNode(const T& anItem, BNode<T>* left, BNode<T>* right) :
          item(anItem), lChild(left), rChild(right) { } 
     bool isLeaf() const {
          if (lChild == NULL && rChild == NULL) 
               return true; 
          return false;
     }
};

// Link-based binary tree class 
template<class T>
class Tree {
private:
     BNode<T>* root;
     // recursive helper methods
     int gHeiHlp(BNode<T>* subTr) const; // get tree height helper
     int gNumOfNodesHlp(BNode<T>* subTr) const; // get number of nodes helper 
     BNode<T>* balancedAdd( BNode<T>*& subTr, BNode<T>* nNode );

     BNode<T>* cpyTree(const BNode<T>* oldRt) const; 
     void destroyTree(BNode<T>*& subTr);
     void preorder(void visit(T&), BNode<T>* tr) const; 
     void inorder(void visit(T&), BNode<T>* tr) const; 
     void postorder(void visit(T&), BNode<T>* tr) const;

public:
     //-------------------------------------------------------------------
     //        Constructors and Destrcutor
     //-------------------------------------------------------------------
     Tree() : root(NULL) { }	// default ctor
     Tree(const T& rtItem) : root(new BNode<T>(rtItem, NULL, NULL)) {} 
     Tree(const T& rtItem, const BNode<T>*& lTr, const BNode<T>*& rTr) :
          root(new BNode<T>(rtItem, cpyTree(lTr->root), cpyTree(rTr->root))) {}
     Tree(const Tree<T>& rhs) { root = cpyTree(rhs.root); } // copy constructor
     ~Tree() { destroyTree(root); }
     //-------------------------------------------------------------------
     //        Acessor and Modifier Functions
     //-------------------------------------------------------------------
     bool isEmpty() const { return root == NULL; }
     int gHei() const { return gHeiHlp(root); } // get tree height 
     int gNumOfNodes( ) const { return gNumOfNodesHlp( root ); }

     T gRtData() const throw(PrecondViolatedExcept) { 
          if (isEmpty())
               throw PrecondViolatedExcept("Tree is empty.");
          else
               return root->item; 
     } // get root data 
     void sRtData(const T& nData) { 
          if (root == nullptr)
               root = new BNode<T>(nData);
          else
               root->item = nData;
     } // set root data
     bool add(const T& nData);	// calls balancedAdd() 
     void clear( ) { destroyTree( root ); root = NULL; }
     T gEnt(const T& anEnt) const throw(NotFoundExcept); // get entry
     BNode<T>* btFind(BNode<T>* subTr, const T& target) const;
     //-------------------------------------------------------------------
     //        Traversal Functions
     //-------------------------------------------------------------------
     void preTrav(void visit(T&)) const { preorder(visit, root); } 
     void inTrav(void visit(T&)) const { inorder(visit, root); } 
     void postTrav(void visit(T&)) const { postorder(visit, root); }
};

// Implementation of cpyTree
template <class T>
BNode<T>* Tree<T>::cpyTree(const BNode<T>* oldRt) const
{
     BNode<T>* newTreePtr = nullptr;
     // Copy tree nodes using preorder traversal
     if (oldRt != nullptr)
     {
          newTreePtr = new BNode<T>(oldRt->item, nullptr, nullptr);
          newTreePtr->lChild = cpyTree(oldRt->lChild);
          newTreePtr->rChild = cpyTree(oldRt->rChild);
     }
     return newTreePtr;
}

// Implementation of destroyTree
template <class T>
void Tree<T>::destroyTree(BNode<T>*& subTr)
{
     if (subTr != nullptr)
     {
          destroyTree(subTr->lChild);
          destroyTree(subTr->rChild);
          delete subTr;
     }
}
// Implementation of gHeiHlp
template <class T>
int Tree<T>::gHeiHlp(BNode<T>* subTr) const
{
     if (subTr == nullptr)
          return 0;
     else
          return 1 + max(gHeiHlp(subTr->lChild), 
                         gHeiHlp(subTr->rChild));
}
// Implementation of add
template <class T>
bool Tree<T>::add(const T& nData)
{
     BNode<T>* newNodePtr = new BNode<T>(nData);
     root = balancedAdd(root, newNodePtr);
     return true;
}
// Implementation of balancedAdd
template <class T>
BNode<T>* Tree<T>::balancedAdd(BNode<T>*& subTr, BNode<T>* nNode)
{
     if (subTr == nullptr)
          return nNode;
     else
     {
          BNode<T>* leftPtr = subTr->lChild;
          BNode<T>* rightPtr = subTr->rChild;
          
          if (gHeiHlp(leftPtr) > gHeiHlp(rightPtr))
          {
               rightPtr = balancedAdd(rightPtr, nNode);
               subTr->rChild = rightPtr;
          }
          else
          {
               leftPtr = balancedAdd(leftPtr, nNode);
               subTr->lChild = leftPtr;
          }
          return subTr;
     }
}
// Implementation of inorder which is LVR
template <class T>
void Tree<T>::inorder(void visit(T&), BNode<T>* tr) const
{
     if (tr != nullptr)
     {
          inorder(visit, tr->lChild);
          T theItem = tr->item;
          visit(theItem);
          inorder(visit, tr->rChild);
     }
}
// Implementation of preorder which is VLR
template <class T>
void Tree<T>::preorder(void visit(T&), BNode<T>* tr) const
{
     if (tr != nullptr)
     {
          T theItem = tr->item;
          visit(theItem);
          preorder(visit, tr->lChild);
          preorder(visit, tr->rChild);
     }
}
// Implementation of postorder which is LRV
template <class T>
void Tree<T>::postorder(void visit(T&), BNode<T>* tr) const
{
     if (tr != nullptr)
     {
          postorder(visit, tr->lChild);
          postorder(visit, tr->rChild);
          T theItem = tr->item;
          visit(theItem);
     }
}
// Implementation of gNumOfNodesHlp
template <class T>
int Tree<T>::gNumOfNodesHlp(BNode<T>* subTr) const
{
     if (subTr == nullptr)
          return 0;
     else
          return 1 + gNumOfNodesHlp(subTr->lChild) + gNumOfNodesHlp(subTr->rChild);
}
// Implementation of gEnt
template <class T>
T Tree<T>::gEnt(const T& anEnt) const throw(NotFoundExcept)
{
     BNode<T>* nd = btFind(root, anEnt);
     if (nd == nullptr)
          throw NotFoundExcept("Entry not found in tree.");
     else
          return nd->item;
}
// Implementation of btFind
template <class T>
BNode<T>* Tree<T>::btFind(BNode<T>* subTr, const T& target) const
{
     if (subTr == nullptr)
          return nullptr;
     else if (subTr->item == target)
          return subTr;
     else if (subTr->item > target)
          return btFind(subTr->lChild, target);
     else
          return btFind(subTr->rChild, target);
}
void print(int& x)
{
     cout << x << " ";
}
void print(string& s)
{
     cout << s << " ";
}

// Driver Code
int main()
{
     Tree<int> intTree;
     intTree.add(1);
     intTree.add(2);
     intTree.add(3);
     cout << "intTree's root is: " << intTree.gRtData() <<endl;
     cout << "The height of intTree is: " << intTree.gHei() << endl;
     cout << "The number of nodes in intTree is: " << intTree.gNumOfNodes() <<endl;
     Tree<int> copyTree(intTree);
     cout << "intTree is not empty (should be 0): " << intTree.isEmpty() << endl;
     intTree.sRtData(4);
     cout << "intTree's new root is: " << intTree.gRtData() << endl;
     cout << "Post Order Traversal: "; 
     intTree.postTrav(print);
     cout << endl;
     cout << "In Order Traversal: ";
     intTree.inTrav(print);
     cout << endl;
     cout << "Pre Order Traversal: ";
     intTree.preTrav(print);
     cout << endl;
     cout << intTree.gEnt(2);
     return 0;
}