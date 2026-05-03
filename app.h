#pragma once
#include "headers.h"
#include <fstream>
namespace dHeader
{
    class socialNetworkApp
    {
        User **users;
        Page **pages;
        Post **posts;
        User *currentUser;
        Date currentDate;
        int userCount, pagesCount, postCount;

    public:
        socialNetworkApp();
        ~socialNetworkApp();
        void setCurrentUser();
        void readData(std ::istream &file);
        void readPages(std::istream &file);
        void viewHome();
        void likeAPost();
        void likedPeopleList(); // displays the list of people who have liked a post
        void commentOnAPost();
        void viewPost();
        void shareMemory();
        void viewProfile();
        void viewFriendList();
        void viewPage();
        User *getUserByID(std ::string ID); // scans the user array and then returns the user object pointer
        Page *getPageByID(std::string ID);
        Post *getPostByID(std ::string ID);
        void run();
    };
}