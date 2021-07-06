//Sort a given set of large natural numbers using Shell Sort.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool cmp(string s1, string s2) {
    if (s1.size() > s2.size())
        return true;
    else if (s1.size() < s2.size())
        return false;
    else {
        for (int j = 0; j < s2.size(); j++) {
            if (s1[j] > s2[j])
               return true;            
            else if (s1[j] < s2[j])
                return false;
        }
    }  
}

void shellSort(string* arr, int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            string tmp = arr[i];
            int j=0;
            for (j = i; j >= gap && cmp(arr[j - gap], tmp); j -= gap)
                    arr[j] = arr[j - gap];              
            
            arr[j] = tmp;
        }
    }
}


int main()
{
    string str;
    ifstream file("input.txt");
    
    getline(file, str);
    int n = stoi(str), i = 0;//n - number elements of an input set
    
    string* tab = new string[n];

    while (getline(file, str))
         tab[i++] = str;    

    shellSort(tab, n);

    for (int i = 0; i < n; i++)
      cout << tab[i] << endl;
        
    delete [] tab;
    
    return 0;
}



