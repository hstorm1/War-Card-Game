/** *********************************************************************
 * @file
 *
 * @brief has functions for the queue class to use for the card hands
 ***********************************************************************/

#pragma once
#include "thpef.h"

using namespace std;

/**
     * @brief linked list based queue for the deck of cards
     */

template <class TY>
class Queue
{
public:
    Queue();
    ~Queue();

    bool enque(TY item);
    bool deque(TY &item);
    bool front(TY &item);
    bool isEmpty();
    int size();
    void print();

private:
    struct node         /** Holds the card as well 
                    as the location for the next one */ 
    {
        TY myCard;      /**< The card stored in the list*/
        node* next;     /**< The address of the next node */
    };
    node* headptr;    /**< The address of the first node */
    node* tailptr;    /**< The address of the last node */
};

/** ***************************************************************************
 * @author David Hill
 *
 * @par Description
 * This function is the constructor and will initialize the linked list by
 * setting the headptr and tailptr to nullptr
 *
 *
 * @returns none
 *
 * @par Example
   @verbatim

   Queue<card> p1;
   // p1 is now initialized

   @endverbatim
 *****************************************************************************/

template <class TY>
Queue<TY>::Queue()
{
    headptr = nullptr;
    tailptr = nullptr;
}

/** ***************************************************************************
 * @author David Hill
 *
 * @par Description
 * This function is the destructor and will delete the linked list by walking
 * through it with a current and next node and deleting each one
 *
 *
 * @returns none
 *
 * @par Example
   @verbatim

   // if our class created an object that goes out of scope, then the
   // destructor would be called to free up the entire list

   @endverbatim
 *****************************************************************************/

template <class TY>
Queue<TY>::~Queue()
{
    node* current = headptr;
    node* next = nullptr;
    while (current != nullptr) // walk through the list
    {
        next = current->next; // change next and delete current
        delete current;
        current = next; // set current to next
    }
    headptr = nullptr;
    tailptr = nullptr;
}

/** ***************************************************************************
 * @author David Hill
 *
 * @par Description
 * This function adds an item to the end of the queue
 *
 * @param[in] item - the item name to add.
 *
 * @returns a boolean value for if the item was added or not
 *
 * @par Example
 * @verbatim

    Queue<int> q;
    q.enque(1);
    q.enque(4);
    // q now contains 1 and 4

   @endverbatim
 *****************************************************************************/

template <class TY>
bool Queue<TY>::enque(TY item)
{
    node* temp = new (nothrow) node;

    // check if memory can be allocated
    if (temp == nullptr)
    {
        return false;
    }
    temp->myCard = item;
    
    // empty list insertion
    if (isEmpty() == true)
    {
        temp->next = nullptr;
        headptr = temp;
        tailptr = temp;
        return true;
    }
    // size 1 list insertion
    if (size() == 1)
    {
        headptr->next = temp;
        tailptr = temp;
    }
    // every other insertion
    tailptr->next = temp;
    tailptr = temp;
    tailptr->next = nullptr;
    return true;
}

/** ***************************************************************************
 * @author David Hill
 *
 * @par Description
 * This function removes the first item from the queue and stores that in
 * the parameter "item"
 *
 *  * @param[in] item - the item name to remove and be stored into
 *
 * @returns a boolean value for if the item was removed or not
 *
 * @par Example
 * @verbatim

    Queue<int> q;
    int item;
    q.enque(1);
    q.enque(4);
    q.deque(item);
    // item now is equal to 1

   @endverbatim
 *****************************************************************************/

template <class TY>
bool Queue<TY>::deque(TY& item)
{
    if (isEmpty())
    {
        return false;
    }
    // set headptr to whatever is after it
    // and set the item parameter to the card value
    node* temp = headptr;
    headptr = headptr->next;
    item = temp->myCard;
    delete temp;
    return true;
}

/** ***************************************************************************
 * @author David Hill
 *
 * @par Description
 * This function looks at the first item and stores it in the parameter "item"
 * but does not remove it.
 *
 *  * @param[in] item - the item name to be stored into.
 *
 * @returns a boolean value for if an item was at the front or not
 *
 * @par Example
 * @verbatim

    Queue<int> q;
    int item;
    q.enque(1);
    q.enque(4);
    q.front(item);
    // item now is equal to 1, but 1 was not removed

   @endverbatim
 *****************************************************************************/

template <class TY>
bool Queue<TY>::front(TY& item)
{
    if (isEmpty())
    {
        return false;
    }
    // set the item parameter to the card value
    item = headptr->myCard;
    return true;
}

/** ***************************************************************************
 * @author David Hill
 *
 * @par Description
 * This function checks if the queue is empty or not
 *
 *
 * @returns a boolean value for if the queue is empty or not
 *
 * @par Example
 * @verbatim

    Queue<int> q;
    bool b = q.isEmpty();
    // b is equal to true

   @endverbatim
 *****************************************************************************/

template <class TY>
bool Queue<TY>::isEmpty()
{
    return headptr == nullptr;
}

/** ***************************************************************************
 * @author David Hill
 *
 * @par Description
 * This function returns the size of the queue
 *
 *
 * @returns an integer value for the size of the queue
 *
 * @par Example
 * @verbatim

    Queue<int> q;
    int size;
    q.enque(1);
    q.enque(4);
    size = q.size()
    // size now is equal to 2

   @endverbatim
 *****************************************************************************/

template <class TY>
int Queue<TY>::size()
{
    int size = 0;
    node* temp = headptr;
    // increment our size variable as we walk through the list
    while (temp != nullptr)
    {
        size += 1;
        temp = temp->next;
    }
    return size;
}

/** ***************************************************************************
 * @author David Hill
 *
 * @par Description
 * This function prints out the queue in the form of the face value and then
 * the suit
 *
 *
 * @par Example
 * @verbatim

    Queue<int> q;
    q.enque(1);
    q.enque(25);
    q.print();
    // the output would be "2H KD"

   @endverbatim
 *****************************************************************************/

template <class TY>
void Queue<TY>::print()
{
    node* temp = headptr;
    // print out specific face values or 1 + the value
    // and then the suit
    while (temp != nullptr)
    {
        if (temp->myCard.faceValue == 0)
        {
            cout << "A";
        }
        else if (temp->myCard.faceValue == 10)
        {
            cout << "J";
        }
        else if (temp->myCard.faceValue == 11)
        {
            cout << "Q";
        }
        else if (temp->myCard.faceValue == 12)
        {
            cout << "K";
        }
        else
        {
            cout << temp->myCard.faceValue + 1;
        }
        if (temp->myCard.suit == 0)
        {
            cout << "H ";
        }
        else if (temp->myCard.suit == 1)
        {
            cout << "D ";
        }
        else if (temp->myCard.suit == 2)
        {
            cout << "C ";
        }
        else if (temp->myCard.suit == 3)
        {
            cout << "S ";
        }
        temp = temp->next;
    }
}