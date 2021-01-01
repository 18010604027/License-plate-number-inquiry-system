#pragma once
#include<string>
using namespace std;
struct plate_data
{
	char province = NULL;//第一位的省级
	char city = NULL;	  //第二级的市级
	int	num_one = NULL;  //后面的五位数
	int num_two = NULL;  //后面的五位数
	int num_three = NULL;//后面的五位数
	int num_four = NULL; //后面的五位数
	int num_five = NULL; //后面的五位数
	string name = "";  //车主姓名
	string place = ""; //车主地址
	string phone = ""; //车主电话
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
	void plate_read(char filename[]);
	void printfList();
	plate_node* return_num(int x);
	void insert(plate_node* p1);
	void _delete(plate_node* p1);
	void _quick_sort();
	void plate_write();
	void remain(int(*visit)) {};
	~plate_number() {};
	plate_node* head;
};