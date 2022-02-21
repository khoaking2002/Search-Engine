#pragma once
#include "Header.h"
void Push(List& L, string data);
Node* Pop(List L);
string XoaCach(string& st);
string ChuThuong(string& st);
string XoaKiTu(string& st);
List ListDau();
string XoaDau(string& st);
List ListStopwords();
bool Tu(string st, int pos, int len);
string XoaTu(string& st, List L);
void DemTu(string st, List& L);
int TongTu(List L);
List ListKhongQuanTrong(List L);
void DeleteList(List& L);
string ChuanHoa(string st);
void XuatMetadata(string link, string st);
void DocFile(string link, string& st);
void listFile();								//Duyet het cac file

