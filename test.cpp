#include <iostream>
using namespace std;

struct node {
    int value;
    node* next;
};

node* init_node(int num) {
    node* ret = new node;
    ret-> value = num;
    return ret;
}

node* odds(int n, node* next) {
    node* item = init_node(n*2-1);
    item->next = next;
    if (n > 1) {
        node* ret = odds(n-1, item);
        cout << ret -> value << endl;
        return ret;
    } else {
        return item;
    }
}