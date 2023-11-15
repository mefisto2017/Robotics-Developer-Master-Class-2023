#include<iostream>
#include<set>
using namespace std;
int main()
{
    set < int > s;
  
    // inserting elements in random order .
    s.insert( 5 ) ;
    s.insert( 1 ) ;
    s.insert( 2 ) ;
    s.insert( 3 ) ;
    s.insert( 4 ) ;
     
    // printing set s
    //initialising the iterator, iterating to the beginning of the set.
 
    set<int >::iterator it ;
    cout << "The element of set s are : \n";
    for (it = s.begin() ; it != s.end() ; it++ ) 
    {
        cout << *it<<" ";
    }
    cout << endl;
    cout<< "The size of set : \n " << s.size() <<endl ;
    return 0 ;
}
     