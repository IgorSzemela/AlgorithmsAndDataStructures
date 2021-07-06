//Using vector implement a max, min heap  and the following operations: 
//addding, removal, printing into console, changing orientation of the heap

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int Left(int i) {
	return 2 * i + 1;
}


int Right(int i) {
	return 2 * i + 2;
}


void Heapify(vector < int >& v, int i, int size, int ifMax)
{
	int l = Left(i);
	int r = Right(i);
	int maxps = 0;

	if (ifMax) {//descending order
		if (l < size && v[l] > v[i])
			maxps = l;
		else
			maxps = i;

		if (r < size && v[r] > v[maxps])
			maxps = r;

		if (maxps != i) {
			swap(v[i], v[maxps]);

			Heapify(v, maxps, size, ifMax);
		}
	}
	else {//ascending order
		if (l < size && v[l] < v[i])
			maxps = l;
		else
			maxps = i;

		if (r < size && v[r] < v[maxps])
			maxps = r;

		if (maxps != i) {
			swap(v[i], v[maxps]);

			Heapify(v, maxps, size, ifMax);
		}
	}	
}


void Remove(vector < int >& v, int ifMax)
{
	cout << v[0] << endl;
	v[0] = v[v.size() - 1];
	v.pop_back();

	for (int i = 0; i <v.size(); i++) 
		Heapify(v, i, v.size(), ifMax);
}


void BuildHeap(vector < int >& v, int size, int ifMax)
{
	int lastNonLeaf = (size / 2) - 1;

	for (int i = lastNonLeaf; i >= 0; i--)
		Heapify(v, i, size, ifMax);
}


void ChangeOrder(vector < int >& v, int size, int& ifMax) {
	if (ifMax) {
		ifMax = 0;
		BuildHeap(v, size, ifMax);
	}
	else {
		ifMax = 1;
		BuildHeap(v, size, ifMax);
	}
}


int main()
{
	int num = 0, ifMax = 1, n = 0;
	char input;
	vector <int> v;

	FILE* file;
	file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("Input reading has faied\n");
		return 1;
	}

	while (fscanf(file, "%c", &input) == 1) {
		switch (input) {
		case '+'://add a 'num' to the heap
			fscanf(file, " %d", &num);
			v.push_back(num);

			BuildHeap(v, v.size(), ifMax);	
			break;
		case '-'://remove the maximum from the max heap (minimum from the min heap respectively)
			Remove(v, ifMax);
			break;
		case 'p'://write all elements of the heap in the order in which they are stored in an vector
			for (int i = 0; i < v.size(); i++)
				printf("%d ", v[i]);
			cout << endl;
			break;
		case 'r': 
			fscanf(file, " %d", &num);
			n = num;
			while (!v.empty())//remove all elements from the heap
				v.pop_back();

			for (int i = 0; i < n; i++) {//create a heap out of n new elements
				fscanf(file, " %d", &num);
				v.push_back(num);
			}
			BuildHeap(v, v.size(), ifMax);
			break;
		case 's':
			ChangeOrder(v, v.size(), ifMax);//change the orientation of the heap – from max to min
			break;							//and from min to max respectively
		case 'q'://exit the program
			return 0;
			break;
		}
	}

	return 0;
}