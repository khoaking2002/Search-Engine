#pragma once
#include "Header.h"
void Push(ListResult& LR, string link, string data);
Result* Pop(ListResult& LR);
ListResult ListMetadata();
ListResult ListMetadata2(ListResult& LR, List Word);
void DeleteListResult(ListResult& L);
ListResult init();
Result* addtail(ListResult& a, string link, string dulieu, int count);
ListResult merge(ListResult a, ListResult b);
void splitlist(ListResult &a, ListResult& b, ListResult c);
void merge_sort(ListResult& a);
void XuatData(ListResult LR, int x);
void Search(ListResult& LR);
bool checkfile(string link);
void AddFile(ListResult& LR);
void DelFile(ListResult& LR);
void MenuSearchEngine();

