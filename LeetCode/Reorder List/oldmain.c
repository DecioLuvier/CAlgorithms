#include <stdlib.h>
#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* getNodeByIndex(int index, struct ListNode* head){
    struct ListNode *node = head;  
    int size = 0;
    while(node->next != NULL){
        if(size == index)
            break;
        node = node->next;
        size++;
    }
    return node;
}

void swapNodeIndex(int a, int b, struct ListNode* head){
    struct ListNode *nodeA = getNodeByIndex(a, head);
    struct ListNode *preA = getNodeByIndex(a - 1, head);
    struct ListNode *posA = getNodeByIndex(a + 1, head);
    struct ListNode *nodeB = getNodeByIndex(b, head);
    struct ListNode *preB = getNodeByIndex(b - 1, head);
    struct ListNode *posB = getNodeByIndex(b + 1, head);

    *preA->next = *nodeB;
    *preB->next = *nodeA;
    *nodeA->next = *posB;
    *nodeB->next = *posA;
}

void reorderList(struct ListNode* head) {
    struct ListNode *node = head;  
    int size = 0;
    while(node != NULL){
        node = node->next;
        size++;
    }
    for(int i = 0; i < size; i++){
        swapNodeIndex(i, size - i, head);
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

    
    return 0;
}