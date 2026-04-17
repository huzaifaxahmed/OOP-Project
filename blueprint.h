#pragma once 
#include<iostream>
#include<string>
namespace myHeader{
    class page ; // forward declaration 
    class date {
        int month , day , year ;
        public : 
            date(){}
            date (int day, int month , int year) ;
    };
    class Activity{
    int type ;
    int value ;
    public : 
    Activity();
    ~Activity() ;
    void displayOptions();
    void setTypeAndValue(int type,std :: string value) ; // sets the value given by the user and the type corresponding to the index in the table 
};
    class user{
        std :: string ID ;
        std :: string name ;
        user** friends ;
        page **likedPages ;
        public : 
        user();
        ~user() ;
        void viewHome() ;
        void likePost (); 
        void viewProfile() ;
        void viewFriendList() ;
};
    class post {
        std :: string ID ;
        std :: string description ;
        date shareDate ;
        user ** liked ;
        Activity *a ; // optional 
        comment **comments ;
        int likedCount ;
        int commentCount ; 
        public :
        post() ;
        ~post() ;
        void seeLiked() ; // list of people who have liked the post 
        void addComment(comment c) ;
        void view() ; 
    };
    class page {
        std :: string ID ;
        post** posts ;
        Memory **memories ;
        user* owner ;
        int totalLiked ;
        public : 
        page() ;
        ~page();
        void view() ; // displays all its posts 
    };
    class comment{
    user* commenter ; 
    std :: string text ;
    public :
    comment (user *commenter , std :: string text);
    ~comment ();
};
class Memory{
    post *ptr ; ;
    std :: string text ;
    public : 
    Memory(post *ptr, std :: string text) ;
    ~Memory();
};

class socialNetworkApp ; // this class will serve the purpose of a driver program with the starting point socialNetworkApp :: run() 
}