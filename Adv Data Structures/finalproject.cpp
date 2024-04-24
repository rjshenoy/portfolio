#include <iostream>
using namespace std;
#include <vector>


class Linked_List {

private:
    
    struct Node {
        int data;
        Node *next;
    };
    Node* head = NULL;
    int size;
    Node *prevHead = NULL;


    
    
    void addNode(int new_data) {
        Node* current = head;
        Node* node = (Node*) malloc(sizeof(Node));
        node->data = new_data;
        node->next = NULL;
    
        // special case for length 0
        if (current == NULL) {
            this->head = node;
        }
        else {
            // locate the last node
            while (current->next != NULL) {
                current = current->next;
            }
    
            current->next = node;
            
        }


    }

public:
    
    Linked_List() {

        

    }

    
    Linked_List(int data[], int size) {

        for (int i = 0; i < size; i++) {

            addNode(data[i]);

        }

    }

    void deleteNode(int key) {
        Node* temp = head;
        Node* prev = NULL;
        if (temp != NULL && temp->data == key) {
            head = temp->next;
            delete(temp);
            return;
        }
        while (temp != NULL && temp->data != key) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) return;
        prev->next = temp->next;
        delete(temp);
    }

    void print() {
        Node* ptr;
        ptr = head;

    if (ptr == NULL) {
        cout << "List is empty" << endl;
    }

        while (ptr != NULL) {
            cout<< ptr->data << " ";
            ptr = ptr->next;
        }
    }

    void addPrevList(Node* prev) {

        this->prevHead = prev;

    }

    Linked_List add(int data,int index) {

        Linked_List new_list = Linked_List();
        Node* temp = (Node*) malloc(sizeof(Node));
        temp = head;
        int currentIndex = 0;

        if (index == 0) {

           
            Node* temp2 = (Node*) malloc(sizeof(Node));
            temp2->data = data;
            temp2->next = NULL;
            new_list.head = temp2;
            new_list.head->next = this->head;
            new_list.addPrevList(this->head);
            return new_list;
                         

        }
        
        while (temp != NULL && currentIndex != index-1) {
            new_list.addNode(temp->data);
            temp = temp->next;
            currentIndex++;
        }

        Node* newTemp = (Node*) malloc(sizeof(Node));
        newTemp->data = temp->data;
        newTemp->next = temp->next;
        
        Node* newNode = (Node*) malloc(sizeof(Node));
        
        newNode->data = data;
        newNode->next = newTemp->next;
        newTemp->next = newNode;

        while (newTemp != NULL) {
            new_list.addNode(newTemp->data);
            newTemp = newTemp->next;
        }

        // new_list.print();
        new_list.addPrevList(this->head);
        return new_list;
        
        

        

    }

    

    Node* getHead() {
        return head;
    }

    
    Linked_List getPrevList() {

        Linked_List x = Linked_List();
        Node* temp = (Node*) malloc(sizeof(Node));
        temp = prevHead;
        while (temp != NULL) {
            x.addNode(temp->data);
            temp = temp->next;
        }
        return x;
    }
        


};

int main() {


    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    Linked_List list = Linked_List(arr,10);
    list.print();
    Linked_List list2 = list.add(0,7);
    cout << endl;
    list2.print();

    
    
    
    
    
    
}