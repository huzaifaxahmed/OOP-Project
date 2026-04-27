#pragma once 
#include"headers.h"
#include<fstream>
namespace dHeader{
class socialNetworkApp{
    User **users ;
    Page **pages ;
    Post **posts ;
    User *currentUser ;
    public : 
    void setCurrentUser(User *current) ;
    void readUsers(const std :: istream &user);
    void readPages(const std :: istream &pages);
    void readPosts(const std :: istream &posts);
    void setCurrentUser() ;
    void viewHome() ;
    void likeAPost();
    void likedPeopleList() ; //displays the list of people who have liked a post 
    void commentOnAPost() ;
    void viewPost() ;
    void shareMemory();
    void viewProfile() ;
    void viewFriendList() ;
    void viewPage() ;
    // all these functions will ask for the parameters first after they are called 
    // this is done to avoid doing much work in the main/run and maintain the readability of the code 
    void run() ;
};
}