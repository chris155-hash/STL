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

    void push_front(const T& val){
        Node* temp = new Node(val,head,nullptr);
        if (head) head->prev = temp;
        else tail = temp;
        head = temp;
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

    void pop_front(const T& val){
        if (current_size > 0){ 
            Node* temp = head->next;
            delete(head);
            head = temp;

            if (head) head->prev = nullptr;    //这里和上面一样，是为了处理删除掉 头/尾 节点以后，List为空但是另一端还没有处理的情况。所以要让另一端也为nullptr，
            else tail = nullptr;               //否则，可能会出现指针越界的情况。
            current_size --;
        }
    }

    int size() {
        return current_size();
    }

    //clear()函数，这里不同于vector，要考虑到节点占用的内存，所以需要循环释放。
    void clear(){
        whiel (head){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        current_size = 0;
    }

    //get()函数，访问特定位置的元素。但实际上是重载"[]"运算符。这样就可以很方便地访问特地元素。
    //这里返回值设置为引用传递，是有时候List[2] = 4这种情况，需要修改Index的data
    T& operator[](size_t index){
        Node* cur = head;
        for (size_t i = 0;i < index;i++){
            if (!cur) throw std::out_of_range("Index out of range!");
            cur = cur->next;
        }
        return cur->data;
    }
    //这里再写一个const版本的和之前vector里的一样，外面的const修饰的对象只能访问const的成员函数，所以提供const版本
    T& operator[](size_t index) const {
        Node* cur = head;
        for (size_t i = 0;i < index;i++){
            if (!cur) throw std::out_of_range("Index out of range!");
            cur = cur->next;
        }
        return cur->data;
    }

    //remove()函数，删除某个节点。这里需要先查找到这个节点，还要注意处理它是头尾节点的特殊情况。
    void remove(const T& val){
        Node* temp = head;
        while (temp && temp->data != val){
            temp = temp->next;
        }
        if (!temp) return;
        if (temp != head && temp != tail){
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        else if (temp == head && temp == tail){
            head = nullptr;
            tail = nullptr;
        }
        else if (temp == head){
            head = temp->next;
            head->prev = nullptr;
        }
        else {
            tail = temp->prev;
            tail->next = nullptr;
        }
        current_size --;
        delete temp;
        temp = nullptr;
    }

    //find()函数：在list中查找第一个值等于 val 的节点，并返回指向该节点中存储数据 (data) 的指针。如果未找到匹配节点，则返回 nullptr。
    Node* getNode(const T & val){
        Node* node = head;
        while (node && node->data != val) node = node->next;
        return node;
    }
    T* find(const T & val){
        Node* node = getNode(val);
        if (!node) return nullptr;
        return & node->data;              //返回的是T*的指针，举例  int* result = find(20);那么result指向list里20这个data的地址，*result为20
    }

    bool empty(){
        return current_size == 0;
    }

    //3.其他功能编写
    //（1）迭代器
    Node* begin(){return head;}
    Node* end(){return tail;}
    const Node* begin() const {return head;}
    const Node* end() const {return tail;}

    //(2)重载<< 符号
    template <typename T>
    std::ostream &operator<<(std::ostream & os,ryylist<T> & pt){
        for (auto current = pt.begin();current;current = current->next){
            os << " " << current->data;
        }
        os << std::endl;
        return os;
    }

    //如果不重载 << 运算符，那么直接使用 std::cout << ; 将无法正常工作，编译器会报错。
    //C++ 标准库中的 std::ostream（如 std::cout）没有为你的自定义类型 ryylist<T> 提供默认的输出方式。
    //如果不重载 <<，你只能这样打印链表内容：手动编写一个打印函数.想向力扣链表题的ACM模式。
};

