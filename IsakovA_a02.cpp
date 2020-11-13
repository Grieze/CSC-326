/*PROGRAM COMMENTS
This program contains a class template of class ArrayBag. Within this class it tests 3 different functions meant to create new ArrayBag objects based on 2 previous instances of ArrayBag objects.
From there we have the three methods: Union, Intersection, and Difference.
The class also has various other methods meant to access private members of the class.*/

#include <iostream>
#include <vector>
using namespace std;


template <class T>
class ArrayBag
{
private:
     static const int dCap = 6;
     T items[dCap];
     int itemCount;
     int maxItems;
     int getIndexOf(const T& target) const;
public:
     // Constructors
     ArrayBag();
     int getCurrentSize() const { return itemCount; }
     bool isEmpty() const { return itemCount == 0; }
     bool add(const T& newEntry);
     bool remove(const T& anEntry);
     void clear();
     bool contains(const T& anEntry) const;
     int getFrequencyOf(const T& anEntry) const;
     vector<T>toVector() const;
     void displayItems() const;
     ArrayBag<T> Union(const ArrayBag<T> rhs);
     ArrayBag<T> Intersection(const ArrayBag<T> rhs);
     ArrayBag<T> Difference(const ArrayBag<T> rhs);
     

};

// Constructor
template <class T>
ArrayBag<T>::ArrayBag()
{
     itemCount = 0;
     maxItems = dCap;
}
// Add method
template <class T>
bool ArrayBag<T>::add(const T& newEntry)
{
     bool hasRoomToAdd = (itemCount < maxItems);
     if (hasRoomToAdd)
     {
          items[itemCount] = newEntry;
          itemCount++;
     }
     return hasRoomToAdd;
}
// toVector method
template<class T>
vector<T>ArrayBag<T>::toVector() const
{
     vector<T> bagContents;
     for (int i = 0; i < itemCount; i++)
          bagContents.push_back(items[i]);
     return bagContents;
}
// displayItems method
template<class T>
void ArrayBag<T>::displayItems() const
{
     for (int i = 0; i < getCurrentSize(); i++)
     {
          cout << items[i] << " ";
     }
}
// getIndexOf method
template<class T>
int ArrayBag<T>::getIndexOf(const T& target) const
{
     bool found = false;
     int result = -1;
     int searchIndex = 0;

     while (!found && (searchIndex<itemCount))
     {
          if (items[searchIndex] == target)
          {
               found = true;
               result = searchIndex;
          }
          else
          {
               searchIndex++;
          }
     }
     return result;
}
// getFrequencyOf method
template<class T>
int ArrayBag<T>::getFrequencyOf(const T& anEntry) const
{
     int frequency = 0;
     int curIndex = 0;
     while (curIndex < itemCount)
     {
          if (items[curIndex] == anEntry)
          {
               frequency++;
          }
          curIndex++;
     }
     return frequency;
}
// Contains method
template<class T>
bool ArrayBag<T>::contains(const T& anEntry) const
{
     bool found = false;
     int curIndex = 0;
     while (!found && (curIndex < itemCount))
     {
          if (anEntry == items[curIndex])
          {
               found = true;
          }
          curIndex++;
     }
     return found;
}
// Remove method
template<class T>
bool ArrayBag<T>::remove(const T& anEntry)
{
     int locatedIndex = getIndexOf(anEntry);
     bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
     if (canRemoveItem)
     {
          itemCount--;
          items[locatedIndex] = items[itemCount];
     }
     return canRemoveItem;
}
// Clear method
template<class T>
void ArrayBag<T>::clear()
{
     itemCount = 0;
}
// Union method
template<class T>
ArrayBag<T> ArrayBag<T>::Union(const ArrayBag<T> rhs)
{
     ArrayBag<T> unionBag;
     for (int i = 0; i < getCurrentSize(); i++)
     {
          unionBag.add(items[i]);
     }
     for (int i = 0; i < rhs.getCurrentSize(); i++)
     {
          unionBag.add(rhs.items[i]);
     }
     cout << "The items in unionBag are: ";
     unionBag.displayItems();
     return unionBag;
}
// Intersection method
template<class T>
ArrayBag<T> ArrayBag<T>::Intersection(const ArrayBag<T> rhs)
{
     ArrayBag<T> interBag;
     for (int i = 0; i < getCurrentSize(); i++)
     {
          if (rhs.contains(items[i]))
               interBag.add(items[i]);
     }
     cout << "The items in interBag are: ";
     interBag.displayItems();
     return interBag;
}
// Difference method
template<class T>
ArrayBag<T> ArrayBag<T>::Difference(const ArrayBag<T> rhs)
{
     ArrayBag<T> diffBag;
     for (int i = 0; i < getCurrentSize(); i++)
     {
          if (!rhs.contains(items[i]))
               diffBag.add(items[i]);
     }
     cout << "The items in diffBag are: ";
     diffBag.displayItems();
     return diffBag;
}





int main()
{
     ArrayBag<int> intBag1;
     ArrayBag<int> intBag2;
     for (int i = 0; i < 3; i++)
     {
          intBag1.add(i);
          intBag2.add(i + 2);
     }
     cout << "The items in bag 1 are: ";
     intBag1.displayItems();
     cout << endl << "The items in bag 2 are: ";
     intBag2.displayItems();
     cout << endl;
     intBag1.Union(intBag2);
     cout << endl;
     intBag1.Intersection(intBag2);
     cout << endl;
     intBag1.Difference(intBag2);
     cout << endl;
     return 0;
}

