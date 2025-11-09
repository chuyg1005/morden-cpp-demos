#ifndef CRTP_DEMO_H
#define CRTP_DEMO_H

#include "crtp_base.h"

// 运行crtp演示
namespace crtp_demo {
    inline void run_demo() {
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