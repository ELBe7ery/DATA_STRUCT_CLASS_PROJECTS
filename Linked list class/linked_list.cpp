#include "linked_list.h"
#include <iostream>
//----------------ctor------------------------------
template<typename userClass>
BlinkedList<userClass> ::BlinkedList() :start(0), end(0) {};
//---------------------------------------------------

//-----------------ctor------------------------------
template<typename userClass>
BlinkedList<userClass> ::BlinkedList(const userClass &userObj) :start(new node<userClass>(userObj)), end(start) {};
// wont matter if init. list is not used
//---------------------------------------------------

//----------------insert------------------------------
template<typename userClass>
void BlinkedList<userClass> ::insert (const userClass &userObj,int indx)
{
  int loc=0;
  node <userClass> *temp= new node<userClass>(userObj);
  node <userClass> *i=start;

  if(indx==0){
    pushFront(userObj);
    return;
  }
  while(i!=end)
  {

    if((++loc)==indx)
    {
      temp->nextNode=i->nextNode;
      i->nextNode=temp;
      return;
    }
    i=i->nextNode;
  }
  if(++loc==indx)
    pushBack(userObj);
};
//---------------------------------------------------

//----------------pushBack---------------------------
template<typename userClass>
void BlinkedList<userClass> ::pushBack(const userClass & userObj)
{
	node<userClass> *temp = new node<userClass>(userObj);         //Create a new node of the user object
	temp->nextNode = 0; 											                    //temp is a pointer to the new element which is to be last

	if (start == 0)                                               //empty ll
	{
		start = temp;
		end = temp;
	}
	else if (start == end) {                                      //one element ll
		start->nextNode = temp;
		end = temp;
	}

	else {
		end->nextNode = temp;										                    //set the nextNode pinter to null for the new added node
		end = temp;                                                 //The last end node is now set to point at the new created node
	}
};
//---------------------------------------------------

//------------------pushFront------------------------
template<typename userClass>
void BlinkedList<userClass> ::pushFront(const userClass & userObj)
{
	node<userClass> *temp = new node<userClass>(userObj);           //Create a new node of the user object
																	                                //temp is a pointer to the new element which is to be first
	temp->nextNode = start;                                         //the new created node points to the first old node
	start = temp;                                                   //the first node in the list is the node just created
};
//-----------------------------------------------

//----------------printAll-----------------------
template<typename userClass>
void BlinkedList<userClass> ::printAll()
{
	node<userClass> *i = start;
	std::cout << '[';
	while (1)
	{
		if (i != end) {
			std::cout << i->data << ", ";
			i = i->nextNode;
		}
		else {
			std::cout << i->data<< "] \n";
			return;
		}
	}
};
//-----------------------------------------------

//-----------------findNode----------------------
template<typename userClass>
node<userClass> * BlinkedList<userClass> ::findNode(const userClass &userObj)
{
	node<userClass> *i = start;
  if(i->data==userObj)
    return i;
	for (; i != end; i = i->nextNode)
		if (i->nextNode->data == userObj)
			return i;                                                     //returns a node pointer representing an element before
	return 0;                                                         //returns NULL in case object doesn't exist
};
//---------------------------------------------

//----------------find-------------------------
template<typename userClass>
bool BlinkedList<userClass> ::find(const userClass &userObj)
{
	if (findNode(userObj) != 0)
		return true;
	else
		return false;
};
//---------------------------------------------
//--------------removeItem---------------------
template<typename userClass>
void BlinkedList<userClass> ::removeItem(const userClass &userObj)
{
	node<userClass> * beforeRemove = findNode(userObj);
  node<userClass> * toRemove = beforeRemove->nextNode;

	if (beforeRemove == 0)
		return;
  else if(beforeRemove==start){
    start=beforeRemove->nextNode;
    delete beforeRemove;
  }
  else if(beforeRemove->nextNode==end){
    end=beforeRemove;
    delete beforeRemove->nextNode;
  }
	else{
    beforeRemove->nextNode = toRemove->nextNode;
	  delete toRemove;
}
};
//---------------------------------------------

//---------------clear-------------------------
template<typename userClass>
void BlinkedList<userClass> ::clear()
{
	node<userClass> *i = start;
	for (; i != end; i = i->next)
		delete i;
};
//---------------------------------------------
