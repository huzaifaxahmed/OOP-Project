#include "app.h"
#include "headers.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
namespace dHeader
{
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
        for (int i=0;i<pagesCount;i++){
            if(pages[i]->getID() == ID)
                return pages[i];
        }
        return nullptr;
    }


    Post* socialNetworkApp::getPostByID(std::string id){
    for(int i = 0; i < postCount; i++){
        if(posts[i]->getID() == id)
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
            getline(file, title);
            if (!title.empty() && title[0] == ' ')
                title.erase(0, 1);
            pages[i] = new Page(id, title, nullptr);
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
        file >> reader;
        userCount = stoi(reader);
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
                }
                users[i]->addFriend(tempUser);
                ss >> temp;
            }
        }
        delete[] userNames;
        delete[] userID;
        delete[] friends;
        delete[] pages;
    }
    void socialNetworkApp::readPosts(std::istream &file){
    int count;
    file >> count;
    postCount = count;
    posts = new Post*[count];
    
    for(int i = 0; i < count; i++){
        int postType;
        std::string postID;
        file >> postType >> postID;

    }


    
}
int main()
{
}