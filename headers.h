#pragma once
#include <iostream>
#include <string>

namespace dHeader
{
    class Comment;
    class Memory;
    class Page;
    class Post; // forward declaration
    class Date
    {
    protected:
        int month, day, year;

    public:
        Date() {}
        Date(int day, int month, int year);
        bool within24Hours(Date other);
        void display();
        int yearsAgo(Date other);
    };

    class User
    {
        std ::string ID;
        std ::string name;
        User **friends;
        Page **likedPages;
        Post **myPosts;
        int friendCount;
        int postCount;
        int likedPagesCount;

    public:
        User(std::string id, std::string name);
        User();
        User(const User &obj);
        ~User();
        User &operator=(const User &obj);
        std::string getID();
        std::string getName();
        void addFriend(User *u);
        void removeFriend(User *u);
        void addLikedPage(Page *p);
        void removeLikedPage(Page *p);
        void addPost(Post *p);
        void removePost(Post *p);
        void display();
        User **getFriends();
        Page **getLikedPages();
        Post **getMyPosts();
        int getFriendCount();
        int getLikedPagesCount();
        int getPostCount();
    };

    class Post
    {
    protected:
        std ::string ID;
        std ::string description;
        Date shareDate;
        User **usersThatLiked; // max 10.  //if User had been deleted, it should be reduced from here
        Page **pagesThatLiked;
        Comment **comments; // max 10
        User *ownerUser;
        Page *ownerPage;
        int likedCount;
        int pageLikeCount;
        int commentCount;

    public:
        Post(std::string id, std::string desc, Date d, User *u, Page *p);
        virtual ~Post();
        void addLike(User *u);
        void addLike(Page *p);
        void removeLike(User *u);
        void seeLiked(); // list of people who have liked the Post
        void addComment(Comment *c);
        void removeComment(Comment *c);
        virtual void display();
        std ::string getID();
        std ::string getDesc();
        Date getDate();
    };

    class Activity : public Post
    {
        int type;
        std::string value;

    public:
        Activity();
        Activity(std::string id, std::string desc, Date d, User *u, Page *p, int type, std::string value);
        void display() override;
        void setTypeAndValue(int type, std ::string value); // sets the value given by the User and the type corresponding to the index in the table
    };

    class Page
    {
        std ::string ID;
        std::string title;
        Post **Posts;
        // Memory **memories;
        int totalLiked;
        int postCount;
        // int MemoryCount;

    public:
        Page(std::string id, std::string title);
        ~Page();
        Page &operator=(const Page &obj);
        void addPost(Post *p);
        void removePost(Post *p);
        std::string getID();
        std::string getTitle();
        Post **getPosts();
        int getPostCount();
    };

    class Comment
    {
        User *CommenterUser;
        Page *CommenterPage;
        std ::string text;

    public:
        Comment(User *u, Page *p, std ::string text);
        ~Comment();
        std::string getText();
        User *getCommenterUser();
        Page *getCommenterPage();
        void view();
    };

    class Memory : public Post
    {
        Post *original;

    public:
        Memory(std::string id, std::string desc, Date d, User *u, Page *p, Post *original);
        ~Memory();
        void display(Date currentDate);
    };

    class socialNetworkApp
    {
        void viewHome();
        void likePost();
        void viewProfile();
        void viewFriendList();

    }; // this class will serve the purpose of a driver program with the starting point socialNetworkApp :: run()

}