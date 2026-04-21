#pragma once 
#include<iostream>
#include<string>

namespace dHeader{
    class Comment;
    class Memory;
    class Page ;
    class Post; // forward declaration 
    class Date {
        int month , day , year ;
    public : 
        Date(){}
        Date (int day, int month , int year);
        bool within24Hours(Date other);
    };

    class User{
        std :: string ID ;
        std :: string name ;
        User** friends ;
        Page** likedPages ;
        Post** myPosts;
        int friendCount;
        int PostCount;
        int likedPagesCount;
    public : 
        User(std::string id="n/a",std::string name="n/a");
        ~User() ;
        std::string getID();
        std::string getName();
        void addFriend(User* u);
        void removeFriend(User*u);
        void addLikedPage(Page* p);
        void addPost(Post* p);
        User** getFriends();
        Page** getLikedPages();
        Post** getMyPosts();
        int getFriendCount();
        int getLikedPagesCount();
        int getPostCount();
    };

    class Post {
        std :: string ID ;
        std :: string description ;
        Date shareDate ;
        User ** UsersThatLiked ;// max 10.  //if User had been deleted, it should be reduced from here
        Comment **Comments ;//max 10
        int likedCount ;
        int CommentCount ; 
    public :
        Post(std::string id, std::string desc, Date d);
        ~Post() ;
        void addLike(User* u);
        void seeLiked() ; // list of people who have liked the Post 
        void addComment(Comment* c) ;
        void view(); 
        std :: string getID() ;
        std :: string getDesc() ;
        Date getDate() ;
    };

    class Activity : public Post{
        int type ;
        std::string value ;
    public : 
        Activity();
        Activity(int type, std::string value);
        ~Activity() ;
        void displayOptions();
        void setTypeAndValue(int type, std :: string value) ; // sets the value given by the User and the type corresponding to the index in the table 
    };

    class Page {
        std :: string ID ;
        std:: string title;
        Post** Posts;
        //Memory **memories;
        User* owner;
        int totalLiked;
        int PostCount;
        int MemoryCount;
    public : 
        Page(std::string id,std::string title,User* owner);
        ~Page();
        void addPost(Post* p);
        void view() ; // displays all its Posts 
        std::string getID();
        std::string getTitle();
        Post** getPosts();
        int getPostCount();     
    };

    class Comment{
        User* CommenterUser;
        Page* CommenterPage;
        std :: string text ;
    public :
        Comment (User *Commenter , std :: string text);
        ~Comment ();
        std::string getText();
        User* getCommenterUser();
        Page* getCommenterPage();
        void view();
    };

    class Memory : public Post{
        Post *original;
        std :: string text ;
    public : 
        Memory(Post *original, std :: string text, Date d) ;
        ~Memory();
        void display();
    };

    class socialNetworkApp{
        void viewHome();
        void likePost (); 
        void viewProfile();
        void viewFriendList();  

    };// this class will serve the purpose of a driver program with the starting point socialNetworkApp :: run() 

}