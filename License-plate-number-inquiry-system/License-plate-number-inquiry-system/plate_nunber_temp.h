#pragma once
#include<string>
#include<queue>
using namespace std;

typedef struct plate_node_temp
{
	int pre;
	struct plate_data* data;
	int next;
	int operator >(const plate_node_temp& c2) const;
	static void swap(plate_node_temp& p1, plate_node_temp& p2)
	{
		struct plate_data* temp = p1.data;
		p1.data = p2.data;
		p2.data = temp;
	}
}plate_node_temp, * link_plate_node_temp;

class plate_number_temp
{
public:
	plate_number_temp();
	void clear_plate_num();
	bool plate_read(char filename[]);
	void printfList();
	plate_node_temp* return_num(int x);
	void insert(CString license, CString name, CString place, CString phone);
	void _delete(int x);
	void _radix_sort();
	void plate_write();
	int half_search(CString license);   //折半查找//这个函数会溢出栈
	int _index_search(CString license);  //索引查找
	//template <class T>
	//T Search(T(*visit)(va_list arg_ptr), ...) ;
	struct ListNum* Search(CString sub, int& num);
	int count();
	int openspace();
	void deletespace(int num);
	~plate_number_temp();
	int head;
	queue<int> MemPool;//内存池用于存放静态内存
	plate_node_temp* array;
};