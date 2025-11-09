#ifndef CRTP_DEMO_H
#define CRTP_DEMO_H

#include <iostream>
#include <type_traits>

// 演示CRTP (奇异递归模板模式)
namespace crtp_demo {
    // CRTP基类模板
    template<typename Derived>
    class Comparable {
    public:
        // 实现相等比较运算符
        bool operator==(const Comparable& other) const {
            const Derived& derived = static_cast<const Derived&>(*this);
            const Derived& other_derived = static_cast<const Derived&>(other);
            return derived.equal(other_derived);
        }

        // 实现小于比较运算符
        bool operator<(const Comparable& other) const {
            const Derived& derived = static_cast<const Derived&>(*this);
            const Derived& other_derived = static_cast<const Derived&>(other);
            return derived.less_than(other_derived);
        }

        // 基于上面的实现，自动获得其他比较运算符
        bool operator!=(const Comparable& other) const {
            return !(*this == other);
        }

        bool operator<=(const Comparable& other) const {
            return !(other < *this);
        }

        bool operator>(const Comparable& other) const {
            return other < *this;
        }

        bool operator>=(const Comparable& other) const {
            return !(*this < other);
        }
    };

    // 使用CRTP的示例类 - 整数包装类
    class IntWrapper : public Comparable<IntWrapper> {
    private:
        int value_;

    public:
        explicit IntWrapper(int value) : value_(value) {}

        // 实现CRTP需要的接口
        bool equal(const IntWrapper& other) const {
            return value_ == other.value_;
        }

        bool less_than(const IntWrapper& other) const {
            return value_ < other.value_;
        }

        int getValue() const {
            return value_;
        }
    };

    // 使用CRTP的另一个示例类 - 字符串包装类
    class StringWrapper : public Comparable<StringWrapper> {
    private:
        std::string value_;

    public:
        explicit StringWrapper(const std::string& value) : value_(value) {}

        // 实现CRTP需要的接口
        bool equal(const StringWrapper& other) const {
            return value_ == other.value_;
        }

        bool less_than(const StringWrapper& other) const {
            return value_ < other.value_;
        }

        const std::string& getValue() const {
            return value_;
        }
    };

    // CRTP用于对象计数
    template<typename Derived>
    class ObjectCounter {
    private:
        static size_t count_;

    public:
        ObjectCounter() {
            ++count_;
        }

        ObjectCounter(const ObjectCounter&) {
            ++count_;
        }

        ~ObjectCounter() {
            --count_;
        }

        static size_t getCount() {
            return count_;
        }
    };

    // 初始化静态成员
    template<typename Derived>
    size_t ObjectCounter<Derived>::count_ = 0;

    // 使用对象计数CRTP的类
    class CountedClass : public ObjectCounter<CountedClass> {
    private:
        int value_;

    public:
        explicit CountedClass(int value) : value_(value) {}
        
        int getValue() const {
            return value_;
        }
    };

    // CRTP用于静态多态
    template<typename Derived>
    class Shape {
    public:
        // 静态多态 - 在编译时确定具体类型
        double area() const {
            const Derived& derived = static_cast<const Derived&>(*this);
            return derived.area_impl();
        }

        void draw() const {
            const Derived& derived = static_cast<const Derived&>(*this);
            derived.draw_impl();
        }
    };

    // 具体的形状类
    class Circle : public Shape<Circle> {
    private:
        double radius_;

    public:
        explicit Circle(double radius) : radius_(radius) {}

        // 实现面积计算
        double area_impl() const {
            return 3.14159 * radius_ * radius_;
        }

        // 实现绘制方法
        void draw_impl() const {
            std::cout << "绘制一个半径为 " << radius_ << " 的圆" << std::endl;
        }
    };

    class Rectangle : public Shape<Rectangle> {
    private:
        double width_, height_;

    public:
        Rectangle(double width, double height) : width_(width), height_(height) {}

        // 实现面积计算
        double area_impl() const {
            return width_ * height_;
        }

        // 实现绘制方法
        void draw_impl() const {
            std::cout << "绘制一个 " << width_ << "x" << height_ << " 的矩形" << std::endl;
        }
    };
    
    // 运行crtp演示
    inline void run_meta_programming_demo() {
        std::cout << "\n1.7 CRTP演示:" << std::endl;
        
        // CRTP比较示例
        std::cout << "CRTP比较示例:" << std::endl;
        IntWrapper int1(10);
        IntWrapper int2(20);
        
        std::cout << "int1(10) == int2(20): " << std::boolalpha << (int1 == int2) << std::endl;
        std::cout << "int1(10) < int2(20): " << std::boolalpha << (int1 < int2) << std::endl;
        std::cout << "int1(10) > int2(20): " << std::boolalpha << (int1 > int2) << std::endl;
        
        StringWrapper str1("hello");
        StringWrapper str2("world");
        
        std::cout << "str1(\"hello\") == str2(\"world\"): " << std::boolalpha << (str1 == str2) << std::endl;
        std::cout << "str1(\"hello\") < str2(\"world\"): " << std::boolalpha << (str1 < str2) << std::endl;
        
        // CRTP对象计数示例
        std::cout << "\nCRTP对象计数示例:" << std::endl;
        std::cout << "创建对象前计数: " << CountedClass::getCount() << std::endl;
        
        {
            CountedClass obj1(1);
            CountedClass obj2(2);
            CountedClass obj3(3);
            std::cout << "创建3个对象后计数: " << CountedClass::getCount() << std::endl;
        }
        
        std::cout << "离开作用域后计数: " << CountedClass::getCount() << std::endl;
        
        // CRTP静态多态示例
        std::cout << "\nCRTP静态多态示例:" << std::endl;
        Circle circle(5.0);
        Rectangle rectangle(4.0, 6.0);
        
        circle.draw();
        std::cout << "圆的面积: " << circle.area() << std::endl;
        
        rectangle.draw();
        std::cout << "矩形的面积: " << rectangle.area() << std::endl;
    }
}

#endif // CRTP_DEMO_H