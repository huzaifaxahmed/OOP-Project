#pragma once 
#include<iostream>
#include<string>

namespace dHeader{
    class comment;
    class Memory;
    class page ;
    class post; // forward declaration 
    class date {
        int month , day , year ;
    public : 
        date(){}
        date (int day, int month , int year);
        bool within24Hours(date other);
    };

    class user{
        std :: string ID ;
        std :: string name ;
        user** friends ;
        page** likedPages ;
        post** myPosts;
        int friendCount;
        int postCount;
        int likedPagesCount;
    public : 
        user(std::string id="n/a",std::string name="n/a");
        ~user() ;
        std::string getID();
        std::string getName();
        void addFriend(user* u);
        void removeFriend(user*u);
        void addLikedPage(page* p);
        void addPost(post* p);
        user** getFriends();
        page** getLikedPages();
        post** getMyPosts();
        int getFriendCount();
        int getLikedPagesCount();
        int getPostCount();
    };

    class post {
        std :: string ID ;
        std :: string description ;
        date shareDate ;
        user ** usersThatLiked ;// max 10.  //if user had been deleted, it should be reduced from here
        comment **comments ;//max 10
        int likedCount ;
        int commentCount ; 
    public :
        post(std::string id, std::string desc, date d);
        ~post() ;
        void addLike(user* u);
        void seeLiked() ; // list of people who have liked the post 
        void addComment(comment* c) ;
        void view(); 
        std :: string getID() ;
        std :: string getDesc() ;
        date getDate() ;
    };

    class Activity : public post{
        int type ;
        std::string value ;
    public : 
        Activity();
        Activity(int type, std::string value);
        ~Activity() ;
        void displayOptions();
        void setTypeAndValue(int type, std :: string value) ; // sets the value given by the user and the type corresponding to the index in the table 
    };

    class page {
        std :: string ID ;
        std:: string title;
        post** posts;
        //Memory **memories;
        user* owner;
        int totalLiked;
        int postCount;
        int memoryCount;
    public : 
        page(std::string id,std::string title,user* owner);
        ~page();
        void addPost(post* p);
        void view() ; // displays all its posts 
        std::string getID();
        std::string getTitle();
        post** getPosts();
        int getPostCount();     
    };

    class comment{
        user* commenterUser;
        page* commenterPage;
        std :: string text ;
    public :
        comment (user *commenter , std :: string text);
        ~comment ();
        std::string getText();
        user* getCommenterUser();
        page* getCommenterPage();
        void view();
    };

    class Memory : public post{
        post *original;
        std :: string text ;
    public : 
        Memory(post *original, std :: string text, date d) ;
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