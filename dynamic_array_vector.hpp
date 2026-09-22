#include <iostream>
#include <stdexcept>
#include <vector>

using std::cout;
using std::endl;
using std::out_of_range;
using std::vector;

// 这个类本质上是一个“动态数组列表”，底层使用 std::vector<E> 作为存储结构。
// 它保留了和 Java ArrayList 相近的接口风格：add / remove / get / set。
// 这样做的好处是：不用自己手动管理内存，自动处理扩容/缩容。
template<typename E>
class MyArrayList {
private:
    // data 就相当于原来手写数组的底层容器。
    // vector 会自动管理内存，内部支持动态扩容。
    vector<E> data;

public:
    // 默认构造：不设初始容量，vector 会自己决定。
    MyArrayList() = default;

    // 带初始容量的构造：先预留空间，避免频繁扩容。
    // 这里的 reserve() 是 vector 的“预分配”接口。
    // 作用相当于：提前让底层数组有 initCapacity 的空间。
    explicit MyArrayList(int initCapacity) {
        if (initCapacity < 0) {
            throw out_of_range("Illegal Capacity");
        }
        data.reserve(initCapacity);
    }

    // 增：在尾部追加元素
    // vector::push_back(e) 相当于数组尾部插入。
    void addLast(E e) {
        data.push_back(e);
    }

    // 在指定位置插入元素
    // vector::insert(begin + index, e) 会把元素插入到指定位置，后面的元素自动后移。
    void add(int index, E e) {
        checkPositionIndex(index); // 先检查索引是否合法：0 <= index <= size
        data.insert(data.begin() + index, e);
    }

    // 在头部插入元素
    void addFirst(E e) {
        add(0, e);
    }

    // 删：删除尾部元素
    // vector::pop_back() 删除最后一个元素。
    E removeLast() {
        if (data.empty()) {
            throw out_of_range("NoSuchElementException");
        }

        E deletedVal = data.back(); // 先保存最后一个值
        data.pop_back();            // 再真正删除它
        return deletedVal;
    }

    // 删除指定位置的元素
    // vector::erase(begin + index) 会删除指定位置元素，并把后面的元素前移。
    E remove(int index) {
        checkElementIndex(index); // 只允许 0 <= index < size

        E deletedVal = data[index];
        data.erase(data.begin() + index);
        return deletedVal;
    }

    // 删除头部元素
    E removeFirst() {
        return remove(0);
    }

    // 查：获取指定位置元素
    // vector[index] 直接按下标访问，速度很快。
    E get(int index) const {
        checkElementIndex(index);
        return data[index];
    }

    // 改：修改指定位置元素，并返回旧值
    E set(int index, E element) {
        checkElementIndex(index);
        E oldVal = data[index];
        data[index] = element;
        return oldVal;
    }

    // 工具方法
    // 获取当前元素个数：vector::size()
    int getSize() const {
        return static_cast<int>(data.size());
    }

    // 判断是否为空：vector::empty()
    bool isEmpty() const {
        return data.empty();
    }

    // 打印当前状态
    // size 表示元素个数，capacity 表示当前内部容量
    void display() const {
        cout << "size = " << data.size() << " cap = " << data.capacity() << endl;
        for (size_t i = 0; i < data.size(); ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

private:
    // 检查 index 是否可以表示“已存在元素的位置”
    // 合法区间：0 <= index < size
    bool isElementIndex(int index) const {
        return index >= 0 && index < static_cast<int>(data.size());
    }

    // 检查 index 是否可以表示“插入位置”
    // 合法区间：0 <= index <= size
    // 因为插入时可以插在末尾位置，也就是 size 这个位置。
    bool isPositionIndex(int index) const {
        return index >= 0 && index <= static_cast<int>(data.size());
    }

    // 若 index 不合法，抛出越界异常。
    void checkElementIndex(int index) const {
        if (!isElementIndex(index)) {
            throw out_of_range("Index out of bounds");
        }
    }

    // 若插入位置不合法，抛出越界异常。
    void checkPositionIndex(int index) const {
        if (!isPositionIndex(index)) {
            throw out_of_range("Index out of bounds");
        }
    }
};

// ------------------------- 示例测试 -------------------------
int main() {
    // 这里的 initCapacity 只是预留空间，并不强制内部容量等于 3。
    // vector 可能会分配更多一些空间，但对使用者来说是透明的。
    MyArrayList<int> arr(3);

    // 测试尾插：1 2 3 4 5
    for (int i = 1; i <= 5; ++i) {
        arr.addLast(i);
    }

    // 删除位置 3 的元素（0-based）
    arr.remove(3);

    // 在位置 1 插入 9
    arr.add(1, 9);

    // 在头部插入 100
    arr.addFirst(100);

    // 删除尾部元素，并保存返回值
    int val = arr.removeLast();

    // 打印最终结果
    for (int i = 0; i < arr.getSize(); ++i) {
        std::cout << arr.get(i) << std::endl;
    }

    std::cout << "removed last = " << val << std::endl;
    return 0;
}
