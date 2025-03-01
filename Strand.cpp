#include "Strand.h"

Strand::Strand(){
    // Name: Strand() - Default Constructor
    // Desc: Used to build a new empty strand (m_head, m_tail = nullptr and size = 0)
    // Preconditions: None
    // Postconditions: Creates a new strand with a default name

    m_name = "";
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0; 
}

Strand::Strand(string name){
    // Name: Strand(string) - Overloaded Constructor
    // Desc: Used to build a new empty strand with the name passed
    //       with m_head, m_tail = nullptr; size = 0;
    // Preconditions: None
    // Postconditions: Creates a new strand with passed name

    m_name = name;
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}
  
Strand::~Strand(){
    // Name: ~Strand() - Destructor
    // Desc: Used to destruct a strand
    // Preconditions: There is an existing strand with at least one node
    // Postconditions: Strand is deallocated (including all dynamically allocated nodes)
    //                 to have no memory leaks!

    Node *curr = m_head; //node pointer will point to the first element in LL

    //create a while loop to iterate through LL
    while (curr != nullptr){
        m_head = curr;
        curr = curr->m_next; //move to the next node
        delete m_head; //deleting the previous node
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}
  
void Strand::InsertEnd(char data){
    // Name: InsertEnd
    // Desc: Takes in a char. Creates a new node.
    //       Inserts node at the end of the strand. Increases size.
    // Preconditions: Requires a strand
    // Postconditions: Strand is larger.

    //Build a new node for the last item 
    Node *newStrand = new Node(); //building a new strand node 
    newStrand->m_data = data; //setting the new node's data to passed char

    //The new node is going to be the last node, 
    //so m_next should point to the null pointer.
    newStrand->m_next = nullptr;

    //Step 3: Set a condition for when the linked list in empty
    if (m_head == nullptr){
        m_head = newStrand;
        m_tail = newStrand;
    }else{
        //address of m_tail should be set to the new node
        m_tail->m_next = newStrand;
        m_tail = newStrand; 
    }
    m_size++;
}
  
string Strand::GetName(){
    // Name: GetName()
    // Preconditions: Requires a strand
    // Postconditions: Returns m_name;

    return m_name;
}
  
int Strand::GetSize(){
    // Name: GetSize()
    // Preconditions: Requires a strand
    // Postconditions: Returns m_size;

    return m_size;
}
  
void Strand::ReverseSequence(){
    // Name: ReverseSequence
    // Preconditions: Reverses the strand
    // Postconditions: Strand sequence is reversed in place; nothing returned

    //Step 1: Create three node pointers
    Node *curr = m_head; //to begin traversing, curr will point to the first element in list
    Node *prev = nullptr; //points to the previous node
    Node *next = nullptr; //points to the next node

    //Step 2: Iterate and update pointer until end
    while (curr != nullptr){
        next = curr->m_next;
        curr->m_next = prev;
        //move pointers
        prev = curr;
        curr = next;
    }

    m_tail = m_head; //since list is reversed, m_tail should point to the first node
    m_head = prev; //now m_head points to the last node in the list
}
  
char Strand::GetData(int nodeNum){
    // Name: GetData
    // Desc: Returns the data at a specific location in the strand.
    //       Iterates to node and returns char.
    // Preconditions: Requires a DNA sequence
    // Postconditions: Returns a single char from a node

    int counter = 0; //will count the number of nodes during the traversal

    //Step 1: Create node pointer
    Node *temp = m_head; //starting at the begin of the LL

    //Step 2: Set a condition for when the linked list is empty
    if (m_head == nullptr){
        cout << "Linked List is empty" << endl;
        return ' ';
    }

    //Step 3: Create while loop to traverse through LL
    while (temp != nullptr){
        if (counter == nodeNum){
            return temp->m_data; //return char if true
        }
        else{
            temp = temp->m_next; //move onto the next node if false
            counter++; //increment by 1 as each node is identified
        }
    }
    return 0;
}
  
ostream &operator<< (ostream &output, Strand &myStrand){
    // Name: operator<<
    // Desc: Overloaded << operator to return ostream from strand
    //       Iterates over the entire strand and builds an output stream
    //       (Called like cout << *m_DNA.at(i); in Sequencer)
    // Preconditions: Requires a strand
    // Postconditions: Returns an output stream (does not cout the output)

    if (myStrand.GetSize() > 0){
        //create a node pointer
        Node *temp = myStrand.m_head;

        //create loop to go through each node
        while (temp != nullptr){
            output << temp->m_data << "->";
            temp = temp->m_next;
        }
        cout << "END" << endl;
    }else{
        output << "Empty strand." << endl;
        return output;
    }

    return output;
}
  
