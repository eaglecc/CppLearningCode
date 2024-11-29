#include "FileOperator.h"
#include <fstream>

using namespace std;

int main() {
    // 2. 创建流式对象
    ofstream ofs;
    // 3. 打开文件
    ofs.open("test.txt", ios::app);  //当没有指定某盘路径时，创建的文件在该项目文件的路径下
    // 4. 写入文件
    ofs << "姓名：张三" << endl;
    ofs << "性别：男" << endl;
    // 5. 关闭文件
    ofs.close();

    return 0;
}