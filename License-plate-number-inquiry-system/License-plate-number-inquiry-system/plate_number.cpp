#include"pch.h"
#include"plate_number.h"

int plate_node::operator >(const plate_node& c2) const
{
	if (data->province > c2.data->province)
	{
		return 1;
	}
	else if (data->province == c2.data->province)
	{
		if (data->city > c2.data->city)
		{
			return 1;
		}
		else if (data->city == c2.data->city)
		{
			if (data->num_one > c2.data->num_one)
			{
				return 1;
			}
			else if (data->num_one == c2.data->num_one)
			{
				if (data->num_two > c2.data->num_two)
				{
					return 1;
				}
				else if (data->num_two == c2.data->num_two)
				{
					if (data->num_three > c2.data->num_three)
					{
						return 1;
					}
					else if (data->num_three == c2.data->num_three)
					{
						if (data->num_four > c2.data->num_four)
						{
							return 1;
						}
						else if (data->num_four == c2.data->num_four)
						{
							if (data->num_five > c2.data->num_five)
							{
								return 1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}



plate_number::plate_number()
{
	head = new plate_node;//注意，开辟空间不可以用malloc来开辟空间
	head->data = new plate_data;
	//头空间不放任何数据
	head->pre = NULL;
	head->next = NULL;
}

void plate_number::clear_plate_num()
{
	fstream fout; fout.open("plate_num.txt", ios_base::out);
	fout.close();
}

void plate_number::plate_read(char filename[])
{

	string name;
	string place;
	string phone;
	string province;//用来帮助判断有没有读到文件尾

	plate_node* pnode1 = NULL;
	plate_node* pnode2 = NULL;
	pnode2 = head;

	fstream fin;
	fin.open(filename, ios_base::in);//别忘了写.txt，别烦这种低级错误
	if (!fin)
	{
		return;
	}
	while (1)
	{
		fin >> province;
		if (fin.eof())
		{
			break;
		}
		else
		{
			//cout << "读文件一次" << endl;
			pnode1 = new plate_node; pnode1->data = new plate_data; pnode1->next = NULL; pnode1->pre = NULL;
			//别错写成pnode2->next = NULL;别烦这种低级错误，否则会极大消耗内存
			pnode1->data->province = province.c_str();
			fin >> pnode1->data->city >> pnode1->data->num_one >> pnode1->data->num_two >> pnode1->data->num_three >> pnode1->data->num_four >> pnode1->data->num_five;
			fin >> name >> place >> phone;
			pnode1->data->name = name.c_str();
			pnode1->data->place = place.c_str();
			pnode1->data->phone = phone.c_str();
			while (pnode2->next != NULL)//让pnode2指向链表的最后一个
			{
				pnode2 = pnode2->next;
			}
			pnode2->next = pnode1;
			pnode1->pre = pnode2;
		}
	}
	fin.close();
}
void plate_number::printfList()
{
	plate_node* temp = NULL;
	temp = head;
	temp = temp->next;

	string province;
	string name;
	string place;
	string phone;

	while (temp != NULL)
	{
		province = CT2A(temp->data->province.GetString());
		name = CT2A(temp->data->name.GetString());
		place = CT2A(temp->data->place.GetString());
		phone = CT2A(temp->data->phone.GetString());

		cout << province << temp->data->city << temp->data->num_one << temp->data->num_two << temp->data->num_three << temp->data->num_four << temp->data->num_five << endl;
		cout << name << " " << place << " " << phone << endl;
		temp = temp->next;
	}
}

plate_node* plate_number::return_num(int x)
{
	int temp = 0;
	plate_node* head_temp = NULL;
	head_temp = head;
	while (temp < x && head_temp->next != NULL)
	{
		head_temp = head_temp->next;
		temp++;
	}
	return head_temp;
}

void plate_number::insert(CString province, char city, int num_one, int num_two, int num_three, int num_four, int num_five, CString name, CString place, CString phone)
{

	//插入在头结点之后
	plate_node* p1 = new plate_node;
	p1->data = new plate_data;
	p1->next = NULL;
	p1->pre = NULL;
	p1->data->province = province; p1->data->city = city; p1->data->num_one = num_one; p1->data->num_two = num_two; p1->data->num_three = num_three; p1->data->num_four = num_four; p1->data->num_five = num_five;

	p1->data->name = name; p1->data->place = place; p1->data->phone = phone;

	plate_node* head_temp = head;
	if (head_temp->next == NULL)//链表是不是只有头结点//是==，不是=，别犯这种低级错误
	{
		head_temp->next = p1;
		p1->pre = head_temp;
	}
	else
	{
		p1->next = head_temp->next;
		head_temp->next->pre = p1;
		head_temp->next = p1;
		p1->pre = head_temp;
	}
	//delete p1->data;这里不能删了这两个空间
	//delete p1;这里不能删了这两个空间
}

void plate_number::_delete(plate_node* p1)
{
	p1->pre->next = p1->next;
	p1->next->pre = p1->pre;
}
void plate_number::_quick_sort()
{
	plate_node* head_temp = NULL;
	head_temp = head;
	while (head_temp->next != NULL)
	{
		head_temp = head_temp->next;
	}
	quick_sort(head, head_temp);
}
void plate_number::plate_write()
{
	string province;
	string name;
	string place;
	string phone;

	fstream fout; fout.open("Data\\plate_num.data", ios_base::out);
	plate_node* pnode = NULL;
	pnode = head->next;
	while (pnode != NULL)
	{
		province = CT2A(pnode->data->province.GetString());
		name = CT2A(pnode->data->name.GetString());
		place = CT2A(pnode->data->place.GetString());
		phone = CT2A(pnode->data->phone.GetString());

		fout << province << " " << pnode->data->city << " " << pnode->data->num_one << " " << pnode->data->num_two << " " << pnode->data->num_three << " " << pnode->data->num_four << " " << pnode->data->num_five << endl;
		fout << name << " " << place << " " << phone << endl;
		pnode = pnode->next;
	}
	fout.close();
}
plate_number::~plate_number()
{

	plate_node* head_temp = head;
	while (head_temp->next != NULL)
	{
		head_temp = head_temp->next;
	}
	while (head_temp->pre != NULL)
	{
		delete head_temp->data;
		head_temp = head_temp->pre;
		delete head_temp->next;
	}
	delete head_temp->data;
	delete head_temp;

}

int plate_number::count()
{
	int i = 0;
	plate_node* head_temp = head->next;
	while (head_temp != NULL)
	{
		head_temp = head_temp->next;
		i++;
	}
	return i;

}