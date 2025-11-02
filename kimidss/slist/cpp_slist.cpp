#pragma once
#include <cstdlib>
#include <initializer_list>
#include <iterator>

typedef int ElemType;

class List {
    struct Node {
        ElemType data;
        Node *prev, *next;
        explicit Node(ElemType d = ElemType{}) : data(d), prev(nullptr), next(nullptr) {}
    };
    Node *head_;   // 哨兵
    Node *tail_;   // 尾结点
    int  len_;

    /* 工具函数 */
    Node *alloc(ElemType e) { return new Node(e); }
    void  dealloc(Node *p) { delete p; }
    void  hook(Node *pos, Node *p) { // 把 p 插到 pos 前
        p->next = pos;
        p->prev = pos->prev;
        pos->prev->next = p;
        pos->prev = p;
        ++len_;
    }
    void  unhook(Node *p) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        if (p == tail_) tail_ = p->prev;
        --len_;
    }
public:
    List() {
        head_ = new Node;
        head_->prev = head_->next = head_;
        tail_ = head_;
        len_  = 0;
    }
    ~List() { clear(); delete head_; }

    /* 拷贝构造 / 赋值 省略，可自行补充 */

    void clear() {
        Node *p = head_->next;
        while (p != head_) {
            Node *nxt = p->next;
            dealloc(p);
            p = nxt;
        }
        head_->next = head_->prev = head_;
        tail_ = head_;
        len_ = 0;
    }
    int  size()  const { return len_; }
    bool empty() const { return len_ == 0; }

    /* 插入 */
    void push_front(ElemType e) { hook(head_->next, alloc(e)); if (tail_ == head_) tail_ = head_->next; }
    void push_back (ElemType e) { hook(head_, alloc(e)); tail_ = head_->prev; }
    void insert(int pos, ElemType e) {
        if (pos < 0 || pos > len_) return;
        if (pos == 0) { push_front(e); return; }
        if (pos == len_) { push_back(e); return; }
        Node *p = head_->next;
        for (int i = 0; i < pos; ++i) p = p->next;
        hook(p, alloc(e));
    }

    /* 删除 */
    bool pop_front(ElemType *out = nullptr) {
        if (empty()) return false;
        Node *p = head_->next;
        if (out) *out = p->data;
        unhook(p);
        dealloc(p);
        return true;
    }
    bool pop_back(ElemType *out = nullptr) {
        if (empty()) return false;
        Node *p = tail_;
        if (out) *out = p->data;
        unhook(p);
        dealloc(p);
        return true;
    }
    bool erase_pos(int pos, ElemType *out = nullptr) {
        if (pos < 0 || pos >= len_) return false;
        Node *p = head_->next;
        for (int i = 0; i < pos; ++i) p = p->next;
        if (out) *out = p->data;
        unhook(p);
        dealloc(p);
        return true;
    }
    int  erase_val(ElemType e) {
        int cnt = 0;
        Node *p = head_->next;
        while (p != head_) {
            Node *nxt = p->next;
            if (p->data == e) {
                unhook(p);
                dealloc(p);
                ++cnt;
            }
            p = nxt;
        }
        return cnt;
    }

    /* 功能 */
    void reverse() {
        if (len_ <= 1) return;
        Node *p = head_;
        do {
            std::swap(p->prev, p->next);
            p = p->prev;          // 因为已经交换，原 next 现在在 prev
        } while (p != head_);
        std::swap(head_, tail_);
    }
    void sort();  // 定义在下面

    /* 简易迭代器，支持范围 for */
    struct iterator : std::iterator<std::bidirectional_iterator_tag, ElemType> {
        Node *p_;
        explicit iterator(Node *n) : p_(n) {}
        ElemType& operator*()  const { return p_->data; }
        iterator& operator++()       { p_ = p_->next; return *this; }
        iterator& operator--()       { p_ = p_->prev; return *this; }
        bool operator!=(const iterator &o) const { return p_ != o.p_; }
    };
    iterator begin() { return iterator(head_->next); }
    iterator end()   { return iterator(head_); }

    void print() const {
        printf("List[%d]: ", len_);
        for (Node *p = head_->next; p != head_; p = p->next)
            printf("%d ", p->data);
        puts("");
    }
};

/* 插入排序，升序 */
inline void List::sort() {
    if (len_ <= 1) return;
    Node *sorted_tail = head_->next;
    while (sorted_tail != tail_) {
        Node *cur = sorted_tail->next;
        if (cur->data >= sorted_tail->data) {
            sorted_tail = cur;
            continue;
        }
        /* 摘下 cur */
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        if (cur == tail_) tail_ = cur->prev;
        --len_;
        /* 找插入位置 */
        Node *pos = head_->next;
        while (pos != sorted_tail->next && pos->data < cur->data)
            pos = pos->next;
        /* 插入 */
        hook(pos, cur);
        if (pos == head_->next) head_->next = cur;
    }
}
int main()
{
    List lst;
    for (int i = 1; i <= 5; ++i) lst.push_back(i);
    lst.print();          // 1 2 3 4 5

    lst.push_front(0);
    lst.print();          // 0 1 2 3 4 5

    int x;
    lst.pop_back(&x);
    printf("pop back %d\n", x);

    lst.insert(3, 99);
    lst.print();          // 0 1 2 99 3 4

    lst.erase_val(2);
    lst.print();          // 0 1 99 3 4

    lst.reverse();
    lst.print();          // 4 3 99 1 0

    lst.sort();
    lst.print();          // 0 1 3 4 99

    /* 范围 for 遍历 */
    for (auto v : lst) printf("%d ", v);
    puts("");
    return 0;
}