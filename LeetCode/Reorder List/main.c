#include <stdlib.h>
#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

int getSizeNode(struct ListNode* head){
    struct ListNode *node = head;  
    int size = 0;   
    while(node != NULL){
        size++;
        node = node->next;
    }
    return size;
}

struct ListNode* getNodeByIndex(struct ListNode* head, int index){
    struct ListNode *node = head;  
    for(int i = 0; i < index; i++)
        node = node->next;
    return node;
}

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* atual = head;
    struct ListNode* prox = NULL;

    while (atual) {
        prox = atual->next;
        atual->next = prev;
        prev = atual;
        atual = prox;
    }

    return prev;
}

void reorderList(struct ListNode* head) {
    if (!head || !head->next)
        return;

    int size = getSizeNode(head);
    int mid = (size - 1) / 2;

    struct ListNode* first = head;
    struct ListNode* midNode = getNodeByIndex(head, mid);

    struct ListNode* second = midNode->next;
    midNode->next = NULL; 

    second = reverseList(second);
    while (second) {
        struct ListNode* nextSecond = second->next;
        second->next = first->next;
        first->next = second;
        first = second->next;
        second = nextSecond;
    }
}

void printAll(struct ListNode* head){
    struct ListNode *node = head;  
    int size = 0;   
    while(node != NULL){
        printf("node: %d val: %d\n", size, node->val);
        size++;
        node = node->next;
    }
}

int main(){
    struct ListNode *node1 = malloc(sizeof(struct ListNode));
    struct ListNode *node2 = malloc(sizeof(struct ListNode));
    struct ListNode *node3 = malloc(sizeof(struct ListNode));
    struct ListNode *node4 = malloc(sizeof(struct ListNode));
    struct ListNode *node5 = malloc(sizeof(struct ListNode));

    node1->val = 1;
    node2->val = 2;
    node3->val = 3;
    node4->val = 4;
    node5->val = 5;

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = NULL;

    printAll(node1);
    reorderList(node1);
    printAll(node1);

    return 0;
}