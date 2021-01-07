#pragma once
//#include"pch.h"
void get_next(CString sub, int next[], int len);
bool kmp(CString s, CString sub,int *next=NULL);
void deal_string(CString& sub, int* num_string);