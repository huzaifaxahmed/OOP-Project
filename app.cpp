#include "app.h"
#include "headers.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
namespace dHeader
{
    socialNetworkApp::socialNetworkApp(int day , int month , int year ) : currentDate(day,month,year)
    {
        users = nullptr;
        pages = nullptr;
        posts = nullptr;
        currentUser = nullptr;
        memories = nullptr ;
        userCount = 0;
        pagesCount = 0;
        postCount = 0;
    }

    socialNetworkApp::~socialNetworkApp()
    {
        for (int i = 0; i < userCount; i++)
            delete users[i];
        delete[] users;

        for (int i = 0; i < pagesCount; i++)
            delete pages[i];
        delete[] pages;

        for (int i = 0; i < postCount; i++)
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
        std :: cin.ignore();
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
        if(!file){
            std :: cout << "Error in opening pages.txt\n" ;
        }
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
        if(!file){
            std :: cout << "Error in opening users.txt\n" ;
            return ;
        }
        std ::string *userNames;
        std::string *userID;
        std::string *friends;
        std::string *pagesID;
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
        pagesID = new std ::string[userCount];
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
                pagesID[pagesIdx] += " " + reader;
                file >> reader;
            }
            nameIdx++, idIdx++, pagesIdx++, friendIdx++;
        }
        // addfriend
        int count = 0 ;
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
                    ss >> temp;
                    continue;
                }
                users[i]->addFriend(tempUser);
                ss >> temp;
                count++ ;
            }
            users[i]->setFriendCount(count) ;
        }

        // addlikedpage
        for (int i = 0; i < userCount; i++)
        {
            count =  0;
            std ::stringstream ss(pagesID[i] + " -1");
            std ::string temp;
            ss >> temp;
            while (temp != "-1")
            {
                Page *tempPage = getPageByID(temp);
                if (tempPage == nullptr)
                {
                    std ::cout << "No such page exists \n";
                    ss >> temp;
                    continue;
                }
                users[i]->addLikedPage(tempPage);
                ss >> temp;
                count++ ;
            }
            users[i]->setLikedPagesCount(count) ;
        }
        delete[] userNames;
        delete[] userID;
        delete[] friends;
        delete[] pagesID;
    }

    void socialNetworkApp::readPosts(std::istream &file)
    {
        if(!file){
            std :: cout << "Error in opening posts.txt\n" ; 
        }
        file >> postCount;
        posts = new Post *[postCount];

        int j  = 0 ;  // keeps track of valid posts 
        for (int i = 0 ; i < postCount; i++) 
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
                    posts[j++] = new Activity(postID, description, temp, ownerUser, nullptr, activityType, activityDesc);
                else
                    posts[j++] = new Post(postID, description, temp, ownerUser, nullptr);

                ownerUser->addPost(posts[j - 1]);
                ownerUser->increasePostCount() ;
            }
            else
            {
                Page *ownerPage = getPageByID(owner);
                if (ownerPage == nullptr)
                {
                    std ::cout << "Faulty owner no such page exits \n";
                    continue;
                }
                if (postType == 2)
                    posts[j++] = new Activity(postID, description, temp, nullptr, ownerPage, activityType, activityDesc);
                else
                    posts[j++] = new Post(postID, description, temp, nullptr, ownerPage);

                ownerPage->addPost(posts[j - 1]);
                ownerPage->increasePostCount() ;
            }
            // now reading users and pages which liked the post
            std ::string likers;
            file >> likers;
            while (likers != "-1")
            {
                if (likers[0] == 'p')
                {
                    Page *temp = getPageByID(likers);
                    if(temp == nullptr){
                        std :: cout << "Invalid ID \n";
                        continue ;
                    }
                    posts[j - 1]->addLike(temp);
                    posts[j-1]->increasePageLikedCount() ;
                }
                else
                {
                    User *temp = getUserByID(likers);
                    if(temp == nullptr){
                        std :: cout << "Invalid ID \n" ;
                        continue ;
                    }
                    posts[j - 1]->addLike(temp);
                    posts[j-1]->increaseUserLikedCount() ;
                }
                file >> likers;
            }
        }
        postCount = j ;
    }
    void socialNetworkApp::readComments(std::istream &file)
    {
        if(!file){
            std :: cout << "Error in opening file\n" ;
        }
        int count;
        file >> count;

        for (int i = 0; i < count; i++)
        {
            std::string commentID, postID, commenterID;
            std::string text;

            file >> commentID >> postID >> commenterID;
            std::getline(file >> std::ws, text);
            Post *post = getPostByID(postID);
            User *commenterUser = nullptr;
            Page *commenterPage = nullptr;

            if (commenterID[0] == 'u')
                commenterUser = getUserByID(commenterID);
            else
                commenterPage = getPageByID(commenterID);

            Comment *comment = new Comment(commenterUser, commenterPage, text);

            if (post == nullptr)
            {
                std::cout << "Post not found\n";
                delete comment;
                continue;
            }
            post->addComment(comment);
        }
    }
    void socialNetworkApp::viewPage()
    {
        std::string id;
        std::cout << "Enter Page ID: ";
        std::cin >> id;
        Page *p = getPageByID(id);
        if (p == nullptr)
        {
            std::cout << "Page not found!\n";
            return;
        }
        std::cout << p->getTitle() << std::endl;
        for (int i = 0; i < p->getPostCount(); i++)
        {
            p->getPosts()[i]->display();
        }
    }

    void socialNetworkApp::viewPost()
    {
        std::string id;
        std::cout << "Enter post ID: ";
        std::cin >> id;
        Post *p = getPostByID(id);
        try
        {
            if (p == nullptr)
                throw std::string("Post not found!");
            p->display();
        }
        catch (std::string e)
        {
            std::cout << "Error: " << e << std::endl;
        }
    }
    void socialNetworkApp::likeAPost()
    {
        std::string id;
        std::cout << "Enter post ID: ";
        std::cin >> id;

        if (currentUser == nullptr)
        {
            std::cout << "No current user set!\n";
            return;
        }
        Post *p = getPostByID(id);
        if (p == nullptr)
        {
            std::cout << "Post not found!\n";
            return;
        }
        p->addLike(currentUser);
    }

    void socialNetworkApp::commentOnAPost()
    {
        std::string id, text;
        std::cout << "Enter post ID: ";
        std::cin >> id;
        std::cout << "Enter comment: ";
        std::cin.ignore();
        std::getline(std::cin, text);

        if (currentUser == nullptr)
        {
            std::cout << "No current user set!\n";
            return;
        }
        Post *p = getPostByID(id);
        if (p == nullptr)
        {
            std::cout << "Post not found!\n";
            return;
        }
        Comment *c = new Comment(currentUser, nullptr, text);
        p->addComment(c);
    }

    void socialNetworkApp::shareMemory()
    {
        std::string postID, text;
        std::cout << "Enter post ID: ";
        std::cin >> postID;
        std::cout << "Enter text: ";
        std::cin.ignore();
        std::getline(std::cin, text);

        if (currentUser == nullptr)
        {
            std::cout << "No current user set!\n";
            return;
        }
        Post *original = getPostByID(postID);
        if (original == nullptr)
        {
            std::cout << "Post not found!\n";
            return;
        }
        Memory *m = new Memory("m" + std::to_string(postCount + 1), text, currentDate, currentUser, nullptr, original);

        // resize allPosts array
        Post **temp = new Post *[postCount + 1]; // adding the post to the socialNetworkApp :: posts array
        for (int i = 0; i < postCount; i++)
            temp[i] = posts[i];
        temp[postCount] = m;
        delete[] posts;
        posts = temp;

        currentUser->addPost(m); // adding the post to current user
        postCount++;
        std::cout << "Memory shared successfully!\n";
    }

    void socialNetworkApp::viewMemories()
    {
        if (currentUser == nullptr)
        {
            std::cout << "No current user set!\n";
            return;
        }
        std::cout << "We hope you enjoy looking back at your memories!\n";
        bool found = false;
        for (int i = 0; i < currentUser->getPostCount(); i++)
        {
            Post *p = currentUser->getMyPosts()[i];
            Date postDate = p->getDate();
            if (postDate.isSameDay(currentDate) && postDate.yearsAgo(currentDate) > 0)
            {
                int years = postDate.yearsAgo(currentDate);
                std::cout << years << " Years Ago\n";
                p->display();
                found = true;
            }
        }
        if (!found)
            std::cout << "No memories for today!\n";
    }

    void socialNetworkApp::viewHome()
    {
        std::cout << currentUser->getName() << "  Home Page\n";
        // Friends' posts
        for (int i = 0; i < currentUser->getFriendCount(); i++)
        {
            User *f = currentUser->getFriends()[i];
            for (int j = 0; j < f->getPostCount(); j++)
            {
                Post *p = f->getMyPosts()[j];
                if (p->getDate().within24Hours(currentDate))
                    p->display();
            }
        }
        // Liked pages posts
        for (int i = 0; i < currentUser->getLikedPagesCount(); i++)
        {
            Page *pg = currentUser->getLikedPages()[i];
            for (int j = 0; j < pg->getPostCount(); j++)
            {
                Post *p = pg->getPosts()[j];
                if (p->getDate().within24Hours(currentDate))
                    p->display();
            }
        }
    }

    void socialNetworkApp ::viewProfile()
    {
        std ::cout << currentUser->getName() << "-Time Line \n";
        Post **tempPosts = currentUser->getMyPosts();
        for (int i = 0; i < currentUser->getPostCount(); i++)
        {
            tempPosts[i]->display();
        }
    }
    void socialNetworkApp ::viewFriendList()
    {
        std ::cout << currentUser->getName() << "-Friend List \n";
        User **tempFriends = currentUser->getFriends();
        for (int i = 0; i < currentUser->getFriendCount(); i++)
        {
            std ::cout << "ID : " << tempFriends[i]->getID() << " Name : " << tempFriends[i]->getName() << std ::endl;
        }
    }

    void socialNetworkApp::likedPeopleList()
    {
        std::string id;
        std::cout << "Enter post ID: ";
        std::cin >> id;
        Post *p = getPostByID(id);
        if (p == nullptr)
        {
            std::cout << "Post not found!\n";
            return;
        }
        p->seeLiked();
    }

    void socialNetworkApp::readData()
    {
        std::ifstream pagesFile("pages.txt");
        std::ifstream usersFile("users.txt");
        std::ifstream postsFile("posts.txt");
        std::ifstream commentsFile("comments.txt");
        readPages(pagesFile);
        readUser(usersFile);
        readPosts(postsFile);
        readComments(commentsFile);
    }

    void socialNetworkApp::run()
    {
        readData();
        int choice;
        while (true)
        {
            std::cout << "\n1. Set Current User\n";
            std::cout << "2. View Home\n";
            std::cout << "3. Like a Post\n";
            std::cout << "4. View Liked List\n";
            std::cout << "5. Comment on a Post\n";
            std::cout << "6. View a Post\n";
            std::cout << "7. Share a Memory\n";
            std::cout << "8. View Profile\n";
            std::cout << "9. View Friend List\n";
            std::cout << "10. View Page\n";
            std::cout << "11. See Your Memories\n";
            std::cout << "0. Exit\n";
            std::cout << "Enter choice: ";
            std::cin >> choice;
            switch (choice)
            {
            case 1:
                setCurrentUser();
                break;
            case 2:
                viewHome();
                break;
            case 3:
                likeAPost();
                break;
            case 4:
                likedPeopleList();
                break;
            case 5:
                commentOnAPost();
                break;
            case 6:
                viewPost();
                break;
            case 7:
                shareMemory();
                break;
            case 8:
                viewProfile();
                break;
            case 9:
                viewFriendList();
                break;
            case 10:
                viewPage();
                break;
            case 11:
                viewMemories();
                break;
            case 0:
                return;
            default:
                std::cout << "Invalid choice\n";
            }
        }
    }
}