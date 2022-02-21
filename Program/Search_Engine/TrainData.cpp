#include "TrainData.h"
//#include "Header.h"


void Push(List& L, string data)
{
    Node* newNode = new Node;
    newNode->word = data;
    newNode->next = L.head;
    L.head = newNode;
}

Node* Pop(List L)
{
    if (L.head == NULL)
        return NULL;
    else
    {
        Node* temp = L.head;
        L.head = temp->next;
        return temp;
    }
}


string XoaCach(string& st)
{
    int i = 0;
    while (st[0] == ' ')
    {
        st.erase(0, 1);
    }
    while (i < st.length())
    {
        if (st[i] == ' ' && st[i + 1] == ' ')
            st.erase(i, 1);
        else i++;
    }
    return st;
}
string ChuThuong(string& st)
{
    for (int i = 0; i < st.length(); i++)
        if (st[i] <= 'Z' && st[i] >= 'A')
            st[i] = st[i] + 32;
    return st;
}
string XoaKiTu(string& st)
{
    int i = 0;
    while (i < st.length())
    {
        if (st[i] == ',' || st[i] == '.' || st[i] == '?' || st[i] == '-' || st[i] == '\r' || st[i] == '\n' || st[i] == ')' || st[i] == '(')
            st.erase(i, 1);
        else i++;
    }
    return st;
}
List ListDau()
{
    string temp;
    List L;
    ifstream in("daukitu.txt");
    while (!in.eof())
    {
        getline(in, temp);
        Push(L, temp);
    }
    in.close();
    return L;
}
string XoaDau(string& st)
{
    st = st + " ";
    List L = ListDau();
    int dem = 0;
    for (Node* p = L.head; p->next != NULL; p = p->next)
    {
        int pos = -1;
        int x = st.find(p->word, pos + 1);
        while (x >= 0)
        {
            int len = p->word.size();
            if (dem < 34)
                st = st.replace(x, len, "a");
            else if (dem == 34 || dem == 35)
                st = st.replace(x, len, "d");
            else if (dem > 35 && dem < 58)
                st = st.replace(x, len, "e");
            else if (dem >= 58 && dem <= 67)
                st = st.replace(x, len, "i");
            else if (dem >= 68 && dem <= 101)
                st = st.replace(x, len, "o");
            else if (dem >= 102 && dem <= 123)
                st = st.replace(x, len, "u");
            else
                st = st.replace(x, len, "y");
            x = st.find(p->word, x + 1);
        }
        dem++;
    }
    return st;
}
List ListStopwords()
{
    ifstream in("stopword.txt");
    List L;
    string temp;
    while (!in.eof())
    {
        getline(in, temp);
        Push(L, temp);
    }
    in.close();
    return L;
}
bool Tu(string st, int pos, int len)
{
    if (pos == 0)
    {
        if (st[pos + len] == ' ')
            return true;
    }
    else
    {
        if (st[pos - 1] == ' ' && st[pos + len] == ' ')
            return true;
        return false;
    }
}
string XoaTu(string& st, List L)
{
    for (Node* p = L.head; p; p = p->next)
    {
        int pos = -1;
        int x = st.find(p->word, pos + 1);
        while (x >= 0)
        {
            if (Tu(st, x, p->word.length()))
                st.erase(x, p->word.length());
            x = st.find(p->word, x + 1);
        }
    }
    return st;
}

void DemTu(string st, List& L)
{
    int i = 0;
    st = st + " ";
    while (i < st.length())
    {
        int len = 1;
        if (st[i] != ' ' && (i == 0 || st[i - 1] == ' '))
        {
            string temp = "";
            int j = i;
            while (st[j] != ' ' && st[j] != '\0')
            {
                temp = temp + st[j];
                j++;
            }
            len = len + temp.length();
            bool kt = false;
            for (Node* p = L.head; p; p = p->next)
            {
                if (p->word == temp)
                {
                    kt = true;
                    p->count++;
                    break;
                }
            }
            if (kt == false)
                Push(L, temp);
        }
        i += len;
    }
}
int TongTu(List L)
{
    int dem = 0;
    for (Node* p = L.head; p; p = p->next)
        dem += p->count;
    return dem;
}
List ListKhongQuanTrong(List L)
{
    List temp;
    int s = TongTu(L);
    for (Node* p = L.head; p; p = p->next)
    {
        if ((p->count * 1.0 / s) < 0.01)
            Push(temp, p->word);
    }
    return temp;
}
void DeleteList(List& L)
{
    while (L.head != NULL)
    {
        Node* temp = L.head;
        L.head = L.head->next;
        delete temp;
    }
}

string ChuanHoa(string st)
{
    st = ChuThuong(st);                 //Chu hoa -> chu thuong
    st = XoaKiTu(st);                   //Xoa cac ki tu trong cau
    List sw = ListStopwords();
    st = XoaTu(st, sw);                 //Xoa stopword
    st = XoaDau(st);                    //Chuyen ve khong dau
    List word;
    DemTu(st, word);                    //Tao list tu
    List kqt = ListKhongQuanTrong(word);
    st = XoaTu(st, kqt);                //Xoa tu khong quan trong
    st = XoaCach(st);                   //Xoa space thua
    DeleteList(sw);
    DeleteList(word);
    DeleteList(kqt);
    return st;
}

void DocFile(string link, string& st)
{
    ifstream fi((const char*)link.c_str(), ios::binary);
    fi.seekg(0, ios::end);
    size_t size = (size_t)fi.tellg();
    fi.seekg(2, ios::beg);
    size -= 2;
    u16string u16((size / 2) + 1, '\0');
    fi.read((char*)&u16[0], size);
    st = wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
    fi.close();
    st = ChuanHoa(st);
}

void listFile()
{
    ofstream fo("metadata.txt");
    DIR* pDIR;
    struct dirent* entry;
    string temp = "D:/new train";
    if (pDIR = opendir((const char*)temp.c_str())) {
        while (entry = readdir(pDIR)) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                cout << entry->d_name << "\n";
                string temp2 = temp + "/";
                for (int i = 0; i < sizeof(entry->d_name); i++)
                {
                    if (entry->d_name[i] != '\0')
                        temp2 = temp2 + entry->d_name[i];
                    else break;
                }
                DIR* pDIR2;
                struct dirent* entry2;
                pDIR2 = opendir((const char*)temp2.c_str());
                while (entry2 = readdir(pDIR2))
                    if (strcmp(entry2->d_name, ".") != 0 && strcmp(entry2->d_name, "..") != 0)
                    {
                        string link = temp2 + "/";
                        for (int i = 0; i < sizeof(entry2->d_name); i++)
                        {
                            if (entry2->d_name[i] != '\0')
                                link = link + entry2->d_name[i];
                            else break;
                        }
                        cout << link << endl;
                        string st = "";
                        DocFile(link, st);
                        fo << link << endl << st << endl;
                    }
                closedir(pDIR2);
            }
        }
        closedir(pDIR);
        fo.close();
    }
}