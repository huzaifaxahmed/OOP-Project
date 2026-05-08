#include "headers.h"
using namespace dHeader;
using namespace std;

Memory::Memory(string id, string desc, Date d, User *u, Page *p, Post *original) : Post(id, desc, d, u, p)
{
    this->original = original;
}
void Memory::display(){
    
    if (ownerUser != nullptr)
        cout << ownerUser->getName();
    else
        cout << ownerPage->getTitle();
    cout << " shared a memory ";
    cout<<"(";
    shareDate.display();
    cout <<")" << endl;
    if (!description.empty())
        cout << "\"" << description << "\"" << endl;
    int years = original->getDate().yearsAgo(shareDate);
    cout<<"("<<years<<" Years Ago)"<<endl;
    cout<<"----"<<endl;
    original->display();
    for (int i = 0; i < commentCount; i++)
        comments[i]->view();
}
Memory::~Memory()
{
    original = nullptr;
}