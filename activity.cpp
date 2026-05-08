#include "headers.h"
#include <iostream>
using namespace std;
using namespace dHeader;

Activity::Activity(string id, string desc, Date d, User *u, Page *p, int type, string value) : Post(id, desc, d, u, p)
{
    this->type = type;
    this->value = value;
}
void Activity::display()
{
    if (ownerUser != nullptr)
        cout << ownerUser->getName();
    else
        cout << ownerPage->getTitle();
    switch (type)
    {
    case 1:
        cout << " is feeling " << value << endl;
        break;
    case 2:
        cout << " is thinking about " << value << endl;
        break;
    case 3:
        cout << " is making " << value << endl;
        break;
    case 4:
        cout << " is celebrating " << value << endl;
        break;
    default:
        cout << "Invalid type of activity!" << endl;
        break;
    }
    for (int i = 0; i < commentCount; i++)
    {
        comments[i]->view();
    }
}
void Activity::setTypeAndValue(int type, std::string value)
{
    this->type = type;
    this->value = value;
}