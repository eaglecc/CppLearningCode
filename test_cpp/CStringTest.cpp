#include <cstring>
#include <iostream>

#pragma warning(disable:4996)

// 自定义字符复制函数，将src复制到dest中，返回dest
char* my_strcpy(char* dest, const char* src) {
    // 使用一个指针遍历源字符串
    char* original_dest = dest; // 保存目标字符串的起始地址

    while (*src != '\0') { // 当源字符不是结束符
        *dest = *src;       // 复制字符
        dest++;             // 移动目标指针
        src++;              // 移动源指针
    }
    *dest = '\0'; // 在目标字符串末尾添加结束符

    return original_dest; // 返回目标字符串的起始地址
}

// 自定义字符串拼接函数，将src拼接到dest后面，返回dest
char* my_strcat(char *dest, const char* src) {
    char* original_dest = dest;
    // 遍历到dest的末尾
    while (*dest != '\0') {
        dest++;
    }
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    return original_dest;
}

//int main() {
//    char str1[20] = "Hello ";
//    const char* str2 = "World";
//    //char* res = strcat(str1, str2); // 字符串拼接
//    //std::cout << "strcat字符串拼接结果：" << res << std::endl;
//
//    //strcat_s(str1, sizeof(str1), str2);
//    //std::cout << str1 << std::endl;
//
//    //strcpy(str1 + strlen(str1), str2);
//    //std::cout << "strcpy字符串复制实现拼接结果：" << str1 << std::endl;
//
//    //my_strcpy(str1 + strlen(str1), str2);
//    //std::cout << str1 << std::endl;
//
//    //my_strcat(str1, str2);
//    //std::cout << str1 << std::endl;
//
//    char msg[] = { 'a','b','c','\0' };
//    std::cout << strlen(msg) << std::endl;
//
//    return 0;
//}

