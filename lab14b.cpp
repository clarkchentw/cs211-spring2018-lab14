#include <cstdio>

// The node class for the linked list
//   This contains the operations and data for each individual
//   node in the list.   
//   The "list-level" stuff is maintained in the MyList class
class MyLNode
{
 private:
  int elem;
  MyLNode* next;
  
 public:
  MyLNode (int v1);
  MyLNode (int v1, MyLNode* n);
  
  void setElem (int e);
  int getElem ();
  void setNext (MyLNode* n);
  MyLNode* getNext();
};

// the list class for the linked list
//  This contains all of the operations and data for the
//  list as a whole
//  This class relies heavily on the MyLNode class
class MyList
{
 private:
  MyLNode* head;
  void copyNode (MyLNode* pNode);  
  
 public:
  MyList();              // default constructor
  MyList(const MyList&); // copy constructor
  ~MyList();             // destructor   

  void show();
  void insert (int v1);
  void remove (int v1);
  void removeAll ();
  void makeCopy (const MyList& p);

  MyList& operator= ( const MyList& p);
};



//  Code for the methods is the MyLNode class
//    These are the Node Level operations
//    Contains: 
//      2 constructors
//      Getters and Setters for the 2 data members
MyLNode::MyLNode (int v1)
{
  elem = v1;
  next = NULL;
}
  
MyLNode::MyLNode (int v1, MyLNode* n)
{
  elem = v1;
  next = n;
}

void MyLNode::setElem (int e)
{
  elem = e;
}

int MyLNode::getElem ()
{
  return elem;
}

void MyLNode::setNext (MyLNode* n)
{
  next = n;
}

MyLNode* MyLNode::getNext()
{
  return next;
}



//  Methods for the MyList class
//    These are the List Level operations
MyList::MyList()
{
  head = NULL;
}

MyList::MyList ( const MyList &p)   //LINE 95
{
 //head = p.head;    // This code does Shallow Copy
	makeCopy(p);
}

// Code to make a copy of a list - doing a Deep Copy
//   This code uses the recursive method of copyNode()
//   copyNode() should be private since it is intended to only
//   be called by makeCopy()
void MyList::makeCopy ( const MyList &p)
{
 head = NULL;
 copyNode (p.head);
} 
 
void MyList::copyNode (MyLNode* pNode)
{
  if (pNode != NULL)
  {
    copyNode ( pNode->getNext() );

    // insert nodes at the front of the list while returning
    //   from the recursive calls  (adds values to the front
    //   in reverse order - this copies the list on O(n) time
    head = new MyLNode ( pNode->getElem(), head );
  }
}

// method to print out all of the values in the list
void MyList::show()
{
  MyLNode* tmp = head;
  
  while ( tmp != NULL )
  {
    printf ("%d, ", tmp->getElem() );
    tmp = tmp->getNext();
  }
  printf ("\n");
}

void MyList::insert (int v1)
{
  MyLNode* tmp = new MyLNode (v1);
  
  // this code just inserts the node at the beginning of the list
  //tmp->setNext (head);
  //head = tmp;

  // the following code insert the node in increasing order in the list
  MyLNode* curr = head;
  MyLNode* prev = NULL;
  
  while ( ( curr != NULL ) && ( curr->getElem() < v1 ) )
  {
    prev = curr;
    curr = curr->getNext();
  }

  // set the next pointer in the new node to point to curr
  tmp->setNext ( curr );

  if ( prev == NULL ) // v1 becomes the in first/head node in list
    head = tmp;
  else
    prev->setNext( tmp );
}


void MyList::remove (int v1)
{
  MyLNode* curr = head;
  MyLNode* prev = NULL;
  
  while ( ( curr != NULL ) && ( curr->getElem() != v1 ) )
  {
    prev = curr;
    curr = curr->getNext();
  }

  if ( curr == NULL ) // v1 does not exist in list
    return;

  if ( prev == NULL ) // v1 is in first/head node in list
  {
    head = curr->getNext();
    delete curr;
  }
  else
  {
    prev->setNext( curr->getNext() );
    delete curr;
  }
}

  

void MyList::removeAll ()
{
  MyLNode* tmp = head;
  
  while ( tmp != NULL )
  {
    MyLNode* tmp2 = tmp;
    tmp = tmp->getNext();
    delete tmp2;
  }
  head = NULL;
}

MyList::~MyList()
{
  // doing a show() so we can see when the destructor is called
  printf ("In Destructor: ");
  show();

  // Note that removeAll() does same operation as required by destructor
  removeAll();
}

// the overloaded assignment operator
//
MyList& MyList::operator= (const MyList& p)
{
 if ( this == &p )   // both operands are the same
   return *this;     //   do nothing, just return

 removeAll();        // Deallocate the existing list

 makeCopy (p);       // Do a deep copy

 return *this;       // allow for "cascading assignments":  a = b = c;
}

void functPBR ( MyList &p)
{
 printf ("In functPBR: ");
 p.show();
}

void functPBV ( MyList p)
{
 printf ("In functPBV: ");
 p.show();
}



int main (int argc, char** argv)
{
  MyList list1;
  MyList list2;

  // insert some values
  printf ("\nTesting the insert() and show() methods\n");
  list1.insert (5);
  list1.insert (18);
  list1.insert (10);
  list1.show();
  list1.insert (3);
  list1.show();
    
  list2.insert (51);
  list2.insert (68);
  list2.insert (24);
  list2.show();
  list2.insert (93);
  list2.show();
    
  // remove some values
  printf ("\nTesting the remove() method\n");
  list1.remove (10);
  list1.show();
  list1.remove (7);
  list1.show();
  list1.remove (3);
  list1.show();
  list1.remove (18);
  list1.show();
    
  list2.remove (93);
  list2.remove (24);
  list2.remove (51);
  list2.show();
  list2.remove (68);
  list2.show();
  list2.remove (3);
  list2.show();
  list2.remove (18);
  list2.show();
    
  /* add code to test the getListLength and getNthElem methodes */
  printf ("\nTesting the getListLength() and getNthElem() methods\n");
  MyList list3;
  // insert some values and verify they are correct
  list3.insert (6);
  list3.insert (4);
  list3.insert (10);
  list3.insert (2);
  list3.insert (8);
  list3.show();

  // Code to test the Copy Constructor
  printf ("\nTesting the Copy Constructor\n");
  // creating a nested block of code for a local variable
  if ( true )
  { 
    MyList list4 ( list3 );
    list3.show();
    list4.show();
    list4.insert(7);
    printf ("If the next 2 lines are the same, Shallow Copy occurred\n");
    list3.show();
    list4.show();

    // as nested block of code ends, destructor is invoked on list4
  } // LINE 311
  // all of the nodes from list4 were removed
  printf ("\nTesting destructor's impact on list3\n");
  list3.show();

  // Test of destructor and Copy Constructor
  printf ("\nTesting the destructor and Copy Constructor\n");
  MyList list5;
  list5.insert (30);
  list5.insert (50);
  list5.insert (10);
  list5.insert (20);
  list5.insert (40);
  list5.show();
  MyList list6;
  list6.makeCopy ( list5 );
  list6.show();
  // call a function sending list5 as pass-by-reference
	printf("LINE 329\n");
  functPBR ( list5 );       // LINE 329
  list5.show();
	printf("LINE 333\n");
  // call a function sending list6 as pass-by-value
  functPBV ( list6 );       // LINE 333
  list6.show();
  
  // Use the overloaded assignment operator 
  MyList list7, list8, list9;
  list7.insert (3);
  list7.insert (6);
  list7.insert (9);
  list7.insert (12);
  list8.insert (2);
  list8.insert (4);
  list8.insert (6);
  list9.insert (12);
  list9.insert (14);
  list9.insert (16);
  list7.show();
  list8.show();
  list9.show();
  list7 = list8;
  list9 = list9;		// LINE 352
  list7.show();
  list8.show();
  list9.show();
  list7 = list8 = list9;	// LINE 356
  list7.show();
  list8.show();
  list9.show();


  // At End of Main
  printf ("\nAt End of Main: Destructor is invoked\n"); 
 
  return 1;
}
