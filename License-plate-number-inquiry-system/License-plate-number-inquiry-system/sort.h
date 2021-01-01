#pragma once

template <class T>
void quick_sort(T* _First, T* _Last)
{
	//Ë«±ß
	if (_First->next == _Last || _First == _Last)
	{
		return;
	}
	T* mid = _First->next;
	T* las = _Last;
	while (mid->next != las)
	{
		while (mid->next != las && *las > *_First)las = las->pre;
		{
			T::swap(*mid, *las);
		}
		while (mid->next != las && !(*mid > *_First))mid = mid->next;
		{
			T::swap(*mid, *las);
		}
	}
	if (*mid > *_First)
	{
		mid = mid->pre;
	}
	T::swap(*mid, *_First);
	quick_sort(_First, mid);
	quick_sort(mid->next, _Last);
}
