#pragma once
#include<string>
using namespace std;

struct ListNum
{
	int num;
	struct ListNum* next;
};

struct plate_data
{
	CString province = NULL;//��һλ��ʡ��
	char city = NULL;	  //�ڶ������м�
	int	num_one = NULL;  //�������λ��
	int num_two = NULL;  //�������λ��
	int num_three = NULL;//�������λ��
	int num_four = NULL; //�������λ��
	int num_five = NULL; //�������λ��
	CString name = L"";  //��������
	CString place = L""; //������ַ
	CString phone = L""; //�����绰
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
	void insert(CString province, char city, int num_one, int num_two, int num_three, int num_four, int num_five, CString name, CString place, CString phone);
	void _delete(plate_node* p1);
	void _quick_sort();
	void plate_write();
	//template <class T>
	//T Search(T(*visit)(va_list arg_ptr), ...) ;
	struct ListNum* Search(bool(*visit)(CString, CString), CString sub, int& num);
	int count();
	~plate_number();
	plate_node* head;
};