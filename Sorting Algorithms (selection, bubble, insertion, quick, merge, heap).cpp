// Colton Clark
// Student ID: 004352008
// Clark326@cougars.csusm.edu

#include <iostream>
using namespace std;

void displayArray(int array[], int size);
void selectionSort(int array[], int size);
void bubbleSort(int array[], int size);
void insertionSort(int array[], int size);
void quickSort(int array[], int p, int r);
void mergeSort(int array[], int p, int r);
void heapSort(int array[], int size);

int main()
{
    cout << "\nInput size of array: ";

    int array[100];
    int size = sizeof(array) / sizeof(int);

    cin >> size;
    cout << "\nProvide " << size << " integers, each separated by a space. \n" << endl;

    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }

    cout << "The unsorted values are: \n";
    displayArray(array, size); cout << endl;

    cout << "Which sorting algorithm would you like to use?" << endl << "1: Selection Sort \n2: Bubble Sort\n3: Insertion Sort\n4: Quick Sort\n5: Merge Sort\n6: Heap Sort\n\n";
    int choice = 0;
    cout << "Algorithm: ";
    cin >> choice;
    switch (choice)
    {
    case 1: cout << "You chose Selection Sort\n";
       selectionSort(array, size); break;

    case 2: cout << "You chose Bubble Sort\n";
       bubbleSort(array, size); break;

    case 3: cout << "You chose Insertion Sort\n";
       insertionSort(array, size); break;

    case 4: cout << "You chose Quick Sort\n";
       quickSort(array, 0, size - 1); break;

    case 5: cout << "You chose Merge Sort\n";
       mergeSort(array, 0, size - 1); break;

    case 6: cout << "You chose Heap Sort\n";
        heapSort(array, size); break;

    default: cout << "Invalid entry"; break;
    }

    cout << "The sorted values are: \n";
    displayArray(array, size);
}

void displayArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}

void selectionSort(int array[], int size)
{

    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (array[j] < array[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            swap(array[i], array[min]);
        }
    }
}

void bubbleSort(int array[], int size)
{
    int index;
    bool swap;
    do
    {
        swap = false;
        for (int i = 0; i < size - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                index = array[i];
                array[i] = array[i + 1];
                array[i + 1] = index;
                swap = true;
            }
        }
    } while (swap);
}

void insertionSort(int array[], int size)
{
    int value, index;
    for (int i = 1; i < size; i++)
    {
        value = array[i];
        index = i;
        while (index > 0 && array[index - 1] > value)
        {
            array[index] = array[index - 1];
            index = index - 1;
        }
        array[index] = value;
    }
}

int partition(int array[], int p, int r)
{

    int pivot = array[p];
    int index = 0;
    
    for (int i = p + 1; i <= r; i++) {
        if (array[i] <= pivot)
            index++;
    }

    int pivotIndex = p + index;
    swap(array[pivotIndex], array[p]);

    int i = p, j = r;

    while (i < pivotIndex && j > pivotIndex) {

        while (array[i] <= pivot) {
            i++;
        }

        while (array[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(array[i++], array[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(int array[], int p, int r)
{

    if (p >= r)
        return;

    int par = partition(array, p, r);

    quickSort(array, p, par - 1);

    quickSort(array, par + 1, r);
}


void merge(int array[], int p, int q, int r)
{
    int size1 = q - p + 1;
    int size2 = r - q;
    int* A = new int[size1];
    int* B = new int[size2];

    for (int i = 0; i < size1; i++)

        A[i] = array[p + i];

    for (int j = 0; j < size2; j++)
        B[j] = array[q + 1 + j];

    int i = 0;
    int j = 0;
    int k = p;
    while ((i < size1) && (j < size2))
    {
        if (A[i] <= B[j])
        {
            array[k] = A[i];
            i++;
        }
        else
        {
            array[k] = B[j];
            j++;
        }
        k++;
    }
    while (i < size1)
    {
        array[k] = A[i];
        i++;
        k++;
    }
    while (j < size2) {
        array[k] = B[j];
        j++;
        k++;
    }
}
void mergeSort(int array[], int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        mergeSort(array, p, q);
        mergeSort(array, q + 1, r);
        merge(array, p, q, r);
    }
}

class MaxHeap {

    int* arr;
    int capacity;
    int size;
    class Underflow {};
    class Overflow {};

public:

    MaxHeap(int cap) {
        size = 0; capacity = cap;
        arr = new int[capacity];
    }

    int parent(int i) {
        return (i - 1) / 2;
    }

    int left(int i) {
        return (2 * i + 1);
    }

    int right(int i) {
        return (2 * i + 2);
    }

    int getSize() {
        return size;
    }

    bool isLeaf(int i) {
        return (i < size / 2) ? false : true;
    }

    int getMax() {
        return arr[0];
    }
    void swap(int* a, int* b) {

        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void siftUp(int i) {

        while (i > 0 && arr[parent(i)] > arr[i]) {

            swap(&arr[i], &arr[parent(i)]);
            i = parent(i);
        }
    }

    void siftDown(int i) {

        while (!isLeaf(i)) {

            int l = left(i);
            int r = right(i);
            int larger = l;

            if (r < size)
                larger = (arr[l] > arr[r]) ? l : r;

            if (arr[i] >= arr[larger])
                break;

            swap(&arr[i], &arr[larger]);
            i = larger;
        }
    }

    void insert(int k) {

        if (size >= capacity)
            throw Overflow();

        int i = size;
        arr[i] = k;
        siftUp(i);
        size++;
    }

    int removeAt(int i) {

        if (i < 0 || size <= i)
            throw Underflow();

        if (size == 1)
            return arr[--size];

        int result = arr[i];
        arr[i] = arr[--size];

        if (arr[i] > result)
            siftDown(i);

        else
            siftUp(i);

        return result;
    }

    int extractMax() {
        if (size <= 0)
            throw Underflow();

        if (size == 1)
            return arr[--size];

        int result = arr[0];
        arr[0] = arr[--size];
        siftDown(0);

        return result;
    }

    void heapify(int* array, int len) {

        arr = array;
        capacity = size = len;

        int half = size / 2 - 1;

        for (int i = half; i >= 0; i--)
            siftDown(i);
    }
};

void heapSort(int A[], int len) {

    MaxHeap heap(len);
    heap.heapify(A, len);
    int i = len - 1;
    int count = 1;

    while (heap.getSize() > 0)
        A[i--] = heap.extractMax();
}
