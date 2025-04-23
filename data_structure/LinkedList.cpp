#include <stdio.h>
#include <string>
#include <iostream>
#define MAXLEN 500

//////////////////////////////////////////////////////////////////
class ListNode{
public:
    ListNode();
    struct ListNode* next;
    struct ListNode* pre;
    size_t getData(std::string src);
    char* get_data();
private:
    char data[MAXLEN + 1];
};

ListNode::ListNode()
{
    next = NULL;
    pre = NULL;
}

size_t ListNode::getData(std::string src)
{
    size_t len = src.length();
    size_t cnt;
    for (cnt = 0; cnt < len && cnt < MAXLEN; cnt ++){
        data[cnt] = src[cnt];
    }
    data[cnt] = 0;
    return cnt;
}

char* ListNode::get_data()
{
	return data;
}

///////////////////////////////////////////////////////////////////

class LinkedList{
public:
	LinkedList();
    struct ListNode* head;
    int len;
};
///////////////////////////////////////////////////////////////////
int main()
{
    ListNode& Node_r = * new ListNode();
    std::cout <<  Node_r.getData("hello?") << std::endl;
    std::cout <<  Node_r.get_data();
    return 0;
}