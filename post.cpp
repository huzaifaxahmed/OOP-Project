#include "headers.h"
using namespace dHeader;

Post::Post(std::string id, std::string desc, Date d, User* u, Page* p){
    ID=id;
    description=desc;
    shareDate=d;
    ownerUser=u;
    ownerPage=p;
    usersThatLiked=nullptr;
    pagesThatLiked=nullptr;
    likedCount=0;
    commentCount=0;
    pageLikeCount=0;
    comments=nullptr;
}
Post::~Post(){

}
void Post::addLike(Page* p){
    int idx = -1 ;
    for(int i = 0 ; i < pageLikeCount ;i++){
        if(pagesThatLiked[i] == p){
            std :: cout << "Page has already liked this post \n" ;
            return ;
        }
    }
    Page** temp = new Page*[pageLikeCount + 1];
    for(int i = 0 ; i < pageLikeCount ; i++){
        temp[i] = pagesThatLiked[i] ;
    }
    temp[pageLikeCount] = p;
    delete[] pagesThatLiked ;
    pagesThatLiked = temp ;
    temp = nullptr ;
    pageLikeCount++ ;
    std :: cout << "Page liked this post succssfully !\n" ;
}
void Post::addLike(User* u){
    int idx = -1 ;
    for(int i = 0 ; i < likedCount ;i++){
        if(usersThatLiked[i] == u){
            std :: cout << "User has already liked this post \n" ;
            return ;
        }
    }
    User** temp = new User*[likedCount + 1];
    for(int i = 0 ; i < likedCount ; i++){
        temp[i] = usersThatLiked[i] ;
    }
    temp[likedCount] = u ;
    delete[] usersThatLiked ;
    usersThatLiked = temp ;
    temp = nullptr ;
    likedCount++ ;
    std :: cout << "User like this post succssfully !\n" ;
}
void Post::seeLiked() {
    for(int i = 0 ; i < likedCount ; i++){
        usersThatLiked[i]->display() ;
        std :: cout << std :: endl ;
    }
}
void Post::addComment(Comment* c) {

}
void Post::view(){

}
std :: string Post::getID(){

}
std :: string Post::getDesc(){

}
Date Post::getDate(){
    
}