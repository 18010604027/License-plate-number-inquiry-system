#pragma once
#include<string>
using namespace std;

struct ListNum
{
	int num;
	struct ListNum* next;
};

typedef struct index_mark
{
	CString pro;
	int begin;
	int end;
}index_mark;

struct plate_data
{
	CString license;
	CString name = L"";  //车主姓名
	CString place = L""; //车主地址
	CString phone = L""; //车主电话
};
typedef struct plate_node
{
	struct plate_node* pre;
	struct plate_data* data;
	struct plate_node* next;
	int operator >(const plate_node& c2) const;
	static void swap(plate_node& p1, plate_node& p2)
	{
		struct plate_data* temp = p1.data;
		p1.data = p2.data;
		p2.data = temp;
	}
}plate_node, * link_plate_node;

class plate_number
{
public:
	plate_number();
	void clear_plate_num();
	bool plate_read(char filename[]);
	void printfList();
	plate_node* return_num(int x);
	void insert(CString license, CString name, CString place, CString phone);
	void _delete(plate_node* p1);
	void _delete(int x);
	void _quick_sort();
	void _radix_sort();
	void plate_write();
	int half_search(CString license);   //折半查找//这个函数会溢出栈
	int _index_search(CString license);  //索引查找
	//template <class T>
	//T Search(T(*visit)(va_list arg_ptr), ...) ;
	struct ListNum* Search(CString sub, int& num);
	int count();
	~plate_number();
	plate_node* head;
};

int NumChange(int index, int num);