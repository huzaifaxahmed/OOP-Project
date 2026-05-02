#pragma once 
#include"headers.h"
#include<fstream>
namespace dHeader{
class socialNetworkApp{
    User *owner;
    User **users ;
    Page **pages ;
    Post **posts ;
    User *currentUser ;
    int userCount , pagesCount , postCount ;
    public : 
    void setCurrentUser() ;
    void readData(std :: istream &file);
    void viewHome() ;
    void likeAPost();
    void likedPeopleList() ; //displays the list of people who have liked a post 
    void commentOnAPost() ;
    void viewPost() ;
    void shareMemory();
    void viewProfile() ;
    void viewFriendList() ;
    void viewPage() ;
    User getUserByID(std :: string ID); // scans the user array and then returns the user object pointer
    // all these functions will ask for the parameters first after they are called 
    // this is done to avoid doing much work in the main/run and maintain the readability of the code 
    void run() ;
};
}