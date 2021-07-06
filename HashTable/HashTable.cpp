//Write a program tracking the amount of transferred money.
//Commands are given in the following format :
//+ from to amount - 'from' pays 'to' the specified amount
//? from to - display the amount transferred by from to to's account

#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <string>

#define TRANSACTION_AMOUNT 10000

struct Node {
	std::string from;
	std::string to;
	Node* nextTransaction;
	int amount;
};


int Hash(std::string from, std::string to)
{
	const char* from_c_str = from.c_str(); //string to  const char*
	const char* to_c_str = to.c_str();
	unsigned int hash = 13;
	int c;

	while (c = *from_c_str++)
		hash = ((hash << 5) + hash) + c;
	
	while (c = *to_c_str++)	
		hash = ((hash << 5) + hash) + c; 
	
	return hash % TRANSACTION_AMOUNT;
}

void AddTransaction(Node** hashTable, std::string from, std::string to, int amount) {

	int index = Hash(from, to);

	if (hashTable[index] == NULL)//first transaction in this cell
	{
		hashTable[index] = new Node;
		hashTable[index]->nextTransaction = NULL;
		hashTable[index]->amount = amount;
		hashTable[index]->from = from;
		hashTable[index]->to = to;
		return;
	}
	else if (hashTable[index]->nextTransaction == NULL
		&& hashTable[index]->from == from && hashTable[index]->to == to) {//one transction
		int temp = hashTable[index]->amount;
		temp += amount;
		hashTable[index]->amount = temp;
		return;
	}
	else {//multiple transacitons in one cell
		Node* ptr = hashTable[index];
		Node* newptr = new Node;
		newptr->amount = amount;
		newptr->from = from;
		newptr->to = to;
		newptr->nextTransaction = NULL;

		while (ptr->nextTransaction != NULL){
			if (ptr->from == from && ptr->to == to) {
				int temp =ptr->amount;
				temp += amount;
				ptr->amount = temp;
				return;
			}		
			ptr = ptr->nextTransaction;
		}

		if (ptr->from == from && ptr->to == to) {
			int temp = ptr->amount;
			temp += amount;
			ptr->amount = temp;
			return;
		}
		ptr->nextTransaction = newptr;
		return;
	}	
}

void PrintTransaction(Node ** hashTable, std::string from, std::string to){

	int index = Hash(from,to);

	if (hashTable[index] == NULL)
		std::cout << "0"<<std::endl;
	else if(hashTable[index] ->nextTransaction == NULL)//one transactoion
		std::cout << hashTable[index]->amount << std::endl; 
	else{//multiple transacitons
		Node* ptr = hashTable[index];
		
		while (ptr->nextTransaction != NULL) {
			if (ptr->from == from && ptr->to == to) {
				std::cout << ptr->amount << std::endl;
				return;
			}
			ptr = ptr->nextTransaction;
		}

		if (ptr->from == from && ptr->to == to) {
			std::cout << ptr->amount << std::endl;
			return;
		}
	}		
}



int main(int argc, char** argv)
{
	Node* hashTable[TRANSACTION_AMOUNT];
	for (int i = 0; i < TRANSACTION_AMOUNT; i++)
		hashTable[i] = NULL;
	
	char  input;
	char from[20], to[20];
	int amount;

	FILE* file;
	file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("Input reading has faied\n");
		return 1;
	}

	while (fscanf(file, "%c", &input) == 1) {
		switch (input)
		{
		case'+':
			fscanf(file, "%s %s %d", from, to, &amount);
			AddTransaction(hashTable, from, to, amount);
			break;
		case'?'://track the sum of transfers and display the 
				//amount transferred by from to to's account
			fscanf(file, "%s %s", from, to);
			PrintTransaction(hashTable, from, to);
			break;
		default:
			break;
		}
	}
	
	for (int i = 0; i < TRANSACTION_AMOUNT; i++)
		delete hashTable[i];

	return 0;
}