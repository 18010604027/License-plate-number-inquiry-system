#include"pch.h"
#include"plate_number.h"

int plate_node::operator >(const plate_node& c2) const
{
	if (data->license > c2.data->license)
	{
		return 1;
	}
	else
	{
		return 0;
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

bool plate_number::plate_read(char filename[])
{
	string name;
	string place;
	string phone;
	string license;//用来帮助判断有没有读到文件尾

	plate_node* pnode1 = NULL;
	plate_node* pnode2 = NULL;
	pnode2 = head;

	fstream fin;
	fin.open(filename, ios_base::in);//别忘了写.txt，别烦这种低级错误
	if (!fin)
	{
		return false;
	}
	while (1)
	{
		fin >> license;
		if (fin.eof())
		{
			break;
		}
		else
		{
			//cout << "读文件一次" << endl;
			pnode1 = new plate_node; pnode1->data = new plate_data; pnode1->next = NULL; pnode1->pre = NULL;
			//别错写成pnode2->next = NULL;别烦这种低级错误，否则会极大消耗内存
			pnode1->data->license = license.c_str();

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
	return true;
}
void plate_number::printfList()
{
	plate_node* temp = NULL;
	temp = head;
	temp = temp->next;

	string license;
	string name;
	string place;
	string phone;

	while (temp != NULL)
	{
		license = CT2A(temp->data->license.GetString());
		name = CT2A(temp->data->name.GetString());
		place = CT2A(temp->data->place.GetString());
		phone = CT2A(temp->data->phone.GetString());

		cout << license << endl;
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

void plate_number::_delete(plate_node* p1)
{
	p1->pre->next = p1->next;
	p1->next->pre = p1->pre;
	delete p1;
}

void plate_number::_delete(int x)
{
	int i = 0;
	plate_node* head_temp = head;
	while (i < x)
	{
		i++;    //别忘了这句话，别犯这种低级错误
		head_temp = head_temp->next;
	}
	head_temp->pre->next = head_temp->next;
	head_temp->next->pre = head_temp->pre;
	delete head_temp;
	/*
	p1->pre->next = p1->next;
	p1->next->pre = p1->pre;
	*/
}

void plate_number::insert(CString license, CString name, CString place, CString phone)
{
	//插入在头结点之后
	plate_node* p1 = new plate_node;
	p1->data = new plate_data;
	p1->next = NULL;
	p1->pre = NULL;
	p1->data->license = license;//////////////////////////////////////////////1333333333333333333333333333

	/*
	CString name_1;
	CString place_1;
	CString phone_1;
	name_1 = name.c_str();
	place_1 = place.c_str();
	phone_1 = phone.c_str();
	*/

	p1->data->name = name; p1->data->place = place; p1->data->phone = phone;
	plate_node* head_temp = head;
	if (head_temp->next == NULL)//链表是不是只有头结点//是==，不是=，别犯这种低级错误
	{
		head_temp->next = p1;
		p1->pre = head_temp;
	}
	else
	{
		while (head_temp->next != NULL)
		{
			head_temp = head_temp->next;
			if (p1->data->license < head_temp->data->license)//注意这里是小于号<，不是大于号
			{
				p1->next = head_temp;
				p1->pre = head_temp->pre;
				head_temp->pre->next = p1;
				head_temp->pre = p1;
				break;
			}
		}
		if (head_temp->next == NULL)
		{
			if (head_temp->pre->data->license == p1->data->license)
			{
				return;
			}
			else
			{
				head_temp->next = p1;
				p1->pre = head_temp;
			}
		}
		/*
		p1->next = head_temp->next;
		head_temp->next->pre = p1;
		head_temp->next = p1;
		p1->pre = head_temp;
		*/
	}
	//delete p1->data;这里不能删了这两个空间
	//delete p1;这里不能删了这两个空间
}
void plate_number::_quick_sort()
{
	plate_node* head_temp = NULL;
	head_temp = head;
	while (head_temp->next != NULL)
	{
		head_temp = head_temp->next;
	}
	quick_sort<plate_node, plate_data>(head->next, head_temp);
}
int NumChange(int index, int num)
{
	if (index == 0)
	{
		const wchar_t province_short[] = { L'云', L'京',L'冀',L'吉',L'宁',L'川',L'新',L'晋',L'桂',L'沪',L'津',L'浙',L'渝',L'港',L'湘',L'澳',
			L'琼',L'甘',L'皖',L'粤',L'苏',L'蒙',
			L'藏',L'豫',L'贵',L'赣',L'辽',L'鄂',
			L'闽',L'陕',L'青',L'鲁',L'黑'
		};
		for (int i = 0; i < 33; i++)
		{
			if (num == province_short[i])
			{
				return i;
			}
		}
		return 0;
	}
	else if (index == 1)
	{
		return num - 'A';
	}
	else
	{
		return num - L'0';
	}
}
void plate_number::_radix_sort()
{
	const int Num[] = { 256,26,10,10,10,10,10 };
	//PutDebug(2, head->next->data->license[1], head->next->data->license[2]);
	plate_node* p = head->next;
	radix(head, count(), Num, NumChange, 7);
}
void plate_number::plate_write()
{
	string license;
	string name;
	string place;
	string phone;

	fstream fout; fout.open("Data\\plate_num.data", ios_base::out);
	plate_node* pnode = NULL;
	pnode = head->next;
	while (pnode != NULL)
	{
		license = CT2A(pnode->data->license.GetString());
		name = CT2A(pnode->data->name.GetString());
		place = CT2A(pnode->data->place.GetString());
		phone = CT2A(pnode->data->phone.GetString());

		fout << license << endl;
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
		if (!head_temp->data)
		{
			delete head_temp->data;
		}
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

//template <class T>
//T plate_number::Search(T(*visit)(va_list arg_ptr), ...)
//{
//	va_list arg_ptr;
//	va_start(arg_ptr, visit);
//	return visit(arg_ptr);
//}
struct ListNum* plate_number::Search(bool(*visit)(CString, CString), CString sub, int& num)
{
	int i = 0;
	num = 0;
	plate_node* head_temp = head->next;
	struct ListNum* list_num = new struct ListNum;
	struct ListNum* p = list_num;
	while (head_temp != NULL)
	{
		plate_data* data = head_temp->data;
		if (visit(data->license, sub))
		{
			p->next = new struct ListNum;
			p = p->next;
			p->num = i;
			num++;
		}
		head_temp = head_temp->next;
		i++;
	}
	p->next = NULL;
	return list_num;
}


int plate_number::half_search(CString license)
{
	int i = 0, j = 0, k = 0;
	plate_node* head_temp = head->next;
	while (head_temp != NULL)
	{
		head_temp = head_temp->next;
		i++;
	}
	head_temp = head->next;
	k = i;
	CString arr[100];
	while (head_temp != NULL && j < 100)
	{
		arr[j] = head_temp->data->license;
		head_temp = head_temp->next;
		j++;
	}
	int low = 0, high = j - 1, mid;
	if (arr[low] == license)
	{
		return low;
	}
	else if (arr[high] == license)
	{
		return high;
	}
	else
	{
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (arr[mid] == license)
			{
				return mid;
			}
			if (license > arr[mid])
			{
				low = mid + 1;
			}
			else
			{
				high = mid - 1;
			}
		}
	}
	return -1;
}

typedef struct index_mark
{
	CString pro;
	int begin;
	int end;
}index_mark;
//注意，这个函数的前提是链表已经排好序了，否则建立的索引表是不正确的
int plate_number::_index_search(CString license)
{

	int count = 0;
	int i = 0, j = 0, n;
	plate_node* head_temp_2 = head->next;

	plate_data array_node[100];           //这个的长度只有100
	while (j < 100 && head_temp_2 != NULL)
	{
		array_node[j].license = head_temp_2->data->license;
		array_node[j].name = head_temp_2->data->name;
		array_node[j].phone = head_temp_2->data->phone;
		array_node[j].place = head_temp_2->data->place;
		j++;
		head_temp_2 = head_temp_2->next;
	}
	plate_node* head_temp = head->next;
	index_mark _index[31];
	_index[0].pro = "京"; _index[0].begin = 0; _index[0].end = 0;
	_index[1].pro = "津"; _index[1].begin = 0; _index[1].end = 0;
	_index[2].pro = "冀"; _index[2].begin = 0; _index[2].end = 0;
	_index[3].pro = "晋"; _index[3].begin = 0; _index[3].end = 0;
	_index[4].pro = "蒙"; _index[4].begin = 0; _index[4].end = 0;
	_index[5].pro = "辽"; _index[5].begin = 0; _index[5].end = 0;
	_index[6].pro = "吉"; _index[6].begin = 0; _index[6].end = 0;
	_index[7].pro = "黑"; _index[7].begin = 0; _index[7].end = 0;
	_index[8].pro = "沪"; _index[8].begin = 0; _index[8].end = 0;
	_index[9].pro = "苏"; _index[9].begin = 0; _index[9].end = 0;
	_index[10].pro = "浙"; _index[10].begin = 0; _index[10].end = 0;
	_index[11].pro = "皖"; _index[11].begin = 0; _index[11].end = 0;
	_index[12].pro = "闽"; _index[12].begin = 0; _index[12].end = 0;
	_index[13].pro = "赣"; _index[14].begin = 0; _index[14].end = 0;
	_index[14].pro = "鲁"; _index[14].begin = 0; _index[14].end = 0;
	_index[15].pro = "豫"; _index[15].begin = 0; _index[15].end = 0;
	_index[16].pro = "鄂"; _index[16].begin = 0; _index[16].end = 0;
	_index[17].pro = "湘"; _index[17].begin = 0; _index[17].end = 0;
	_index[18].pro = "粤"; _index[18].begin = 0; _index[18].end = 0;
	_index[19].pro = "桂"; _index[19].begin = 0; _index[19].end = 0;
	_index[20].pro = "琼"; _index[20].begin = 0; _index[20].end = 0;
	_index[21].pro = "渝"; _index[21].begin = 0; _index[21].end = 0;
	_index[22].pro = "川"; _index[22].begin = 0; _index[22].end = 0;
	_index[23].pro = "贵"; _index[23].begin = 0; _index[23].end = 0;
	_index[24].pro = "云"; _index[24].begin = 0; _index[24].end = 0;
	_index[25].pro = "藏"; _index[25].begin = 0; _index[25].end = 0;
	_index[26].pro = "陕"; _index[26].begin = 0; _index[26].end = 0;
	_index[27].pro = "甘"; _index[27].begin = 0; _index[27].end = 0;
	_index[28].pro = "青"; _index[28].begin = 0; _index[28].end = 0;
	_index[29].pro = "宁"; _index[29].begin = 0; _index[29].end = 0;
	_index[30].pro = "新"; _index[30].begin = 0; _index[30].end = 0;
	/**
	string str1 = "京", str2 = "津", str3 = "冀", str4 = "晋", str5 = "蒙", str6 = "辽", str7 = "吉", str8 = "黑", str9 = "沪";
	string str10 = "苏", str11 = "浙", str12 = "皖", str13 = "闽", str14 = "赣", str15 = "鲁", str16 = "豫", str17 = "鄂";
	string str18 = "湘", str19 = "粤", str20 = "桂", str21 = "琼", str22 = "渝", str23 = "川", str24 = "贵", str25 = "云";
	string str26 = "藏", str27 = "陕", str28 = "甘", str29 = "青", str30 = "宁", str31 = "新";
	*/
	i = 0;

	while (i < j)
	{

		if (array_node[i].license[0] == _index[0].pro)         //index[1]
		{
			_index[0].begin = i;								          //index[1]
			i++;
			while (array_node[i].license[0] == _index[0].pro)  //index[1]
			{
				i++;
			}
			_index[0].end = i - 1;								          //index[1]
		}
		else if (array_node[i].license[0] == _index[1].pro)
		{
			_index[1].begin = i;
			i++;
			while (array_node[i].license[0] == _index[1].pro)
			{
				i++;
			}
			_index[1].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[2].pro)
		{
			_index[2].begin = i;
			i++;
			while (array_node[i].license[0] == _index[2].pro)
			{
				i++;
			}
			_index[2].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[3].pro)
		{
			_index[3].begin = i;
			i++;
			while (array_node[i].license[0] == _index[3].pro)
			{
				i++;
			}
			_index[3].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[4].pro)
		{
			_index[4].begin = i;
			i++;
			while (array_node[i].license[0] == _index[4].pro)
			{
				i++;
			}
			_index[4].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[5].pro)
		{
			_index[5].begin = i;
			i++;
			while (array_node[i].license[0] == _index[5].pro)
			{
				i++;
			}
			_index[5].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[6].pro)
		{
			_index[6].begin = i;
			i++;
			while (array_node[i].license[0] == _index[6].pro)
			{
				i++;
			}
			_index[6].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[7].pro)
		{
			_index[7].begin = i;
			i++;
			while (array_node[i].license[0] == _index[7].pro)
			{
				i++;
			}
			_index[7].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[8].pro)
		{
			_index[8].begin = i;
			i++;
			while (array_node[i].license[0] == _index[8].pro)
			{
				i++;
			}
			_index[8].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[9].pro)
		{
			_index[9].begin = i;
			i++;
			while (array_node[i].license[0] == _index[9].pro)
			{
				i++;
			}
			_index[9].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[10].pro)
		{
			cout << "运行索引查找" << endl;
			_index[10].begin = i;
			i++;
			while (array_node[i].license[0] == _index[10].pro)
			{
				i++;
			}
			_index[10].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[11].pro)
		{
			_index[11].begin = i;
			i++;
			while (array_node[i].license[0] == _index[11].pro)
			{
				i++;
			}
			_index[11].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[12].pro)
		{
			_index[12].begin = i;
			i++;
			while (array_node[i].license[0] == _index[12].pro)
			{
				i++;
			}
			_index[12].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[13].pro)
		{
			_index[13].begin = i;
			i++;
			while (array_node[i].license[0] == _index[13].pro)
			{
				i++;
			}
			_index[13].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[14].pro)
		{
			_index[14].begin = i;
			i++;
			while (array_node[i].license[0] == _index[14].pro)
			{
				i++;
			}
			_index[14].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[15].pro)
		{
			_index[15].begin = i;
			i++;
			while (array_node[i].license[0] == _index[15].pro)
			{
				i++;
			}
			_index[15].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[16].pro)
		{
			_index[16].begin = i;
			i++;
			while (array_node[i].license[0] == _index[16].pro)
			{
				i++;
			}
			_index[16].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[17].pro)
		{
			_index[17].begin = i;
			i++;
			while (array_node[i].license[0] == _index[17].pro)
			{
				i++;
			}
			_index[17].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[18].pro)
		{
			_index[18].begin = i;
			i++;
			while (array_node[i].license[0] == _index[18].pro)
			{
				i++;
			}
			_index[18].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[19].pro)
		{
			_index[19].begin = i;
			i++;
			while (array_node[i].license[0] == _index[19].pro)
			{
				i++;
			}
			_index[19].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[20].pro)
		{
			_index[20].begin = i;
			i++;
			while (array_node[i].license[0] == _index[20].pro)
			{
				i++;
			}
			_index[20].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[21].pro)
		{
			_index[21].begin = i;
			i++;
			while (array_node[i].license[0] == _index[21].pro)
			{
				i++;
			}
			_index[21].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[22].pro)
		{
			_index[22].begin = i;
			i++;
			while (array_node[i].license[0] == _index[22].pro)
			{
				i++;
			}
			_index[22].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[23].pro)
		{
			_index[23].begin = i;
			i++;
			while (array_node[i].license[0] == _index[23].pro)
			{
				i++;
			}
			_index[23].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[24].pro)
		{
			_index[24].begin = i;
			i++;
			while (array_node[i].license[0] == _index[24].pro)
			{
				i++;
			}
			_index[24].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[25].pro)
		{
			_index[25].begin = i;
			i++;
			while (array_node[i].license[0] == _index[25].pro)
			{
				i++;
			}
			_index[25].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[26].pro)
		{
			_index[26].begin = i;
			i++;
			while (array_node[i].license[0] == _index[26].pro)
			{
				i++;
			}
			_index[26].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[27].pro)
		{
			_index[27].begin = i;
			i++;
			while (array_node[i].license[0] == _index[27].pro)
			{
				i++;
			}
			_index[1].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[28].pro)
		{
			_index[28].begin = i;
			i++;
			while (array_node[i].license[0] == _index[28].pro)
			{
				i++;
			}
			_index[28].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[29].pro)
		{
			_index[29].begin = i;
			i++;
			while (array_node[i].license[0] == _index[29].pro)
			{
				i++;
			}
			_index[29].end = i - 1;
		}
		else if (array_node[i].license[0] == _index[30].pro)
		{
			_index[30].begin = i;
			i++;
			while (array_node[i].license[0] == _index[30].pro)
			{
				i++;
			}
			_index[30].end = i - 1;
		}

		i++;//这里不能忘了i++，否则会死循环
	}

	n = 0;
	j = 0;
	while (j <= 30)
	{
		if (license[0] == _index[j].pro)
		{
			n = _index[j].begin;
			while (n <= _index[j].end)
			{
				if (license == array_node[n].license)
				{
					return n;
				}
				else
				{
					n++;
				}
			}
			return -1;
		}
		j++;
	}
	return -1;
}
