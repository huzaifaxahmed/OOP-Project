#include "app.h"
#include "headers.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
namespace dHeader
{
    socialNetworkApp::socialNetworkApp(){
        users = nullptr;
        pages = nullptr;
        posts = nullptr;
        currentUser = nullptr;
        userCount = 0;
        pagesCount = 0;
        postCount = 0;
    }

    socialNetworkApp::~socialNetworkApp(){
        for(int i = 0; i < userCount; i++)
            delete users[i];
        delete[] users;
    
        for(int i = 0; i < pagesCount; i++)
            delete pages[i];
        delete[] pages;
    
        for(int i = 0; i < postCount; i++)
            delete posts[i];
        delete[] posts;
    }

    void socialNetworkApp ::setCurrentUser()
    {
        std ::string user;
        std ::cout << "Enter the id of the user you want to set as the owner \n";
        std ::cout << "Here are your options \n";
        for (int i = 0; i < userCount; i++)
            users[i]->display();
        getline(std ::cin, user);
        // now loop through the users to find the user and then set him as the owner
        int idx = -1;
        for (int i = 0; i < userCount; i++)
        {
            if (user == users[i]->getID())
                idx = i;
        }
        if (idx == -1)
        {
            std ::cout << "Invalid name entered \n";
            return;
        }
        currentUser = users[idx]; // copies the address of the user (composition)
    }

    User *socialNetworkApp ::getUserByID(std ::string ID)
    {
        for (int i = 0; i < userCount; i++)
        {
            if (users[i]->getID() == ID)
                return users[i];
        }
        return nullptr;
    }

    Page *socialNetworkApp::getPageByID(std::string ID)
    {
        for (int i = 0; i < pagesCount; i++)
        {
            if (pages[i]->getID() == ID)
                return pages[i];
        }
        return nullptr;
    }

    Post *socialNetworkApp::getPostByID(std::string id)
    {
        for (int i = 0; i < postCount; i++)
        {
            if (posts[i]->getID() == id)
                return posts[i];
        }
        return nullptr;
    }

    void socialNetworkApp::readPages(std::istream &file)
    {
        int count;
        file >> count;
        pages = new Page *[count];
        pagesCount = count;
        for (int i = 0; i < count; i++)
        {
            std::string id, title;
            file >> id;
            std ::getline(file >> std ::ws, title);
            pages[i] = new Page(id, title);
        }
    }

    void socialNetworkApp ::readUser(std ::istream &file)
    {
        std ::string *userNames;
        std::string *userID;
        std::string *friends;
        std::string *pages;
        int nameIdx = 0;
        int idIdx = 0;
        int friendIdx = 0;
        int pagesIdx = 0;
        std::string reader;
        std::string firstName, lastName;
        file >> userCount;
        users = new User *[userCount];
        userNames = new std ::string[userCount];
        userID = new std ::string[userCount];
        friends = new std ::string[userCount];
        pages = new std ::string[userCount];
        for (int i = 0; i < userCount; i++)
        {
            file >> reader;
            userID[idIdx] = reader;
            file >> firstName;
            file >> lastName;
            userNames[nameIdx] = firstName + " " + lastName;
            users[nameIdx] = new User(userID[idIdx], userNames[nameIdx]);
            file >> reader;
            while (reader != "-1")
            {
                friends[friendIdx] += " " + reader;
                file >> reader;
            }
            file >> reader;
            while (reader != "-1")
            {
                pages[pagesIdx] += " " + reader;
                file >> reader;
            }
            nameIdx++, idIdx++, pagesIdx++, friendIdx++;
        }
        // addfriend
        for (int i = 0; i < userCount; i++)
        {
            std ::stringstream ss(friends[i] + " -1");
            std ::string temp;
            ss >> temp;
            while (temp != "-1")
            {
                User *tempUser = getUserByID(temp);
                if (tempUser == nullptr)
                {
                    std ::cout << "no such user exists \n";
                    continue;
                }
                users[i]->addFriend(tempUser);
                ss >> temp;
            }
        }
        // addlikedpage
        for (int i = 0; i < userCount; i++)
        {
            std ::stringstream ss(pages[i] + " -1");
            std ::string temp;
            ss >> temp;
            while (temp != "-1")
            {
                Page *tempPage = getPageByID(temp);
                if (tempPage == nullptr){
                    std ::cout << "No such page exists \n";
                    ss>>temp;
                    continue;
                }
                users[i]->addLikedPage(tempPage);
                ss >> temp;
            }
        }
        delete[] userNames;
        delete[] userID;
        delete[] friends;
        delete[] pages;
    }

    void socialNetworkApp::readPosts(std::istream &file)
    {
        file >> postCount;
        posts = new Post *[postCount];

        for (int i = 0; i < postCount; i++)
        {
            int postType;
            std::string postID;
            std ::string description;
            std ::string owner;
            bool ownerType; // 1 if the owner is a user 0 if the owner is a page
            int day, month, year;

            int activityType;          // only applicable if the post is an activity
            std ::string activityDesc; // same as above

            file >> postType >> postID;
            file >> day >> month >> year;

            Date temp(day, month, year);

            std ::getline(file >> std ::ws, description);

            if (postType == 2)
            {
                file >> activityType;
                std ::getline(file >> std ::ws, activityDesc);
            }
            file >> owner;
            ownerType = owner[0] == 'p' ? 0 : 1;
            if (ownerType)
            {
                User *ownerUser = getUserByID(owner);
                if (ownerUser == nullptr)
                {
                    std ::cout << "Faulty owner no such user exits \n";
                    continue;
                }
                if (postType == 2)
                    posts[i] = new Activity(postID, description, temp, ownerUser, nullptr, activityType, activityDesc);
                else
                    posts[i] = new Post(postID, description, temp, ownerUser, nullptr);
            }
            else
            {
                Page *ownerPage = getPageByID(owner);
                if (ownerPage == nullptr)
                {
                    std ::cout << "Faulty owner no such user exits \n";
                    continue;
                }
                if (postType == 2)
                    posts[i] = new Activity(postID, description, temp, nullptr, ownerPage, activityType, activityDesc);
                else
                    posts[i] = new Post(postID, description, temp, nullptr, ownerPage);
            }
            // now reading users and pages which liked the post
            std ::string likers;
            file >> likers;
            while (likers != "-1")
            {
                if (likers[0] == 'p')
                {
                    Page *temp = getPageByID(likers);
                    posts[i]->addLike(temp);
                }
                else
                {
                    User *temp = getUserByID(likers);
                    posts[i]->addLike(temp);
                }
                file >> likers;
            }
        }
    }
    void socialNetworkApp::readComments(std::istream& file){
    int count;
    file >> count;
    
    for(int i = 0; i < count; i++){
        std::string commentID, postID, commenterID;
        std::string text;
        
        file >> commentID >> postID >> commenterID;
        std::getline(file >> std::ws, text);
        Post *post = getPostByID(postID);
        User *commenterUser = nullptr;
        Page *commenterPage = nullptr;

        if (commenterID[0]=='u')
            commenterUser = getUserByID(commenterID);
        else
            commenterPage = getPageByID(commenterID);

        Comment *comment = new Comment(commenterUser, commenterPage, text);


        if(post == nullptr){
            std::cout << "Post not found\n";
            delete comment;
            continue;
        }
        post->addComment(comment);
    }

}

int main() {}