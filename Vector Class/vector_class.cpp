#include "vector_class.h"

template <typename userClass>
bVector<userClass> ::  bVector (int initialSize) :size(initialSize),capacity(initialSize+INIT_SPARE_CAPACITY)
{
  objects=new userClass[capacity];                //Allocate memory space for an array of userClass of initialSize capacity
};

/*
 -When creating an object for the first time, set its objcets pointer to null
 -Then equate it with the obj2Cpy object
*/
template <typename userClass>
bVector<userClass> :: bVector (const bVector &obj2Cpy) :objects(0)
{
  operator=(obj2Cpy);
};

/*
  recreate the array with double sized capacity
*/
template <typename userClass>
void bVector<userClass> ::  resize(int newSize)
{
  if(newSize > capacity)
    reserve(newSize*2);
};

template <typename userClass>
void bVector<userClass> ::  reserve(int newCapacity)
{
  if(newCapacity<=capacity || newCapacity<size)
    return;
  userClass *oldObjectsPointer =objects;          //copy the old pointer
  capacity = newCapacity;                         //update object attribute
  objects = new userClass [newCapacity];          //re-allocate memory locations

  for (int i = 0; i < size; i++) {
    objects[i]=oldObjectsPointer[i];              //Copy the old elements into the new array

  delete [] oldObjectsPointer;                    //Delete the old objects pointer, we no longer need it
  }
};

template <typename userClass>
void bVector<userClass> :: pushBack(const userClass &pObj)
{
  if(size==capacity)
    reserve(capacity*2);
  objects[size++]=pObj;
};


template <typename userClass>
bVector<userClass>  &  bVector<userClass> :: operator= (const bVector &r)
{
  if(this==r)
    return *this;                             //de-reference the this pointer and return its value which is a bVector object

  size = r.size;                              //set the new size to the right hand side size
  capacity = r.capacity;                      //set the new capacity to the right hand side capacity
  delete [] objects;                          //Delete the old array of objects
  objects = new userClass [capacity];         //reallocate memory space to hold objects

  for (unsigned int i = 0; i < size; i++)
    objects[i]=r.objects[i];                  //Copy the old elements into the new array

  return *this;                               //de-reference the this pointer after being updated and return its value which is a bVector object
};


template <typename userClass>
userClass & bVector<userClass> :: operator[] (int indx)
{
  return objects[indx];
};


/*------------Notes-----------------------------
- When a function returns a reference, it returns an implicit pointer to its return value.
  This way, a function can be used on the left side of an assignment statement. For example, consider this simple program:


-----------------------------------------------*/


/*------------Things i dont know-----------------
- Why the operator= returns a ref not a copy? what is the diff? [Done]
= To support chaining x =(y=z); will set z to y, get the return of this operator [which is a reference of y] and call x.operator=(y)
= If it returns a copy, same result is achieved but
Also
- int x1=(xx=x);
  will call the operator= member function of xx {xx.operator=(x)} and the returned value of this function is an integer set to x1 !
  in case we want to support chain of equal operator (x=xx=xxx) which will be made in the following manner xx.operator=(xxx) and the returned value
  will be set to x.operator=(xx.operator=(xxx)). Its better if xx.operator=(xxx) returns a reference to the object instead of an entirly copy of it
  as long as the parameters of operator= are defined to be const. we wont change the returned value of xx.operator=(xxx) which is xx object !


- Why we need to declare the template {template <typename userClass>} every time we implement a function ?
-----------------------------------------------*/
