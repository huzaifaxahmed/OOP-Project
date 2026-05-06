#include "headers.h"
namespace dHeader
{
    // functions of the class user
    User ::User(std ::string id, std ::string name)
    {
        ID = id;
        this->name = name;
    }
    User ::User()
    {
        name = "N/A";
        ID = "N/A";
        friends = nullptr;
        likedPages = nullptr;
        myPosts = nullptr;
        likedPagesCount = 0;
        postCount = 0;
        friendCount = 0;
    }

    User &User ::operator=(const User &obj)
    {
        if (this == &obj)
            return *this;
        ID = obj.ID;
        name = obj.name;

        friendCount = obj.friendCount;
        likedPagesCount = obj.likedPagesCount;
        postCount = obj.postCount;
        // the main concept is making a new array of single pointers and then copying address value by value
        // so that if one array gets deleted somewhere it does not affect the other
        if (friends != nullptr)
            delete[] friends;

        friends = new User *[friendCount];
        for (int i = 0; i < friendCount; i++)
            friends[i] = obj.friends[i];

        if (likedPages != nullptr)
            delete[] likedPages;

        likedPages = new Page *[likedPagesCount];
        for (int i = 0; i < likedPagesCount; i++)
            likedPages[i] = obj.likedPages[i];

        if (myPosts != nullptr)
            delete[] myPosts;

        myPosts = new Post *[postCount];
        for (int i = 0; i < postCount; i++)
            myPosts[i] = obj.myPosts[i];

        return *this;
    }

    User ::User(const User &obj)
    {
        ID = obj.ID;
        name = obj.name;

        friendCount = obj.friendCount;
        likedPagesCount = obj.likedPagesCount;
        postCount = obj.postCount;
        // the main concept is making a new array of single pointers and then copying address value by value
        // so that if one array gets deleted somewhere it does not affect the other

        friends = new User *[friendCount];
        for (int i = 0; i < friendCount; i++)
            friends[i] = obj.friends[i];

        likedPages = new Page *[likedPagesCount];
        for (int i = 0; i < likedPagesCount; i++)
            likedPages[i] = obj.likedPages[i];

        myPosts = new Post *[postCount];
        for (int i = 0; i < postCount; i++)
            myPosts[i] = obj.myPosts[i];
    }
    std ::string User::getName() { return name; }
    std ::string User ::getID() { return ID; }
    void User ::addFriend(User *u)
    {
        // resize the friend array and then add another user
        // first see if the friend is already there or not
        for (int i = 0; i < friendCount; i++)
        {
            if (friends[i] == u)
            {
                std ::cout << "Friend already present \n";
                return;
            }
        }
        User **temp = new User *[friendCount + 1];
        for (int i = 0; i < friendCount; i++)
        {
            temp[i] = friends[i];
        }
        temp[friendCount] = u;
        delete[] friends;
        friends = temp;
        temp = nullptr;
        friendCount++;
        std ::cout << "Friend successfully added \n";
    }
    void User ::removeFriend(User *u)
    {
        int idx = -1;
        for (int i = 0; i < friendCount; i++)
        {
            if (friends[i] == u)
            {
                idx = i;
                break;
            }
        }
        if (idx == -1)
        {
            std ::cout << "User is not your friend\n";
            return;
        }
        User **temp = new User *[friendCount - 1];
        for (int i = 0, j = 0; j < friendCount; j++)
        {
            if (j != idx)
            {
                temp[i++] = friends[j];
            }
        }

        delete[] friends;
        friends = temp;
        temp = nullptr;
        friendCount--;

        std ::cout << "User removed from friends list \n";
    }
    void User ::addLikedPage(Page *p)
    {
        for (int i = 0; i < likedPagesCount; i++)
        {
            if (likedPages[i] == p)
            {
                std ::cout << "Page already liked \n";
                return;
            }
        }
        Page **temp = new Page *[likedPagesCount + 1];
        for (int i = 0; i < likedPagesCount; i++)
        {
            temp[i] = likedPages[i];
        }

        temp[likedPagesCount] = p;
        delete[] likedPages;
        likedPages = temp;
        temp = nullptr;
        likedPagesCount++;

        std ::cout << "Page successfully liked \n";
    }
    void User ::removeLikedPage(Page *p)
    {
        int idx = -1;
        for (int i = 0; i < likedPagesCount; i++)
        {
            if (likedPages[i] == p)
            {
                idx = i;
                break;
            }
        }
        if (idx == -1)
        {
            std ::cout << "Page is already not liked .. ";
            return;
        }
        Page **temp = new Page *[likedPagesCount - 1];
        for (int i = 0, j = 0; j < likedPagesCount; j++)
        {
            if (j != idx)
                temp[i++] = likedPages[j];
        }
        delete[] likedPages;
        likedPages = temp;
        temp = nullptr;
        likedPagesCount--;
        std ::cout << "Page unliked... " << std ::endl;
    }
    void User ::addPost(Post *p)
    {
        for (int i = 0; i < postCount; i++)
        {
            if (myPosts[i] == p)
            {
                std ::cout << "Post already present \n";
                return;
            }
        }
        Post **temp = new Post *[postCount + 1];
        for (int i = 0; i < postCount; i++)
        {
            temp[i] = myPosts[i];
        }
        temp[postCount] = p;
        delete[] myPosts;
        myPosts = temp;
        temp = nullptr;
        postCount++;
        std ::cout << "Post added successfully \n ";
    }
    void User ::removePost(Post *p)
    {
        int idx = -1;
        for (int i = 0; i < postCount; i++)
        {
            if (myPosts[i] == p)
            {
                idx = i;
                break;
            }
        }
        if (idx == -1)
        {
            std ::cout << "Page is already not liked .. ";
            return;
        }
        Post **temp = new Post *[postCount - 1];
        for (int i = 0, j = 0; j < postCount; j++)
        {
            if (j != idx)
                temp[i++] = myPosts[j];
        }
        delete[] myPosts;
        myPosts = temp;
        temp = nullptr;
        postCount--;
        std ::cout << "Post removed... " << std ::endl;
    }
    void User ::display()
    {
        std ::cout << "ID : " << ID << std ::endl
                   << "Name : " << name << std ::endl;
    }
    User ::~User()
    {
        delete[] myPosts;
        delete[] likedPages;
        delete[] friends;
    }
    User **User ::getFriends() { return friends; }
    Page **User ::getLikedPages() { return likedPages; }
    Post **User ::getMyPosts() { return myPosts; }
    int User ::getFriendCount() { return friendCount; }
    int User ::getLikedPagesCount() { return likedPagesCount; }
    int User ::getPostCount() { return postCount; }

    // functions of the class post

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
    }
    void Post ::addComment(Comment *c)
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

    void Post ::view()
    {
        if (ownerPage == nullptr)
            std ::cout << "--" << ownerUser->getName() << " shared : " << description << std ::endl;
        else
            std ::cout << "--" << ownerPage->getTitle() << " shared : " << description << std ::endl;
    }
    std ::string Post ::getID() { return ID; }
    std ::string Post ::getDesc() { return description; }
    Date Post ::getDate() { return shareDate; }
    Post ::~Post()
    {
        delete[] comments;
        delete[] usersThatLiked;
    }

    // functions of the class page
    Page :: Page (std :: string ID , std :: string title){
        this->ID = ID ;
        this->title  = title ;
    }
    std ::string Page ::getTitle() { return title; }
    std ::string Page ::getID() { return ID; }
    int Page ::getPostCount() { return postCount; }
    Post **Page ::getPosts() { return Posts; }
    void Page ::addPost(Post *p)
    {
        // first check if the post is already in the posts array or not
        for (int i = 0; i < postCount; i++)
        {
            if (Posts[i] == p)
            {
                std ::cout << "This post is already present !\n";
                return;
            }
        }
        Post **temp = new Post *[postCount + 1];
        for (int i = 0; i < postCount; i++)
        {
            temp[i] = Posts[i];
        }
        temp[postCount] = p;
        delete[] Posts;
        Posts = temp;
        temp = nullptr;
        postCount++;
        std ::cout << "Post successfully added \n";
    }
    void Page ::removePost(Post *p)
    {
        // first if the post even exists on the page
        int idx = -1;
        for (int i = 0; i < postCount; i++)
        {
            if (Posts[i] == p)
            {
                idx = i;
                break;
            }
        }
        if (idx == -1)
        {
            std ::cout << "Invaid post ";
            return;
        }
        Post **temp = new Post *[postCount - 1];
        for (int i = 0, j = 0; i < postCount; i++)
        {
            if (i != idx)
            {
                temp[j++] = Posts[i];
            }
        }
        delete[] Posts;
        Posts = temp;
        postCount--;
        std ::cout << "Post removed !\n";
    }

}
int main()
{
}