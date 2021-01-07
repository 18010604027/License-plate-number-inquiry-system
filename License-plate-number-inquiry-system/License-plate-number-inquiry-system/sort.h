#pragma once
#define px license
//快排
template <class T, class M>
void quick_sort(T* _First, T* _Last)
{
	//双边
	if (_First == _Last)
	{
		return;
	}
	T* mid = _First;
	T* las = _Last;
	T key;
	key.data = _First->data;
	while (mid != las)
	{
		int m = 0;
		while (mid != las && *las > key)las = las->pre;
		if (mid != las)
		{
			mid->data = las->data;
			mid = mid->next;
		}
		while (mid != las && !(*mid > key))mid = mid->next;
		if (mid != las)
		{
			las->data = mid->data;
			las = las->pre;
		}
	}
	mid->data = key.data;
	key.data = NULL;
	if (_First != mid)
	{
		quick_sort<T, M>(_First, mid->pre);
	}
	if (mid != _Last)
	{
		quick_sort<T, M>(mid->next, _Last);
	}

}

//基数排序
template <class T>
void RadixPass(T* source, T* pass, int num, int length, int(*NumChange)(int index, int num), int dig)
{
	int count[256];
	int pos[256];
	T* p, * p2;
	for (int j = 0; j < num; j++)
	{
		count[j] = 0;
	}
	p = source->next;
	while (p)
	{
		int bit = NumChange(dig, (p->data->px[dig]));
		p = p->next;
		count[bit]++;
	}

	pos[0] = 0;
	for (int i = 1; i < num; i++)
	{
		pos[i] = pos[i - 1] + count[i - 1];
	}

	//收集
	p = source->next;
	static int m = 0;
	for (int i = 0; i < length; i++)
	{
		int bit = NumChange(dig, (p->data->px[dig]));
		p2 = pass->next;
		for (int j = 0; j < pos[bit]; j++)
		{
			p2 = p2->next;
		}
		pos[bit]++;
		p2->data = p->data;
		p = p->next;
	}
	m++;
}

template <class T>
void radix(T* target, int length, const int* Num/*各位范围*/, int(*NumChange)(int index, int num), int maxlength = 0)
{
	T* copy, * p, * p_next, * p2;
	copy = new T;
	p = copy;
	p2 = target->next;
	for (int i = 0; i < length; i++)
	{
		p->next = new T;

		p = p->next;
		p->data = p2->data;
		p2 = p2->next;
	}
	p->next = NULL;
	int numlength;
	if (maxlength)
	{

		numlength = maxlength;

	}
	else
	{

		//numlength = maxnumlength(target, length);
	}

	for (int i = 0; i < numlength; i++)
	{

		if (i % 2 == 0)
		{
			RadixPass(target, copy, Num[numlength - i - 1], length, NumChange, numlength - i - 1);
		}
		else
		{
			RadixPass(copy, target, Num[numlength - i - 1], length, NumChange, numlength - i - 1);
		}

	}
	if ((numlength) % 2 != 0)
	{
		p = copy->next;
		p2 = target->next;
		int i = 0;
		while (p && p2)
		{
			p2->data = p->data;
			p2 = p2->next;
			p = p->next;
		}
	}
	p = copy;
	while (p)
	{
		p_next = p->next;
		delete p;
		p = p_next;
	}
}

template <class T>
void RadixPass_temp(T* space, T* copy_space, int source, int pass, int num, int length, int(*NumChange)(int index, int num), int dig)
{
	int count[256];
	int pos[256];
	int p, p2;
	for (int j = 0; j < num; j++)
	{
		count[j] = 0;
	}
	p = space[source].next;
	while (p)
	{
		int bit = NumChange(dig, (space[p].data->px[dig]));
		p = space[p].next;
		count[bit]++;
	}

	pos[0] = 0;
	for (int i = 1; i < num; i++)
	{
		pos[i] = pos[i - 1] + count[i - 1];
	}

	//收集
	p = space[source].next;
	static int m = 0;
	for (int i = 0; i < length; i++)
	{
		int bit = NumChange(dig, (space[p].data->px[dig]));
		p2 = copy_space[pass].next;
		for (int j = 0; j < pos[bit]; j++)
		{
			p2 = copy_space[p2].next;
		}
		pos[bit]++;
		copy_space[p2].data = space[p].data;
		p = space[p].next;
	}
	m++;
}

template <class T>
void radix_temp(T* space, int target, int length, const int* Num/*各位范围*/, int(*NumChange)(int index, int num), int maxlength = 0)
{
	T* copy_space;
	int copy, p, p_next, p2;
	copy_space = new T[length + 1];
	copy = 1;
	p = copy;
	p2 = space[target].next;
	for (int i = 1; i < length + 1; i++)
	{
		copy_space[i].next = i + 1;
	}
	copy_space[length].next = NULL;
	int numlength;
	if (maxlength)
	{

		numlength = maxlength;

	}
	else
	{

		//numlength = maxnumlength(target, length);
	}

	for (int i = 0; i < numlength; i++)
	{

		if (i % 2 == 0)
		{
			RadixPass_temp(space, copy_space, target, copy, Num[numlength - i - 1], length, NumChange, numlength - i - 1);
		}
		else
		{
			RadixPass_temp(copy_space, space, copy, target, Num[numlength - i - 1], length, NumChange, numlength - i - 1);
		}

	}
	if ((numlength) % 2 != 0)
	{
		p = copy_space[copy].next;
		p2 = space[target].next;
		int i = 0;
		while (p && p2)
		{
			space[p2].data = copy_space[p].data;
			p2 = space[p2].next;
			p = copy_space[p].next;
		}
	}
	delete[] copy_space;
}
