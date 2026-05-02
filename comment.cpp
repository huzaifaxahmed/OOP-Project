#include "headers.h"
#include <iostream>
using namespace std;
using namespace dHeader;

Comment::Comment (User *u,Page* p , std :: string text){
    this->CommenterUser = u;
    this->CommenterPage = p;
    this->text = text;
}
Comment::~Comment (){

}
std::string Comment::getText(){
    return text;
}
User* Comment::getCommenterUser(){
    return CommenterUser;
}
Page* Comment::getCommenterPage(){
    return CommenterPage;
}
void Comment::view(){
    if(CommenterUser != nullptr){
        cout << CommenterUser->getName() << " wrote: " << text << endl;
    }
    else{
        cout << CommenterPage->getTitle() << " wrote: " << text << endl;
    }
}
