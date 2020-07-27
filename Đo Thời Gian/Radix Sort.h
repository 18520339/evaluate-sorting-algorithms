#include <math.h>

int SoLonNhat(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max) max = arr[i];
	return max;
}

void CountSort(int* MangNguon, int SoLuong, int exp)
{
	int* MangDich = new int[SoLuong]; // MangDich
	int i, count[10] = {0};

	// Đếm có bao nhiêu số hạng chứa cơ số i ở hàng exp
	for (i = 0; i < SoLuong; i++)
		count[(MangNguon[i] / exp) % 10]++;

	// Khi xét Mảng Nguồn từ trên xuống, 
	// số đầu tiên có chữ số hàng exp là i 
	// thì được xếp vào vị trí count[i - 1] 
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Chuyển các số từ Mảng Nguồn sang Mảng Đích 
	for (i = SoLuong - 1; i >= 0; i--)
	{
		MangNguon[i];
		MangDich[count[(MangNguon[i] / exp) % 10] - 1] = MangNguon[i];
		count[(MangNguon[i] / exp) % 10]--;
	}

	// Nạp Lại Mảng Nguồn từ Mảng Đích được sắp xếp
	for (i = 0; i < SoLuong; i++)
		MangNguon[i] = MangDich[i];

	delete[] MangDich;
}

void RadixSort(int arr[], int n)
{
	// Xác định bao nhiêu chữ số để lặp
	int max = SoLonNhat(arr, n); 
	
	// Sắp xếp theo cơ số cho từng hàng
	for (int exp = 1; max / exp > 0; exp *= 10)
		CountSort(arr, n, exp);
}
