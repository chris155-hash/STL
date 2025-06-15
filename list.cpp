//手写简化版本的的STL里的list    基于双向链表的数据结构
//List与基于数组的std::vector相比不同，插入和删除的时间复杂度都为O(1)，效率更高，所以更适用于频繁插入和删除的操作。

//Listing具有的函数等：
//1、基本成员函数： 构造函数：初始化List节点；析构函数：结束后释放资源，防止内存泄漏。    
//为什么不需要拷贝构造、拷贝构造运算符？：list一般不需要去拷贝新的list，所以不需要特地写。
// 2.成员函数： push_back/push_front、pop_back/pop_front、empty、clear、size、find、remove、get
// 3。其他功能： 迭代器、重载输出符等


// 1.基础成员函数的编写
template<typename T>
class ryylist{
private:
public:
    // 定义链表节点的结构体，有三个关键成员，节点值，后继指针，前驱指针
    struct Node{
        T data;
        Node* next;
        Node* prev;
        Node(const T & data_,Node* next_ = nullptr,Node* prev_ = nullptr)  //接收传参，构造函数
        :data(data_),next(next_),prev(prev_){}
    };

    Node* head;
    Node* tail;
    size_t current_size;
public:
    ryylist() : head(nullptr),tail(nullptr),current_size(0){};
    ~ryylist() {clear();};

    // 2、核心功能函数的编写
    void push_back(const T& val){
        Node* temp = new Node(val,nullptr,tail);
        if (tail) tail->next = temp;//list不为空
        else head = temp;//list为空
        
        tail = temp;
        current_size++;
    }
    void pop_back(const T& val){
        if (current_size > 0){
            Node* temp = tail->prev;
            delete tail;
            tail = temp;

            if (tail) tail->next = nullptr;
            else head = nullptr;// 如果尾节点为空，说明链表已经为空，将头节点也设置为nullptr
            current_size--;
        }
    }
};

