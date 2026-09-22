#include <iostream>
#include <stdexcept>
#include <vector>

// 更接近 STL 容器风格的版本：
// - 底层容器仍然是 std::vector<E>
// - 提供 begin/end、size/empty、operator[]、at
// - 同时保留 addLast / add / remove 等 Java 风格接口，方便练习
// - 这个版本更像“标准库容器”，更适合学习 C++ 容器设计思想

using std::out_of_range;
using std::vector;

template<typename E>
class MyArrayList {
private:
    vector<E> data;

public:
    // 默认构造：不指定初始容量
    MyArrayList() = default;

    // 指定最小容量预留
    explicit MyArrayList(int initCapacity) {
        if (initCapacity < 0) {
            throw out_of_range("Illegal Capacity");
        }
        data.reserve(static_cast<size_t>(initCapacity));
    }

    // 迭代器接口：像 STL 容器一样支持 begin/end
    using iterator = typename vector<E>::iterator;
    using const_iterator = typename vector<E>::const_iterator;

    iterator begin() { return data.begin(); }
    iterator end() { return data.end(); }
    const_iterator begin() const { return data.begin(); }
    const_iterator end() const { return data.end(); }
    const_iterator cbegin() const { return data.cbegin(); }
    const_iterator cend() const { return data.cend(); }

    // 容器大小接口：size()、empty()
    size_t size() const noexcept { return data.size(); }
    bool empty() const noexcept { return data.empty(); }

    // 预留空间：类似动态数组扩容前的准备工作
    void reserve(size_t newCapacity) {
        data.reserve(newCapacity);
    }

    // 返回当前容量
    size_t capacity() const noexcept {
        return data.capacity();
    }

    // 清空容器
    void clear() noexcept {
        data.clear();
    }

    // ------------------------- Java 风格接口 -------------------------
    // addLast：尾部追加元素
    void addLast(const E& e) {
        data.push_back(e);
    }

    void addLast(E&& e) {
        data.push_back(std::move(e));
    }

    // add：插入到指定位置
    void add(int index, const E& e) {
        checkPositionIndex(index);
        data.insert(data.begin() + index, e);
    }

    void add(int index, E&& e) {
        checkPositionIndex(index);
        data.insert(data.begin() + index, std::move(e));
    }

    void addFirst(const E& e) {
        add(0, e);
    }

    void addFirst(E&& e) {
        add(0, std::move(e));
    }

    // removeLast：删除最后一个元素并返回它
    E removeLast() {
        if (data.empty()) {
            throw out_of_range("NoSuchElementException");
        }

        E last = data.back();
        data.pop_back();
        return last;
    }

    // remove：删除 index 位置元素，并返回它
    E remove(int index) {
        checkElementIndex(index);

        E value = data[static_cast<size_t>(index)];
        data.erase(data.begin() + index);
        return value;
    }

    E removeFirst() {
        return remove(0);
    }

    // get：获取 index 位置元素
    E get(int index) const {
        return at(index);
    }

    // set：修改元素并返回旧值
    E set(int index, const E& element) {
        checkElementIndex(index);
        E oldVal = data[static_cast<size_t>(index)];
        data[static_cast<size_t>(index)] = element;
        return oldVal;
    }

    // ------------------------- STL 风格接口 -------------------------
    // operator[]：更像 C++ 数组访问
    E& operator[](size_t index) {
        return data[index];
    }

    const E& operator[](size_t index) const {
        return data[index];
    }

    // at()：带边界检查的访问方式
    E& at(size_t index) {
        if (index >= data.size()) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    const E& at(size_t index) const {
        if (index >= data.size()) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // front/back：返回第一个/最后一个元素
    E& front() {
        if (data.empty()) {
            throw out_of_range("Container is empty");
        }
        return data.front();
    }

    const E& front() const {
        if (data.empty()) {
            throw out_of_range("Container is empty");
        }
        return data.front();
    }

    E& back() {
        if (data.empty()) {
            throw out_of_range("Container is empty");
        }
        return data.back();
    }

    const E& back() const {
        if (data.empty()) {
            throw out_of_range("Container is empty");
        }
        return data.back();
    }

    // push_back：STL 风格尾插
    void push_back(const E& e) {
        data.push_back(e);
    }

    void push_back(E&& e) {
        data.push_back(std::move(e));
    }

    // emplace_back：直接构造元素，减少拷贝
    template<typename... Args>
    E& emplace_back(Args&&... args) {
        data.emplace_back(std::forward<Args>(args)...);
        return data.back();
    }

    // insert：STL 风格插入
    iterator insert(iterator pos, const E& value) {
        return data.insert(pos, value);
    }

    iterator insert(iterator pos, E&& value) {
        return data.insert(pos, std::move(value));
    }

    // erase：删除指定位置或区间
    iterator erase(iterator pos) {
        return data.erase(pos);
    }

    iterator erase(iterator first, iterator last) {
        return data.erase(first, last);
    }

    // 兼容旧接口：getSize / isEmpty / display
    int getSize() const {
        return static_cast<int>(data.size());
    }

    bool isEmpty() const {
        return data.empty();
    }

    void display() const {
        std::cout << "size = " << data.size() << " capacity = " << data.capacity() << std::endl;
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    // 仅对 Java 风格接口使用的检查函数
    bool isElementIndex(int index) const {
        return index >= 0 && index < static_cast<int>(data.size());
    }

    bool isPositionIndex(int index) const {
        return index >= 0 && index <= static_cast<int>(data.size());
    }

    void checkElementIndex(int index) const {
        if (!isElementIndex(index)) {
            throw out_of_range("Index out of bounds");
        }
    }

    void checkPositionIndex(int index) const {
        if (!isPositionIndex(index)) {
            throw out_of_range("Index out of bounds");
        }
    }
};

int main() {
    MyArrayList<int> arr(3);

    // 1. 添加元素
    arr.addLast(1);
    arr.addLast(2);
    arr.addLast(3);
    arr.addLast(4);
    arr.addLast(5);

    // 2. 在指定位置插入
    arr.add(1, 99);

    // 3. 头插
    arr.addFirst(100);

    // 4. 删除元素
    int removed = arr.remove(2);

    // 5. STL 风格访问
    std::cout << "arr[0] = " << arr[0] << std::endl;
    std::cout << "at(1) = " << arr.at(1) << std::endl;
    std::cout << "front = " << arr.front() << std::endl;
    std::cout << "back = " << arr.back() << std::endl;
    std::cout << "removed = " << removed << std::endl;

    // 6. 遍历：STL 风格
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    arr.display();
    return 0;
}
