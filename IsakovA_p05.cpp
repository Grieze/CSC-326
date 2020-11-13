/*PROGRAM COMMENTS
This program uses 5 different sorting algorithms and attempts to measure their performance by measuring how fast they can finish executing given n ammount of random ints or double valeus*/

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
// Need Bubble, Selection, Insert, Merge, Quick
/// SELECTION SORT BEGIN ///////////////////////////////////////////////////////////
template <class T>
int findIndexofLargest(const T theArray[], int size)
{
	int indexsoFar = 0;
	for (int currentIndex = 1; currentIndex < size; currentIndex++)
	{
		if (theArray[currentIndex] > theArray[indexsoFar])
		{
			indexsoFar = currentIndex;
		}
	}
	return indexsoFar;
}
template <class T>
void selectionSort(T theArray[], int n)
{
	for (int last = n-1; last >= 1 ; last--)
	{
		int largest = findIndexofLargest(theArray, last + 1);
		swap(theArray[largest], theArray[last]);
	}
}
/// SELECTION SORT END /////////////////////////////////////////////////////////////

/// BUBBLE SORT BEGIN //////////////////////////////////////////////////////////////
template <class T>
void bubbleSort(T theArray[], int n)
{
	bool sorted = false;
	int pass = 1;
	while (!sorted &&(pass < n))
	{
		sorted = true;
		for (int index = 0; index < n - pass; index++)
		{
			int nextIndex = index + 1;
			if (theArray[index] > theArray[nextIndex])
			{
				swap(theArray[index], theArray[nextIndex]);
				sorted = false;
			}
		}
		pass++;
	}
}
/// BUBBLE SORT END ////////////////////////////////////////////////////////////////

/// INSERTION SORT BEGIN ///////////////////////////////////////////////////////////
template <class T>
void insertionSort(T theArray[], int n)
{
	for (int unsorted = 1; unsorted < n; unsorted++)
	{
		T nextItem = theArray[unsorted];
		int loc = unsorted;
		while ((loc>0) && (theArray[loc-1]>nextItem))
		{
			theArray[loc] = theArray[loc - 1];
			loc--;
		}
		theArray[loc] = nextItem;
	}
}
/// INSERTION SORT END /////////////////////////////////////////////////////////////

/// MERGE SORT BEGIN ///////////////////////////////////////////////////////////////
//const int MAX_SIZE = 500050;
template <class T>
void merge(T theArray[], int first, int mid, int last) 
{
	T* tempArray = new T[1000001];  
	int first1 = first; 
	int last1  = mid;
	int first2 = mid + 1;
	int last2  = last; 
	int index = first1; 
	while ((first1 <= last1) && (first2 <= last2))    
	{ 
		if (theArray[first1] <= theArray[first2])        
		{            
			tempArray[index] = theArray[first1];            
			first1++;        
		} 
		else       
		{            
			tempArray[index] = theArray[first2];
			first2++;        
		}  
		index++;    
	}
	while (first1 <= last1)    
	{ 
		tempArray[index] = theArray[first1];
		first1++;       
		index++;    
	}
	while (first2 <= last2)    
	{ 
		tempArray[index] = theArray[first2];        
		first2++;        
		index++;    
	}  
	for (index = first; index <= last; index++)        
		theArray[index] = tempArray[index]; 
	delete[] tempArray;
}
template <class T>
void mergeSort(T theArray[], int first, int last) {
	if (first < last) 
	{ 
		int mid = first + (last - first) / 2;
		mergeSort(theArray, first, mid);
		mergeSort(theArray, mid + 1, last); 
		merge(theArray, first, mid, last);    
	}
}
/// MERGE SORT END /////////////////////////////////////////////////////////////////

/// QUICK SORT BEGIN ///////////////////////////////////////////////////////////////
template <class T>
int partition(T theArray[], int start, int end)
{
	int pivot = theArray[end];
	//P-index indicates the pivot value index

	int P_index = start;
	int i, t; //t is temporary variable

	//Here we will check if array value is 
	//less than pivot
	//then we will place it at left side
	//by swapping 

	for (i = start; i < end; i++)
	{
		if (theArray[i] <= pivot)
		{
			t = theArray[i];
			theArray[i] = theArray[P_index];
			theArray[P_index] = t;
			P_index++;
		}
	}
	//Now exchanging value of
	//pivot and P-index
	t = theArray[end];
	theArray[end] = theArray[P_index];
	theArray[P_index] = t;

	//at last returning the pivot value index
	return P_index;
}
template <class T>
void Quicksort(T theArray[], int start, int end)
{
	if (start < end)
	{
		int P_index = partition(theArray, start, end);
		Quicksort(theArray, start, P_index - 1);
		Quicksort(theArray, P_index + 1, end);
	}
}
/// QUICK SORT END /////////////////////////////////////////////////////////////////

int randomInt(int n)
{
	return rand() % n + 1;
}

double randomDouble(int n)
{
	return (rand() % n + 1) / 1.1;
}

int main()
{
	srand(42);
	const int n = 100;
	int* intArr = new int[n];
	for (int i = 0; i < n; i++)
		intArr[i] = randomInt(n);
	auto start = high_resolution_clock::now();
	insertionSort(intArr, n);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << duration.count() <<" ms" << endl;
	return 0;
}
