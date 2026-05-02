#include "headers.h"
using namespace dHeader;
using namespace std;

Memory::Memory(string id, string desc, Date d, User* u, Page* p, Post* original): Post(id, desc, d, u, p){
    this->original=original;
}
Memory::~Memory(){

}
void Memory::display(Date currentDate){
    if(ownerUser != nullptr)
        cout << ownerUser->getName();
    else
        cout << ownerPage->getTitle();
    cout << " shared a memory ";
    shareDate.display();
    cout<<endl<<description<<endl;
    cout << "(" << shareDate.yearsAgo(currentDate) << " Years Ago)" << endl;
}