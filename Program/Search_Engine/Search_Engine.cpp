#include "Header.h"
#include "TrainData.h"
#include "Function.h"

int main(int argc, wchar_t* argv[])
{
    _setmode(_fileno(stdout), _O_WTEXT); 
    wcout << L"Vui lòng chờ trong giây lát để chương trình khởi động" << endl;
    //listFile();                 //Tao metadata 
    MenuSearchEngine();         //Search
    return 0;
}



