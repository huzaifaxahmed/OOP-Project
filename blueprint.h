#pragma once 
#include<iostream>
namespace myHeader{
class user{
    int ID ;
    std :: string name ;
    user** friends ;



};
class page {
    int ID ;
    std :: string description ;
    int totalLiked ;


};
class post {
    int ID ;
    user ** liked ;
    int likedCount ;
    int commentCount ; 
};
}