#ifndef _QTYPE_H  // header guard
#define _QTYPE_H
#include <mutex>



// ==========�� ������ ���� ����==========

typedef unsigned int Key;  // ���� Ŭ���� ���� �켱����
typedef void* Value;

typedef struct {
    Key key;
    Value value;
    int value_size;  // value�� ����Ű�� �޸� ũ�� (����Ʈ ����)
} Item;

typedef struct {
    bool success;   // true: ����, false: ����
    Item item;
    // �ʵ� �߰� ����
} Reply;

typedef struct node_t {
    Item item;
    struct node_t* next;
    // �ʵ� �߰� ����
} Node;

typedef struct {
    Node* head, * tail;
    std::mutex mtx;
    // �ʵ� �߰� ����
} Queue;

// ���� �����Ӱ� �߰�/����: ���ο� �ڷ��� ���� ��

#endif
