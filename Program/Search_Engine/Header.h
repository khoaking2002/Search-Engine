#pragma once
#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()
#include <string>  //chi su dung getline
#include <locale>  
#include <codecvt> //possible C++11?
#include <fstream> 
#include <wchar.h>
#include<stdio.h>
#include<cstdlib>
#include<time.h>
#include<string.h>
#include "dirent.h"  //xu ly folder

using namespace std;
struct Node
{
    string word = "";
    int count = 1;
    double rate = 0.0;
    Node* next = NULL;
};
struct List
{
    Node* head = NULL;
};

struct Result
{
    string link = "";
    string data = "";
    int count = 5000;
    Result* next = NULL;
};
struct ListResult
{
    Result* head = NULL;
};


#endif // !HEADER_H

