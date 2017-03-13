#ifndef VECTOR_CLASS_H
#define vector_class_h
#define INIT_SPARE_CAPACITY 32
template <typename userClass>
/*-----------------------------------
Function interface
-----------------------------------*/
class bVector {

  //All the class private attributes
  private:
    userClass *objects;                               //Pointer to an array of user defined object
    int size;                                         //The vector size [size++ when push back, size-- when pop back]. We cant use the [] operator for index >= size
    int capacity;                                     //Double the capacity to reallocate storage for the vector less often every time size==capacity

  //The class interface
  public:
    //Constructor, distructor area
    explicit bVector(int initialSize);                //default constructor to create a bVector object by specifying the initialSize
    explicit bVector(const bVector &obj2Cpy);         //The copy constructor, where we want to create a new object that is a copy of another bVector object
    ~bVector() {delete [] objects;}                   //bVector distructor. Once the scope of the bVector is ended

    //all the operations done on the object
    void resize(int newSize);                         //re-size the vector [Mutator]
    void reserve(int newCapacity);                    //re-allocate memory locations for the vector [Mutator]
    bool isEmpty() {return size==0;}                  //returns if the vector is empty [Accessor]
    int getCapacity() {return capacity;}              //returns the current object capacity
    int getSize() {return size;}                      //returns the current object size
    void pushBack(const userClass &pObj);             //Insert the pObj at the end of the vector [Mutator]
    void pop() {size--;}                              //Decrement the size pointer, ignoring the last stored object [Mutator]
    const userClass & getLastElement() {return objects[size-1];}
                                                     //Returns a constant reference to the last element [Accessor]

    //operator overloading
    bVector & operator= (const bVector &r);           //Assignment operator overloading when equating two bVector s with each other
    userClass & operator[] (int indx);                //Subscripting operator overloading when trying to access bVector[index] [Mutator]
};
#endif
