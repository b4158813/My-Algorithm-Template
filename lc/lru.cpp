struct MyListNode {
    MyListNode* prev;
    MyListNode* next;
    int key;
    int val;
    MyListNode(): prev(nullptr), next(nullptr), key(0), val(0) {}
    MyListNode(const int& key, const int& val): prev(nullptr), next(nullptr), key(key), val(val) {}
};

class LRUCache {
    MyListNode* dummyhead;
    MyListNode* dummytail;
    unordered_map<int, MyListNode*> ma;
    int m_capacity;
    int m_capacity_used;
public:
    LRUCache(int capacity) {
        m_capacity = capacity;
        m_capacity_used = 0;
        dummyhead = new MyListNode();
        dummytail = new MyListNode();
        dummyhead->next = dummytail;
        dummytail->prev = dummyhead;
    }
    
    int get(int key) {
        if(ma.find(key) == ma.end()){
            return -1;
        }
        MyListNode* u = ma[key];
        move_to_head(u);
        return u->val;
    }
    
    void put(int key, int value) {
        if(ma.find(key) != ma.end()){
            MyListNode* u = ma[key];
            u->val = value;
            move_to_head(u);
        }else {
            MyListNode* u = new MyListNode(key, value);
            add_to_head(u);
            ma[key] = u;
            m_capacity_used ++;
        }
        while(m_capacity_used > m_capacity){
            ma.erase(dummytail->prev->key);
            erase_tail();
            m_capacity_used --;
        }
    }

    void move_to_head(MyListNode* u) {
        u->prev->next = u->next;
        u->next->prev = u->prev;
        add_to_head(u);
    }

    void add_to_head(MyListNode* u) {
        u->prev = dummyhead;
        u->next = dummyhead->next;
        dummyhead->next->prev = u;
        dummyhead->next = u;
    }

    void erase_tail() {
        MyListNode* u = dummytail->prev;
        u->prev->next = dummytail;
        dummytail->prev = u->prev;
        u->prev = nullptr;
        u->next = nullptr;
        delete(u);
        u = reinterpret_cast<MyListNode*>(0x66);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */