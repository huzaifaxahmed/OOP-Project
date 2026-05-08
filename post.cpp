#include "headers.h"
using namespace dHeader;

Post::Post(std::string id, std::string desc, Date d, User *u, Page *p)
{
    ID = id;
    description = desc;
    shareDate = d;
    ownerUser = u;
    ownerPage = p;
    usersThatLiked = nullptr;
    pagesThatLiked = nullptr;
    likedCount = 0;
    commentCount = 0;
    pageLikeCount = 0;
    comments = nullptr;
}

void Post::addLike(Page *p)
{
    int idx = -1;
    for (int i = 0; i < pageLikeCount; i++)
    {
        if (pagesThatLiked[i] == p)
        {
            std ::cout << "Page has already liked this post \n";
            return;
        }
    }
    Page **temp = new Page *[pageLikeCount + 1];
    for (int i = 0; i < pageLikeCount; i++)
    {
        temp[i] = pagesThatLiked[i];
    }
    temp[pageLikeCount] = p;
    delete[] pagesThatLiked;
    pagesThatLiked = temp;
    temp = nullptr;
    pageLikeCount++;
    std ::cout << "Page liked this post succssfully !\n";
}
void Post::addLike(User *u)
{
    int idx = -1;
    for (int i = 0; i < likedCount; i++)
    {
        if (usersThatLiked[i] == u)
        {
            std ::cout << "User has already liked this post \n";
            return;
        }
    }
    User **temp = new User *[likedCount + 1];
    for (int i = 0; i < likedCount; i++)
    {
        temp[i] = usersThatLiked[i];
    }
    temp[likedCount] = u;
    delete[] usersThatLiked;
    usersThatLiked = temp;
    temp = nullptr;
    likedCount++;
    std ::cout << "User like this post succssfully !\n";
}

void Post ::removeLike(User *u)
{
    int idx = -1;
    for (int i = 0; i < likedCount; i++)
    {
        if (usersThatLiked[i] == u)
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
    {
        std ::cout << "This user hasn't liked this post \n";
        return;
    }
    User **temp = new User *[likedCount - 1];
    for (int i = 0, j = 0; j < likedCount; j++)
    {
        if (j != idx)
        {
            temp[i++] = usersThatLiked[j];
        }
    }
    delete[] usersThatLiked;
    usersThatLiked = temp;
    temp = nullptr;
    likedCount--;
}


void Post ::seeLiked()
{
    for (int i = 0; i < likedCount; i++)
    {
        usersThatLiked[i]->display();
        std ::cout << std ::endl;
    }
        for (int i = 0; i < pageLikeCount; i++)
    {
        pagesThatLiked[i]->display();
        std ::cout << std ::endl;
    }
}

void Post::addComment(Comment *c)
{
    int idx = -1;
    if (commentCount >= 10)
    {
        std ::cout << "Max limit reached \n";
        return;
    }
    for (int i = 0; i < commentCount; i++)
    {
        if (comments[i] == c)
        {
            std ::cout << "This comment is already under this post \n";
            return;
        }
    }
    Comment **temp = new Comment *[commentCount + 1];
    for (int i = 0; i < commentCount; i++)
    {
        temp[i] = comments[i];
    }
    temp[commentCount] = c;
    delete[] comments;
    comments = temp;
    temp = nullptr;
    commentCount++;
    std ::cout << "Comment added successfully \n";
}

void Post ::removeComment(Comment *c)
{
    int idx = -1;
    for (int i = 0; i < commentCount; i++)
    {
        if (comments[i] == c)
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
    {
        std ::cout << "The given comment is not under this post \n";
        return;
    }
    Comment **temp = new Comment *[commentCount - 1];
    for (int i = 0, j = 0; i < commentCount; i++)
    {
        if (idx != i)
            temp[j++] = comments[i];
    }
    delete[] comments;
    comments = temp;
    temp = nullptr;
    commentCount--;
}

void Post ::display()
{
    if (ownerPage == nullptr)
        std ::cout << "--" << ownerUser->getName() << " shared : " << description << std ::endl;
    else
        std ::cout << "--" << ownerPage->getTitle() << " shared : " << description << std ::endl;
    for (int i = 0; i < commentCount; i++)
    {
        comments[i]->view();
    }
}
std ::string Post ::getID() { return ID; }
std ::string Post ::getDesc() { return description; }
Date Post ::getDate() { return shareDate; }
Post ::~Post()
{
    delete[] comments;
    delete[] usersThatLiked;
    delete[] pagesThatLiked;
}

