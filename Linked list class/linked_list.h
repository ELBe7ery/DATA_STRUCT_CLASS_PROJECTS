#ifndef BLINKED_LIST_H
#define BLINKED_LIST_H
template<typename userClass>
struct node
{
    //Node attributes
    userClass data;                          //object stored
    node * nextNode;                         //link to the next node

    //Call by const. ref. No need to copy whatever object, since it will be handeled by operator=() definition
    explicit node(const userClass &userData) : data(userData), nextNode(0){}
    /*
    - No need for setters, getters since no one but the friendClass list will access these values
    */
};
template<typename userClass>
class BlinkedList{
  //ll internal attributes
  private:
    node<userClass> * start;                            //A pointer to the first item in the lL
    node<userClass> * end;                              //A pointer to the last item in the ll [Used for O(1) push back]

  //ll interface
  public:
    explicit BlinkedList();                             //Defult constructor
    explicit BlinkedList(const userClass &userObj);           //Construct the ll with  single element
    void insert (const userClass &userObj,int indx);            //insert an item at some index indx
    void pushBack(const userClass & userObj);                 //Push the user Object back to the ll
    void pushFront(const userClass &userObj);                 //Push the user obj infront of the ll
    void printAll();                                    //Prints all the object inside the ll
    bool find(const userClass &userObj);                      //returns if a specific object is in the ll [Depends on operator==()]
    void removeItem(const userClass &userObj);                //removes the user object if its found
    void clear();                                       //deletes all the node objects [since each is created by new] [Depends on the userObj distructor]
  //private methods
  node<userClass> * findNode(const userClass &userObj);     //returns an the node object or null if the userObj doesn't exist in the ll
};
#endif
