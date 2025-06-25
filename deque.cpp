//deque的手写简单版本
//deque双端队列是在内存中连续存储元素的数据结构，支持队头和队尾添加和删除元素。属于顺序容器。
//底层和vector一样是数组。


template<typename T>
class Deque{
private: 
    T* elements;
    size_t capacity;
    size_t size;
    size_t frontIndex;
    size_t backIndex;
public:
    //1.基础函数：构造、析构
    Deque(): capacity(0),size(0),elements(nullptr),frontIndex(0),backIndex(0) {}
    ~Deque(){
        clear();
        delete [] elements;//正确的，delete elements[]错误的，只会释放第一个元素，会导致内存泄漏。
    }

    //2.功能函数
    void push_back(T& value){
        if (size == capacity) resize();
        elements[backIndex] = value;
        backIndex = (backIndex + 1) % capacity;//环形队列。1.避免频繁扩容2.环形结构的关键优势：头尾操作的时间复杂度O(1),也是deque高效的关键3.内存利用率较高，不会浪费头部空间
        size ++;
    }

    void push_front(T& value){
        if (size == capacity) resize();
        elements[frontIndex] = value;
        frontIndex = (frontIndex - 1 + capacity) % capacity;
        size ++;
    }
    // deque高效的关键就在于首尾相接，比如说队头进行pop，只需让front后移一位，而不用整段数组前移。灵魂即： 真正用于构建队列的元素只有夹在头尾指针之间的元素。

    void pop_back(){
        if (size == 0) throw std::out_of_range("Deque is empty");
        backIndex = (backIndex - 1 + capacity) % capacity;
        size--;
    }
    void pop_front(){
        if (size == 0) throw std::out_of_range("Deque is empty");
        frontIndex = (frontIndex + 1) % capacity;
        size --;
    } 

    //get(),获取某个位置的元素。通过重载[]来实现。
    T& operator [](int index){
        if (size < 0 || size > capacity) throw::out_of_range("Index out of range");
        return elements[(frontIndex + index) % capacity];
    }

    size_t get_size() const{
        return size;
    }

    void clear(){
        while (size > 0) pop_front();
    }

    //resize()函数
    void resize(){
        size_t newcapacity = capacity == 0 ? 1 : capacity * 2;
        T* newelements = new T[newcapacity];

        size_t index = frontIndex;
        for (size_t i = 0;i < newcapacity;i++){
            newelements[i] = elements[index];
            index = (index + 1) % capacity;
        }

        delete [] elements;

        elements = newelements;
        capacity = newcapacity;
        frontIndex = 0;
        backIndex = size;
    }

};