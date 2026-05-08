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
        Memory **memories ;
        int userCount, pagesCount, postCount;

    public:
        socialNetworkApp();
        ~socialNetworkApp();
        void setCurrentUser();
        void readUser(std ::istream &file);
        void readPages(std::istream &file);
        void readPosts(std::istream &file);
        void readComments(std::istream &file);
        void readData();
        void viewHome();
        void likeAPost();
        void likedPeopleList(); // displays the list of people who have liked a post
        void commentOnAPost();
        void viewPost();
        void shareMemory();
        void viewMemories();
        void viewProfile();
        void viewFriendList();
        void viewPage();
        User *getUserByID(std ::string ID); // scans the user array and then returns the user object pointer
        Page *getPageByID(std::string ID);
        Post *getPostByID(std ::string ID);
        void run();
    };
}