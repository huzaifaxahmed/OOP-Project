#include <iostream>
#include "headers.h"
using namespace dHeader;

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