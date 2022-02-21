#include "Function.h"
#include "TrainData.h"
//#include "Header.h"

void Push(ListResult& LR, string link, string data)
{
    Result* newResult = new Result;
    newResult->link = link;
    newResult->data = data;
    newResult->next = LR.head;
    LR.head = newResult;
}
Result* Pop(ListResult& LR)
{
    if (LR.head == NULL)
        return NULL;
    else
    {
        Result* temp = LR.head;
        LR.head = temp->next;
        return temp;
    }
}
ListResult ListMetadata()
{
    ifstream fi("metadata.txt");
    ListResult LR;
    while (!fi.eof())
    {
        string link = "";
        getline(fi, link);
        string data = "";
        getline(fi, data);
        Push(LR, link, data);
    }
    fi.close();
    return LR;
}
ListResult ListMetadata2(ListResult& LR, List Word)
{
    for (Result* p = LR.head; p; p = p->next)
    {
        p->count = 5000;
        for (Node* p2 = Word.head; p2; p2 = p2->next)
        {
            int pos = -1;
            int x = p->data.find(p2->word, pos + 1);
            int dem = 0;
            while (x >= 0 && Tu(p->data, x, p2->word.length()))
            {
                dem++;
                x = p->data.find(p2->word, x + 1);
            }
            if (dem < p->count)
                p->count = dem;
        }
    }
    return LR;
}
void DeleteListResult(ListResult& L)
{
    while (L.head != NULL)
    {
        Result* temp = L.head;
        L.head = temp->next;
        delete temp;
    }
}
ListResult init() {
    ListResult a;
    a.head = NULL;
    return a;
}
Result* addtail(ListResult& a, string path, string dulieu, int dem) {
    Result* add = new Result;
    add->next = NULL;
    add->link = path;
    add->count = dem;
    add->data = dulieu;
    if (a.head == NULL) { a.head = add;}
    else {
        Result* p = a.head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = add;
    }
    return add;
}
ListResult merge(ListResult a, ListResult b) {
    if (a.head == NULL) { return b; }
    if (b.head == NULL) { return a; }
    ListResult c = init();
    Result* p = a.head;
    Result* q = b.head;
    Result* tmp = new Result;
    while (p != NULL && q != NULL) {
        if (p->count > q->count) { tmp = addtail(c, p->link,p->data,p->count); p = p->next; }
        else { tmp = addtail(c, q->link, q->data, q->count); q = q->next; }
    }
    if (p != NULL) { tmp->next = p; }
    if (q != NULL) { tmp->next = q; }
    return c;
}
void spilitlist(ListResult &a, ListResult& b, ListResult c) {
    Result* fast = c.head;
    a.head = c.head;
    Result* slow = c.head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    b.head = slow->next;
    slow->next = NULL;
}
void merge_sort(ListResult& a) {
    if (a.head == NULL || a.head->next == NULL) { return; }
    else {
        ListResult a1 = init();
        ListResult a2 = init();
        spilitlist(a1, a2, a);
        merge_sort(a1);
        merge_sort(a2);
        a = merge(a1, a2);
    }
}
void XuatData(ListResult LR, int x)
{
    //_setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    int i = 0;
    for (Result* p = LR.head; p; p = p->next)
    {
        i++;
        if (i == x)
        {
            /*ifstream fi((const char*)p->link.c_str());
            string st;
            getline(fi, st);
            wstring wst(st.begin(), st.end());
            wcout << wst << endl;*/
            ifstream fi((const char*)p->link.c_str(), ios::binary);
            fi.seekg(0, ios::end);
            size_t size = (size_t)fi.tellg();
            fi.seekg(2, ios::beg);
            size -= 2;
            u16string u16((size / 2) + 1, '\0');
            fi.read((char*)&u16[0], size);
            fi.close();
            wstring wst(u16.begin(), u16.end());
            wcout << wst << endl;
        }
    }
}

void Search(ListResult& LR)
{
    clock_t start, end;
    double cpu_time_used;
    //_setmode(_fileno(stdout), _O_U16TEXT);
    //_setmode(_fileno(stdout), _O_WTEXT);
    string st = "";
    //cout << "Moi ban nhap tu: ";
    wcout << L"Mời bạn nhập từ: ";
    cin.ignore();
    getline(cin, st);
    start = clock();
    st = ChuThuong(st);
    List Word;
    DemTu(st, Word);
    LR = ListMetadata2(LR, Word);
    merge_sort(LR);
    end = clock();
    cpu_time_used = ((double)(end - start))/ CLOCKS_PER_SEC;
    wcout << L"Thời gian thực thi: " << cpu_time_used << endl;
    if (LR.head->count == 0)
    {
        wcout << L"Lỗi tìm kiếm, hãy chắc chắn bạn nhập từ đúng chính tả.\n";
        wcout << L"Hãy thử tìm lại từ khác\n";
    }
    else
    {
        int dem = 0;
        for (Result* p = LR.head; p; p = p->next)
        {
            dem++;
            if (dem%10==1 && dem>10) {
                wcout << L"Hiển thị thêm kết quả tìm kiếm ?/1. có, 0. không: ";
                int c;
                cin >> c;
                if (c == 0) { break; }
            }
            //cout << dem << ". " << p->link << endl;
            wstring wst(p->link.begin(), p->link.end());
            wcout << dem << ". " << wst << endl;
        }
        int x;
        wcout << L"Bạn muốn xem chi tiết file nào (0:thoát/1->"<<dem-1<<" ): ";
        cin >> x;
        if (x >= 1 && x <= dem-1)
        {
            XuatData(LR, x);
        }
    }
    DeleteList(Word);
}
bool checkfile(string link) {
    ifstream fi(link);
    bool kt = fi.good();
    fi.close();
    return kt;
}
void AddFile(ListResult& LR)
{
    _setmode(_fileno(stdout), _O_WTEXT);
    string link;
    wcout << L"Nhập đường dẫn của file muốn thêm(hãy đảm bảo bạn nhập đúng, ví dụ D:/caigido.txt): ";
    cin.ignore();
    getline(cin, link);
    if (!checkfile(link)) { //err
        wcout << L"Đường dẫn đến file bạn cần thêm bị lỗi, hãy xem lại!!!\n";
    }
    else
    {
        string st = "";
        DocFile(link, st);
        Push(LR, link, st);
        wcout << L"File đã được thêm thành công vào bộ dữ liệu\n";
    }
}

void DelFile(ListResult& LR)
{
    _setmode(_fileno(stdout), _O_WTEXT);
    string link;
    wcout << L"Nhập đường dẫn đến file muốn xóa(hãy đảm bảo bạn nhập đúng, ví dụ D:/huydeptrai.txt): ";
    cin.ignore();
    getline(cin, link);
    bool kt = false;
    if (LR.head->link == link) {
        kt = true;
        Result* temp = LR.head;
        LR.head = LR.head->next;
        delete temp;
        wcout << L"File đã được xóa thành công khỏi bộ dữ liệu\n";
    }
    else {
        for (Result* p = LR.head; p->next; p = p->next)
        {
            if (p->next->link == link)
            {
                kt = true;
                Result* temp = p->next;
                p->next = temp->next;
                delete temp;
                wcout << L"File đã được xóa thành công khỏi bộ dữ liệu\n";
                break;
            }
        }
    }
    if (kt == false)
        wcout << L"Đường dẫn đến file bạn cần xóa không tồn tại trong dữ liệu!!!\n";
}

void MenuSearchEngine()
{
    ListResult LR = ListMetadata();
    _setmode(_fileno(stdout), _O_WTEXT);
    int x, y;
    do
    {
        system("cls");
        wcout << L"_____________________WELCOME_TO_SEARCH_ENGINE__________________\n";
        wcout << L"1.Tim từ\n";
        wcout << L"2.Thêm file\n";
        wcout << L"3.Xóa file\n";
        wcout << L"4.Thoát chương trình\n";
        wcout << L"Nhập chức năng bạn muốn: ";
        cin >> x;

        if (x == 4 || cin.fail()) break;
        if (x == 1)
            Search(LR);
        else if (x == 2)
            AddFile(LR);
        else if (x == 3)
            DelFile(LR);
        wcout << L"Bạn có muốn tìm tục sử dụng công cụ (0:Thoát/ 1:Tiếp tục): ";
        cin >> y;
        if (y == 0 || cin.fail()) break;
    } while (x != 4 || y != 0);
    DeleteListResult(LR);
}

