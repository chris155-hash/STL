//vector是一个动态数组，可以存储任意类型的数据，在内存中以连续的块存储内存，与静态数组相比，允许动态扩容，无需手动管理内存。
//但是，vector的访问速度比静态数组慢，因为vector的访问需要检查数组边界，而静态数组的访问不需要检查数组边界。

//vector应该具有哪些函数？
//1.基础成员函数
//构造函数： 初始化Vector
//析构函数：自动释放Vector的内存资源，运行结束后摧毁Vector，防止内存泄漏
//拷贝构造函数： 允许Vector从其他Vector创建新的Vector
//拷贝赋值运算符： 允许多个Vector相互赋值
//2.核心功能函数： push_back（）添加元素到Vector末尾、、pop_back()删除Vector末尾的元素、、 size() 计算Vector的元素个数、、
//insert（） 向Vector某处插入元素、、get（） 访问Vector某处的元素、、 clear（） 清空Vector的元素

//基础成员函数的编写
//一个Vector 有 指向他自己的指针、容量大小、 当前大小三个元素
template <typename T>    //泛型编程，后续的函数或类可以使用T作为占位符，根据实际传入的类型生成对应的代码。
class ryyvector{
private:
    T * elements;
    size_t capacity;
    size_t current_size
public:
    ryyVector(): elements(nullptr);capacity(0);current_size(0);{}
    ~ryyvector(){delete [] elements;}
    ryyvector(const ryyvector & other): capacity(other.capacity),current_size(other.current_size){
        elements = new T[capacity];    //因为elements不是一个真实的数组，而是指针，所以要创还能数组来进行复制
        std::copy(other.elements,other.elements + current_size,elements);  //copy(1,2,3),1是复制目标的起点，2是复制目标的终点，3是对象的起点
    }
    //这里拷贝赋值运算符和拷贝构造函数很像，但是要先删除elements指针，防止内存泄漏。因为拷贝构造会由析构函数释放，而拷贝赋值运算符不会。
    //因为析构和拷贝不能像普通函数一样直接被调用，而是根据对象的生命周期进行自动调用。
    ryyvector &operator = (const ryyvector & other){
        if (this != other){
            delete [] elements;
            capacity = other.capacity;
            current_size = other.current_size;
            elements = new T[capacity];
            std::copy(other.elements,other.elements + current_size,elements);
        }
    }

    //1.push_back()函数，首先要写一个分配内存的函数。不然根本没办法进行插入
    void reserve(size_t newCapacity){
        if (newCapacity > capacity){
            T* newElements = new T[newCapacity];
            std::copy(elements,elements + current_size,newElements);
            delete [] elements;
            elements = newElements;
            capacity = newCapacity;
        }
    }
    void push_back(const & input){
        if (current_size == capacity){
            capacity ? reserve(capacity * 2) : reserve(1);
        }
        elements[current_size++] = input;
    }

    //2. size()函数: 返回当前vector元素个数
    size_t size(){
        return current_size;
    }

    //3. get()函数 访问vector元素，这里仿写c++库的vector，希望实现通过vector[i]来访问i处的元素
    T & operator[] (size_t i){
        if (i > current_size) std::cout << "Index out of range" << std::endl;
        return elements[i];
    }
    const T &[] (size_t i) const {
        if (i > current_size) std::cout << "Index out of range" << std::endl;
        return elements[i];
    }
    //这里之所以要多写一种const的版本，是因为有时候vector会被const修饰，这时候操作符也要有const属性。

    //4. pop_back()函数：删除vector的最后一个元素。并不是真正释放内存，只是将current_size减1
    //这样做的原因1.避免频繁释放和分配内存。2.下次添加元素会直接覆盖，所以这种逻辑上的删除就足够了。3.后需要添加元素不用再分配内存，保持当前容量以提高效率。
    void pop_back(){
        if (current_size) current_size
    }

    //5.insert()函数：在指定位置插入元素。
    void insert(const size_t input,const T& value){
        //1.超出capacity要返回错误 2.数组已经满了要扩容 3.正常后移其他元素，插入新元素
        if (input > current_size) throw std::cout << "error: input out of capacity" << std::endl;
        if (input == current_size) reserve(current_size ? current_size * 2 : 1)
        for (size_t i = current_size;i > input ;i--){
            elements[i] = elements[i - 1];     //因为初始下标从0就开始，所以这是移动input及后面的元素
        }
        elements[input] = value;
        current_size++;
    }

    //6.clear函数：清空vector
    void clear{
        current_size = 0;
    }
};
