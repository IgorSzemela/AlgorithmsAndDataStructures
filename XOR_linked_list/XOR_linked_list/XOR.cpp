//The task is based on implement a bidirectional list. A classic bidirectional list stores
//successor and predecessor addresses in nodes, in our task the list stores only xor of 
//these addresses in nodes. This saves approximately 50% of memory used by the list structure.

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Node {
public:
    int value;
    Node* npx;
};

Node* XOR(Node* n1, Node* n2) {
    return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(n1) ^ reinterpret_cast<uintptr_t>(n2));
}

// adding an element's 'value'  to the beginning of the list
void ADD_BEG(Node** head_ref, Node** tail_ref, Node** actual_ref, int value, Node** prev_ref, Node** next_ref) {
    Node* temp_node = new Node();
    temp_node->value = value;
    temp_node->npx = *head_ref;

    if (*head_ref != NULL)
    {
        if ((*actual_ref)->npx == NULL)//only one element
            *prev_ref = XOR(temp_node, (*head_ref)->npx);
        else if ((*actual_ref)->npx == *next_ref)//list has actual and successor
            *prev_ref = temp_node;

        (*head_ref)->npx = XOR(temp_node, (*head_ref)->npx);
    }
    else {
        *actual_ref = temp_node;
        *tail_ref = temp_node;
    }
    *head_ref = temp_node;
}

// adding an element's 'value'  to the end of the list
void ADD_END(Node** head_ref, Node** tail_ref, Node** actual_ref, int value, Node** prev_ref, Node** next_ref) {
    Node* temp_node = new Node();
    temp_node->value = value;
    temp_node->npx = *tail_ref;

    if (*head_ref != NULL)
    {
        if ((*actual_ref)->npx == NULL)//only one element
            *next_ref = XOR((*tail_ref)->npx, temp_node);
        else if ((*actual_ref)->npx == *prev_ref)//list has actual and predecessor 
            *next_ref = temp_node;

        (*tail_ref)->npx = XOR((*tail_ref)->npx, temp_node);
    }
    else {
        *actual_ref = temp_node;
        *head_ref = temp_node;
    }
    *tail_ref = temp_node;
}

// prints the contents of the list from the first to the last element
void PRINT_FORWARD(Node* head_ref) {
    Node* curr = head_ref, * prev = NULL, * next = NULL;

    if (curr == NULL) {
        cout << "NULL" << endl;
    }
    else {
        while (curr != NULL)
        {
            cout << curr->value << " ";

            next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
        }
        cout << endl;
    }
}

//prints the contents of the list from the last to the first element
void PRINT_BACKWARD(Node* tail) {
    Node* curr = tail, * prev = NULL, * next;

    while (curr != NULL)
    {
        cout << curr->value << " ";

        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
    cout << endl;
}

//value of the currently pointed element
void ACTUAL(Node* actual_ref) {

    if (actual_ref != NULL)
        cout << actual_ref->value << endl;
    else
        cout << "NULL" << endl;
}

//prints the value of the ACTUAL's successor
void NEXT(Node** head_ref, Node** tail_ref, Node** actual_ref, Node** prev_ref, Node** next_ref) {

    if (*actual_ref != NULL)
    {
        if (*actual_ref == *tail_ref) {
            *prev_ref = *actual_ref;
            *actual_ref = *head_ref;
            *next_ref = XOR((*head_ref)->npx, NULL);
        }
        else {
            *prev_ref = *actual_ref;
            *actual_ref = *next_ref;
            *next_ref = XOR((*next_ref)->npx, *prev_ref);

            if (*next_ref == NULL)
                *next_ref = *head_ref;
        }
        cout << (*actual_ref)->value << endl;
    }
    else cout << "NULL" << endl;
}

//prints the value of the ACTUAL's predecessor 
void PREV(Node** head_ref, Node** tail_ref, Node** actual_ref, Node** prev_ref, Node** next_ref) {

    if (*actual_ref != NULL)
    {
        if (*actual_ref == *head_ref) {
            *next_ref = *head_ref;
            *actual_ref = *tail_ref;
            *prev_ref = XOR((*tail_ref)->npx, NULL);
        }
        else {
            *next_ref = *actual_ref;
            *actual_ref = *prev_ref;
            *prev_ref = XOR((*actual_ref)->npx, *next_ref);

            if (*prev_ref == NULL)
                *prev_ref = *tail_ref;
        }
        cout << (*actual_ref)->value << endl;
    }
    else cout << "NULL" << endl;
}

//removes the first node from the list
void DEL_BEG(Node** head_ref, Node** tail_ref, Node** actual_ref, Node** prev_ref, Node** next_ref) {
    Node* temp_node = *head_ref;
    if (*actual_ref != NULL) {

        *head_ref = XOR((*head_ref)->npx, NULL);
        if (*head_ref != NULL)
            (*head_ref)->npx = XOR(NULL, XOR(temp_node, (*head_ref)->npx));

        if (*head_ref == NULL) {//if last element was deleted and list is empty
            *tail_ref = NULL;
            *actual_ref = NULL;
            *prev_ref = NULL;
            *next_ref = NULL;
        }
    }
}

//removes the last node from the list
void DEL_END(Node** head_ref, Node** tail_ref, Node** actual_ref, Node** prev_ref, Node** next_ref) {
    Node* temp_node = *tail_ref;
    if (*actual_ref != NULL) {

        *tail_ref = XOR((*tail_ref)->npx, NULL);
        if (*tail_ref != NULL)
            (*tail_ref)->npx = XOR(NULL, XOR(temp_node, (*tail_ref)->npx));

        if (*tail_ref == NULL) {
            *head_ref = NULL;
            *actual_ref = NULL;
            *prev_ref = NULL;
            *next_ref = NULL;
        }
    }
}

//adding an element's 'value' as a predecessor of the currently selected element (ACTUAL).
void ADD_ACT(Node** head_ref, Node** tail_ref, Node** actual_ref, int value, Node** prev_ref, Node** next_ref) {

    Node* new_node = new Node();
    new_node->value = value;

    if ((*actual_ref) != NULL)
    {
        if (*head_ref == *actual_ref) {//adding at the beggining
            ADD_BEG(head_ref, tail_ref, actual_ref, value, prev_ref, next_ref);
        }
        else {//adding in the middle
            new_node->npx = XOR(*prev_ref, *actual_ref);
            (*prev_ref)->npx = XOR(new_node, XOR((*prev_ref)->npx, *actual_ref));
            (*actual_ref)->npx = XOR(new_node, XOR((*actual_ref)->npx, *prev_ref));
        }
    }
    else {//adding first element to the list
        *actual_ref = new_node;
        *head_ref = new_node;
        *tail_ref = new_node;
    }
}

//removes from the list the node that ACTUAL points to
void DEL_ACT(Node** head_ref, Node** tail_ref, Node** actual_ref, Node** prev_ref, Node** next_ref) {
    Node* delete_node = *actual_ref;

    if ((*actual_ref) != NULL) {
        if (*actual_ref == *head_ref) {//actual is head
            *actual_ref = *tail_ref;
            *head_ref = *next_ref;
            *prev_ref = *next_ref;
            (*next_ref)->npx = XOR((*next_ref)->npx, delete_node);

            if (*head_ref == *tail_ref) {
                *head_ref = NULL;
                *actual_ref = NULL;
                *prev_ref = NULL;
                *next_ref = NULL;
                *tail_ref = NULL;
            }
        }
        else {//actual has prev
            (*prev_ref)->npx = XOR((*prev_ref)->npx, XOR(*next_ref, delete_node));

            if (*prev_ref == (*prev_ref)->npx)
                *next_ref = *tail_ref = *prev_ref;
            else
                (*next_ref)->npx = XOR((*next_ref)->npx, XOR(*prev_ref, delete_node));

            *actual_ref = *prev_ref;
        }
    }
}

//removes from the list all nodes whose value is equal to N.
void DEL_VAL(Node** head_ref, Node** tail_ref, Node** actual_ref, int N, Node** prev_ref, Node** next_ref) {
    Node* curr = *head_ref, * prev = NULL, * next = *head_ref;
    next = XOR(prev, next->npx);

    while (curr != NULL) {
        if (curr == *head_ref && curr->value == N) {//curr is head_ref

            *head_ref = XOR((*head_ref)->npx, NULL);
            if (*head_ref != NULL)
                (*head_ref)->npx = XOR(NULL, XOR(curr, (*head_ref)->npx));

            curr = next;
            next = XOR(prev, next->npx);
        }
        else if (curr->value == N && curr == *tail_ref) { //curr is tail

            *next_ref = *head_ref;
            (*actual_ref)->npx = XOR((*actual_ref)->npx, *tail_ref);
            *tail_ref = *actual_ref;
            prev = curr;
            curr = next;
        }
        else if (curr->value == N) {//curr has prev

            if (*actual_ref == *tail_ref) {//curr has neighbours      
                (*actual_ref)->npx = XOR((*actual_ref)->npx, XOR(curr, prev));
                (*next_ref)->npx = XOR((*next_ref)->npx, XOR(*prev_ref, *actual_ref));
                (*prev_ref) = *next_ref;

                *tail_ref = *actual_ref;
                *head_ref = *next_ref;

                break;
            }
            else {
                (*actual_ref)->npx = XOR((*actual_ref)->npx, XOR(curr, prev));
                (*head_ref)->npx = XOR((*head_ref)->npx, XOR(curr, next));
                (*prev_ref) = *head_ref;

                break;
            }

        }
        else {//incrementing through list
            prev = curr;
            curr = next;
            next = XOR(prev, next->npx);
        }
    }
}

int main()
{
    string str, str_substr;
    int N;
    Node* head = NULL, * tail = NULL, * actual = NULL, * prev = NULL, * next = NULL;

    ifstream file("input.txt");
    while (!file.eof()) {
        getline(file, str);

        str_substr = str.substr(0, 7);

        if (str_substr == "ADD_BEG" || str_substr == "ADD_END" || str_substr == "ADD_ACT" || str_substr == "DEL_VAL") {
            N = stoi(str.substr(8, str.length() - 8));

            if (str_substr == "ADD_BEG") {
                ADD_BEG(&head, &tail, &actual, N, &prev, &next);
            }
            else if (str_substr == "ADD_END") {
                ADD_END(&head, &tail, &actual, N, &prev, &next);
            }
            else if (str_substr == "ADD_ACT") {
                ADD_ACT(&head, &tail, &actual, N, &prev, &next);
            }
            else if (str_substr == "DEL_VAL") {
                DEL_VAL(&head, &tail, &actual, N, &prev, &next);
            }
        }
        else {
            if (str == "PRINT_FORWARD") {
                PRINT_FORWARD(head);
            }
            else if (str == "PRINT_BACKWARD") {
                PRINT_BACKWARD(tail);
            }
            else if (str_substr == "ACTUAL") {
                ACTUAL(actual);
            }
            else if (str_substr == "NEXT") {
                NEXT(&head, &tail, &actual, &prev, &next);
            }
            else if (str_substr == "PREV") {
                PREV(&head, &tail, &actual, &prev, &next);
            }
            else if (str_substr == "DEL_BEG") {
                DEL_BEG(&head, &tail, &actual, &prev, &next);
            }
            else if (str_substr == "DEL_END") {
                DEL_END(&head, &tail, &actual, &prev, &next);
            }
            else if (str_substr == "DEL_ACT") {
                DEL_ACT(&head, &tail, &actual, &prev, &next);
            }
        }
    }

    delete head, tail, actual, prev, next;

    return (0);
}