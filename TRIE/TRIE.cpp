//Implement a TRIE tree which contains translations of words. 

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

#define ALPHABET 26
using namespace std;

struct Node {
	struct Node* child[ALPHABET];
	string polishFullTrans;
	char singleLetter;
	bool isLeaf = false;
};

struct Node* addNewNode()
{
	struct Node* newNode = new Node;
	newNode->isLeaf = false;

	for (int i = 0; i < ALPHABET; i++)
		newNode->child[i] = NULL;

	return newNode;
}

void search(struct Node* root, string eng)
{
	struct Node* traversalNode = root;

	for (int i = 0; i < eng.length(); i++)
	{
		if (traversalNode->child[eng[i] - 'a'] == NULL) {
			cout << "-" << endl;
			return;
		}
			
		traversalNode = traversalNode->child[eng[i] - 'a'];
	}

	if (traversalNode != NULL && traversalNode->isLeaf)
		cout << traversalNode->polishFullTrans << endl;
	else {
		cout << "-" << endl;
		return;
	}
}

void prefixPrint(struct Node* intenralNode)
{
	struct Node* traversalNode = intenralNode;
	
	if (traversalNode->isLeaf)
		cout << traversalNode->polishFullTrans << endl;
	
	for (int i = 0; i < ALPHABET; i++)		
		if (traversalNode->child[i] != NULL)
			prefixPrint(traversalNode->child[i]);
}


void prefixSearch(struct Node* root, string eng)
{
	struct Node* traversalNode = root;

	for (int i = 0; i < eng.length(); i++)
	{
		if (traversalNode->child[eng[i] - 'a'] == NULL) {
			cout << "-" << endl;
			return;
		}
		traversalNode = traversalNode->child[eng[i] - 'a'];		
	}

	if (traversalNode != NULL) // && traversalNode->isLeaf
		prefixPrint(traversalNode);
	else {
		cout << "-" << endl;
		return;
	}
}

void add(struct Node* root, string eng, string pol)
{
	struct Node* traversalNode = root;

	for (int i = 0; i < eng.length(); i++)
	{
		if (traversalNode->child[eng[i] - 'a']==NULL)
			traversalNode->child[eng[i] - 'a'] = addNewNode();

		traversalNode = traversalNode->child[eng[i] -'a'];
	}
	traversalNode->polishFullTrans = pol;
	traversalNode->isLeaf = true;
}

int main(int argc, char** argv)
{
	char  input;
	char eng[20], pol[20];

	FILE* file;
	file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("Input reading has faied\n");
		return 1;
	}
	
	struct Node* root= addNewNode();

	while (fscanf(file, "%c", &input) == 1) {
		switch (input)
		{
		case'+'://add a word eng with the translation pol
			fscanf(file, "%s %s", eng, pol);
			add(root, eng, pol);
			break;
		case'?'://query about a word eng.Write a translation of eng 
				//or '-'  if it has not been added
			fscanf(file, "%s", eng);
			search(root, eng);
			break;
		case'*'://Write all words such that eng is a prefix of the word 
				//(including word eng)
			fscanf(file, "%s", eng);
			prefixSearch(root, eng);
			break;
		default:
			break;
		}
	}

	return 0;
}
