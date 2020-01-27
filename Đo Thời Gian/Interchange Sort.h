#pragma once
#include <Hoan Vi.h>

void InterchangeSort(int* MangNguon, int SoLuong)
{
	for (int i = 0; i < SoLuong - 1; i++)
		for (int j = i + 1; j < SoLuong; j++)
			if (MangNguon[i] > MangNguon[j])
				HoanVi(MangNguon[i], MangNguon[j]);
}