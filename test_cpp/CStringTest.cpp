#include <cstring>
#include <iostream>

#pragma warning(disable:4996)

// �Զ����ַ����ƺ�������src���Ƶ�dest�У�����dest
char* my_strcpy(char* dest, const char* src) {
    // ʹ��һ��ָ�����Դ�ַ���
    char* original_dest = dest; // ����Ŀ���ַ�������ʼ��ַ

    while (*src != '\0') { // ��Դ�ַ����ǽ�����
        *dest = *src;       // �����ַ�
        dest++;             // �ƶ�Ŀ��ָ��
        src++;              // �ƶ�Դָ��
    }
    *dest = '\0'; // ��Ŀ���ַ���ĩβ��ӽ�����

    return original_dest; // ����Ŀ���ַ�������ʼ��ַ
}

// �Զ����ַ���ƴ�Ӻ�������srcƴ�ӵ�dest���棬����dest
char* my_strcat(char *dest, const char* src) {
    char* original_dest = dest;
    // ������dest��ĩβ
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
//    //char* res = strcat(str1, str2); // �ַ���ƴ��
//    //std::cout << "strcat�ַ���ƴ�ӽ����" << res << std::endl;
//
//    //strcat_s(str1, sizeof(str1), str2);
//    //std::cout << str1 << std::endl;
//
//    //strcpy(str1 + strlen(str1), str2);
//    //std::cout << "strcpy�ַ�������ʵ��ƴ�ӽ����" << str1 << std::endl;
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

