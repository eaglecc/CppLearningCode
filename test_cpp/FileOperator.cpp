#include "FileOperator.h"
#include <fstream>

using namespace std;

int main() {
    // 2. ������ʽ����
    ofstream ofs;
    // 3. ���ļ�
    ofs.open("test.txt", ios::app);  //��û��ָ��ĳ��·��ʱ���������ļ��ڸ���Ŀ�ļ���·����
    // 4. д���ļ�
    ofs << "����������" << endl;
    ofs << "�Ա���" << endl;
    // 5. �ر��ļ�
    ofs.close();

    return 0;
}