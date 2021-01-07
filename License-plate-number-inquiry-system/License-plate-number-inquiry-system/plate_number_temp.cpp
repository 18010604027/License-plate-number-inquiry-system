#include"pch.h"
#include"plate_nunber_temp.h"
int plate_node_temp::operator >(const plate_node_temp& c2) const
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

int plate_number_temp::openspace()
{
	int num = MemPool.front();
	MemPool.pop();
	return num;
}
void plate_number_temp::deletespace(int num)
{
	MemPool.push(num);
}

plate_number_temp::plate_number_temp()
{
	const int maxnum = 10000;
	array = new plate_node_temp[maxnum + 1];
	for (int i = 1; i <= maxnum; i++)
	{
		MemPool.push(i);
	}
	head = openspace();//ע�⣬���ٿռ䲻������malloc�����ٿռ�
	array[head].data = new plate_data;
	//ͷ�ռ䲻���κ�����
	array[head].pre = NULL;
	array[head].next = NULL;
}
plate_number_temp::~plate_number_temp()
{

	int head_temp = head;
	while (array[head_temp].next != NULL)
	{
		head_temp = array[head_temp].next;
	}
	while (array[head_temp].pre != NULL)
	{
		if (!array[head_temp].data)
		{
			delete array[head_temp].data;
		}
		head_temp = array[head_temp].pre;
		deletespace(array[head_temp].next);
	}
	delete array[head_temp].data;
	deletespace(head_temp);

}

void plate_number_temp::printfList()
{
	int temp = NULL;
	temp = head;
	temp = array[temp].next;

	string license;
	string name;
	string place;
	string phone;

	while (temp != NULL)
	{
		license = CT2A(array[temp].data->license.GetString());
		name = CT2A(array[temp].data->name.GetString());
		place = CT2A(array[temp].data->place.GetString());
		phone = CT2A(array[temp].data->phone.GetString());

		cout << license << endl;
		cout << name << " " << place << " " << phone << endl;
		temp = array[temp].next;
	}
}
plate_node_temp* plate_number_temp::return_num(int x)
{
	int count = 0;
	int head_temp = NULL;
	head_temp = head;
	while (count < x && array[head_temp].next != NULL)
	{
		head_temp = array[head_temp].next;
		count++;
	}
	return (array + head_temp);
}

void plate_number_temp::insert(CString license, CString name, CString place, CString phone)
{
	//������ͷ���֮��
	int p1 = openspace();
	array[p1].data = new plate_data;
	array[p1].next = NULL;
	array[p1].pre = NULL;
	array[p1].data->license = license;//////////////////////////////////////////////1333333333333333333333333333

	/*
	CString name_1;
	CString place_1;
	CString phone_1;
	name_1 = name.c_str();
	place_1 = place.c_str();
	phone_1 = phone.c_str();
	*/

	array[p1].data->name = name; array[p1].data->place = place; array[p1].data->phone = phone;
	int head_temp = head;
	if (array[head_temp].next == NULL)//�����ǲ���ֻ��ͷ���//��==������=�������ֵͼ�����
	{
		array[head_temp].next = p1;
		array[p1].pre = head_temp;
	}
	else
	{
		while (array[head_temp].next != NULL)
		{
			head_temp = array[head_temp].next;
			if (array[p1].data->license < array[head_temp].data->license)//ע��������С�ں�<�����Ǵ��ں�
			{
				array[p1].next = head_temp;
				array[p1].pre = array[head_temp].pre;
				array[array[head_temp].pre].next = p1;
				array[head_temp].pre = p1;
				break;
			}
		}
		if (array[head_temp].next == NULL)
		{
			if (array[array[head_temp].pre].data->license == array[p1].data->license)
			{
				return;
			}
			else
			{
				array[head_temp].next = p1;
				array[p1].pre = head_temp;
			}
		}
		/*
		p1->next = head_array[temp].next;
		head_array[temp].next->pre = p1;
		head_array[temp].next = p1;
		p1->pre = head_temp;
		*/
	}
	//delete p1->data;���ﲻ��ɾ���������ռ�
	//delete p1;���ﲻ��ɾ���������ռ�
}
void plate_number_temp::_delete(int x)
{
	int i = 0;
	int head_temp = head;
	while (i < x)
	{
		i++;    //��������仰�������ֵͼ�����
		head_temp = array[head_temp].next;
	}
	array[array[head_temp].pre].next = array[head_temp].next;
	array[array[head_temp].next].pre = array[head_temp].pre;
	deletespace(head_temp);
	/*
	p1->pre->next = p1->next;
	p1->next->pre = p1->pre;
	*/
}

bool plate_number_temp::plate_read(char filename[])
{
	string name;
	string place;
	string phone;
	string license;//���������ж���û�ж����ļ�β

	int pnode1 = NULL;
	int pnode2 = NULL;
	pnode2 = head;

	fstream fin;
	fin.open(filename, ios_base::in);//������д.txt�������ֵͼ�����
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
			//cout << "���ļ�һ��" << endl;
			pnode1 = openspace(); array[pnode1].data = new plate_data; array[pnode1].next = NULL; array[pnode1].pre = NULL;
			//���д��array[pnode2].next = NULL;�����ֵͼ����󣬷���Ἣ�������ڴ�
			array[pnode1].data->license = license.c_str();

			fin >> name >> place >> phone;
			array[pnode1].data->name = name.c_str();
			array[pnode1].data->place = place.c_str();
			array[pnode1].data->phone = phone.c_str();

			while (array[pnode2].next != NULL)//��pnode2ָ����������һ��
			{
				pnode2 = array[pnode2].next;
			}
			array[pnode2].next = pnode1;
			array[pnode1].pre = pnode2;
		}
	}
	fin.close();
	return true;
}
void plate_number_temp::plate_write()
{
	string license;
	string name;
	string place;
	string phone;

	fstream fout; fout.open("Data\\plate_num.data", ios_base::out);
	int pnode = NULL;
	pnode = array[head].next;
	while (pnode != NULL)
	{
		license = CT2A(array[pnode].data->license.GetString());
		name = CT2A(array[pnode].data->name.GetString());
		place = CT2A(array[pnode].data->place.GetString());
		phone = CT2A(array[pnode].data->phone.GetString());

		fout << license << endl;
		fout << name << " " << place << " " << phone << endl;
		pnode = array[pnode].next;
	}
	fout.close();
}
void plate_number_temp::clear_plate_num()
{
	fstream fout; fout.open("plate_num.txt", ios_base::out);
	fout.close();
}

int plate_number_temp::count()
{
	int i = 0;
	int head_temp = array[head].next;
	while (head_temp != NULL)
	{
		head_temp = array[head_temp].next;
		i++;
	}
	return i;

}

void plate_number_temp::_radix_sort()
{
	const int Num[] = { 31,26,10,10,10,10,10 };
	int p = array[head].next;
	radix_temp(array, head, count(), Num, NumChange, 7);
}

struct ListNum* plate_number_temp::Search(CString sub, int& num)
{
	int i = 0;
	num = 0;
	int head_temp = array[head].next;
	struct ListNum* list_num = new struct ListNum;
	struct ListNum* p = list_num;
	int* next = new int[sub.GetLength()];
	get_next(sub, next, sub.GetLength());
	while (head_temp != NULL)
	{
		plate_data* data = array[head_temp].data;
		if (kmp(data->license, sub, next))
		{
			p->next = new struct ListNum;
			p = p->next;
			p->num = i;
			num++;
		}
		head_temp = array[head_temp].next;
		i++;
	}
	p->next = NULL;
	return list_num;
}
int plate_number_temp::half_search(CString license)
{
	int i = 0, j = 0, k = 0;
	int head_temp = array[head].next;
	while (head_temp != NULL)
	{
		head_temp = array[head_temp].next;
		i++;
	}
	head_temp = array[head].next;
	k = i;
	CString arr[100];
	while (head_temp != NULL && j < 100)
	{
		arr[j] = array[head_temp].data->license;
		head_temp = array[head_temp].next;
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
int plate_number_temp::_index_search(CString license)
{

	int count = 0;
	int i = 0, j = 0, n;
	int head_temp_2 = array[head].next;

	plate_data array_node[100];           //����ĳ���ֻ��100
	while (j < 100 && head_temp_2 != NULL)
	{
		array_node[j].license = array[head_temp_2].data->license;
		array_node[j].name = array[head_temp_2].data->name;
		array_node[j].phone = array[head_temp_2].data->phone;
		array_node[j].place = array[head_temp_2].data->place;
		j++;
		head_temp_2 = array[head_temp_2].next;
	}
	int head_temp = array[head].next;
	index_mark _index[31];
	_index[0].pro = "��"; _index[0].begin = 0; _index[0].end = 0;
	_index[1].pro = "��"; _index[1].begin = 0; _index[1].end = 0;
	_index[2].pro = "��"; _index[2].begin = 0; _index[2].end = 0;
	_index[3].pro = "��"; _index[3].begin = 0; _index[3].end = 0;
	_index[4].pro = "��"; _index[4].begin = 0; _index[4].end = 0;
	_index[5].pro = "��"; _index[5].begin = 0; _index[5].end = 0;
	_index[6].pro = "��"; _index[6].begin = 0; _index[6].end = 0;
	_index[7].pro = "��"; _index[7].begin = 0; _index[7].end = 0;
	_index[8].pro = "��"; _index[8].begin = 0; _index[8].end = 0;
	_index[9].pro = "��"; _index[9].begin = 0; _index[9].end = 0;
	_index[10].pro = "��"; _index[10].begin = 0; _index[10].end = 0;
	_index[11].pro = "��"; _index[11].begin = 0; _index[11].end = 0;
	_index[12].pro = "��"; _index[12].begin = 0; _index[12].end = 0;
	_index[13].pro = "��"; _index[14].begin = 0; _index[14].end = 0;
	_index[14].pro = "³"; _index[14].begin = 0; _index[14].end = 0;
	_index[15].pro = "ԥ"; _index[15].begin = 0; _index[15].end = 0;
	_index[16].pro = "��"; _index[16].begin = 0; _index[16].end = 0;
	_index[17].pro = "��"; _index[17].begin = 0; _index[17].end = 0;
	_index[18].pro = "��"; _index[18].begin = 0; _index[18].end = 0;
	_index[19].pro = "��"; _index[19].begin = 0; _index[19].end = 0;
	_index[20].pro = "��"; _index[20].begin = 0; _index[20].end = 0;
	_index[21].pro = "��"; _index[21].begin = 0; _index[21].end = 0;
	_index[22].pro = "��"; _index[22].begin = 0; _index[22].end = 0;
	_index[23].pro = "��"; _index[23].begin = 0; _index[23].end = 0;
	_index[24].pro = "��"; _index[24].begin = 0; _index[24].end = 0;
	_index[25].pro = "��"; _index[25].begin = 0; _index[25].end = 0;
	_index[26].pro = "��"; _index[26].begin = 0; _index[26].end = 0;
	_index[27].pro = "��"; _index[27].begin = 0; _index[27].end = 0;
	_index[28].pro = "��"; _index[28].begin = 0; _index[28].end = 0;
	_index[29].pro = "��"; _index[29].begin = 0; _index[29].end = 0;
	_index[30].pro = "��"; _index[30].begin = 0; _index[30].end = 0;
	/**
	string str1 = "��", str2 = "��", str3 = "��", str4 = "��", str5 = "��", str6 = "��", str7 = "��", str8 = "��", str9 = "��";
	string str10 = "��", str11 = "��", str12 = "��", str13 = "��", str14 = "��", str15 = "³", str16 = "ԥ", str17 = "��";
	string str18 = "��", str19 = "��", str20 = "��", str21 = "��", str22 = "��", str23 = "��", str24 = "��", str25 = "��";
	string str26 = "��", str27 = "��", str28 = "��", str29 = "��", str30 = "��", str31 = "��";
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
			cout << "������������" << endl;
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

		i++;//���ﲻ������i++���������ѭ��
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
