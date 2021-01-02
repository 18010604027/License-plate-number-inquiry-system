#include"pch.h"
#include"kmp.h"

void get_next(CString sub, int next[], int len)
{
	next[0] = 0;
	for (int i = 1, j = 0; i < len;)
	{
		if (sub[i] == sub[j])
		{
			next[i] = j;
			j++;
			i++;
		}
		else if (j == 0)
		{
			next[i] = 0;
			i++;
		}
		else
		{
			j = next[j];
		}
	}
}

bool kmp(CString s, CString sub)//, int pos = 0)
{
	int i = 0;
	int j = 0;
	int len = s.GetLength();
	int len2 = sub.GetLength();
	int* next = new int[len2];
	get_next(sub, next, len2);
	for (; i < len && j < len2;)
	{
		if (s[i] == sub[j])
		{
			i++;
			j++;
		}
		else if (j == 0)
		{
			i++;
		}
		else
		{
			j = next[j];
		}
	}
	delete[] next;
	if (j == len2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void deal_string(CString& sub, int* num_string)
{
	int len = sub.GetLength();
	int* num_cun = new int[len];
	int j = 0;

}