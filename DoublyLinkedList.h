#include <iostream>
#incldue "ListNode.h"

using namespace std;

template <class T>
class DoublyLinkedList
{
private:

public:
  unsigned int size;
  ListNode<T> *front;
  ListNode<T> *back;

  DoublyLinkedList();//Constructor
  ~DoublyLinkedList();//Destructor

  void insertBack(T data);
  T removeFront();
  T getFront();

  void printList();
  int deletePos(int pos);

  bool isEmpty();
  unsigned int getSize();
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
  size = 0;
  front = NULL;
  back = NULL;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{

}

template <class T>
void DoublyLinkedList<T>::insertBack(T d)
{
  ListNode<T> *node = new ListNode<T>(d);

  if(size == 0) //empty list
  {
    front = node;
  }
  else //not empty
  {
    back->next = node;
    node->prev = back;
  }
  back = node;
  ++size;
}

template <class T>
T DoublyLinkedList<T>::removeFront()
{
  if(!isEmpty())
  {
    ListNode<T> *node = front;
    if(front->next == NULL) //only node in list
    {
      front = NULL;
      back = NULL;
    }
    else //more than one node
    {
      front->next->prev = NULL;
      front = front->next;
    }
    T temp = node->data;

    delete node;
    --size;
    return temp;
  }
  else
  {
    return T();
  }
}

template <class T>
T DoublyLinkedList<T>::getFront()
{
  return front->data;
}

template <class T>
void DoublyLinkedList<T>::printList()
{
  ListNode<T> *curr = front;

  while(true)
  {
    if(curr->next == NULL)
    {
      break;
    }

    cout << curr->data << endl;
    curr = curr->next;
  }
}

template <class T>
void DoublyLinkedList<T>::deletePos(int pos)
{
  int index = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;

  while(index != pos)
  {
    prev = curr;
    curr = curr->next;
    ++index;
  }
  prev->next = curr->next; //stuff to be deleted
  curr->next->prev = prev;
  curr->next = NULL;
  curr->prev = NULL;
  curr->data = NULL;

  --size;
  delete curr;
}

template <class T>
bool DoublyLinkedList<T>::isEmpty()
{
  return(size == 0);
}

template <class T>
unsigned int DoublyLinkedList<T>::getSize()
{
  return size;
}
