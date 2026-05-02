#include"socialNetworkApp.h"
#include"headers.h"
#include<iostream>
#include<fstream>
#include<string>
namespace dHeader{
    void socialNetworkApp ::  setCurrentUser(){
        std :: string user ;
        std :: cout << "Enter the id of the user you want to set as the owner \n" ;
        std :: cout << "Here are your options \n" ;
        for(int i = 0 ; i < userCount ; i++)
            users[i]->display() ;
            getline(std :: cin,user) ;
        // now loop through the users to find the user and then set him as the owner
        int idx = -1 ;
        for(int i = 0 ; i < userCount ; i++){
            if(user == users[i]->getID())
                idx = i ;
        }
        if(idx == -1){
            std :: cout << "Invalid name entered \n" ;
            return ;
        }
        owner = users[idx] ;  // copies the address of the user (composition)
    }
    User socialNetworkApp :: getUserByID(std :: string ID){}
    void socialNetworkApp :: readData(std :: istream &file){
    std ::string *userNames;
    std::string *userID;
    std::string *friends;
    std::string *pages ;
    int nameIdx = 0;
    int idIdx =  0;
    int friendIdx = 0 ;
    int pagesIdx = 0 ;
    std::string reader ;
    std::string firstName , lastName ;
    file >> reader ;
    int userCount = stoi(reader) ;
    users = new User*[userCount];
    for(int i = 0 ; i < userCount  ; i++){
    file >> reader ;
    userID[idIdx] = reader ;
    file >> firstName ;
    file >> lastName ;
    userNames[nameIdx] = firstName + " " + lastName ;
    users[nameIdx] = new User(userID[idIdx],userNames[nameIdx]) ;
    file >> reader ;
    while(reader != "-1") {
        friends[friendIdx] += " " + reader ;
        file >> reader ;
    }
    file >> reader ;
    while(reader != "-1"){
        pages[pagesIdx] = " " +  reader ;
        file >> reader ;
    }
     nameIdx++ , idIdx++ , pagesIdx++ , friendIdx++ ;
    }
}

}
int main(){
    
}