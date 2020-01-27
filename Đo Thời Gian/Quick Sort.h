#pragma once
#include <Hoan Vi.h>

void QuickSort(int* MangNguon, int left, int right)
{
	int i = left;
	int j = right;
	int PhanTuGiua = MangNguon[(left + right) / 2];

	do
	{
		// Tìm vị trí i, j cần hoán vị
		while (MangNguon[i] < PhanTuGiua && i < right)
			i++;
		while (MangNguon[j] > PhanTuGiua && j > left)
			j--;

		if (i <= j)
		{
			HoanVi(MangNguon[i], MangNguon[j]);
			i++;
			j--;
		}
	} while (i <= j);

	// Khi đó PhanTuGiua sẽ chốt vị trí trong mảng
	// Ta cần gọi đệ quy đến 2 mảng con bên trái PhanTuGiua và bên phải PhanTuGiua
	if (left < j)
		QuickSort(MangNguon, left, j);

	if (i < right)
		QuickSort(MangNguon, i, right);
}