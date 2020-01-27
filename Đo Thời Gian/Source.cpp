#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string>

#include <Interchange Sort.h>
#include <Quick Sort.h>
#include <Radix Sort.h>

#include <iostream>
using namespace std;

// n là số lượng các số được Random
// số sẽ random trong đoạn [a, b]
// KieuPhatSinh = 1: các số tăng dần, 2: các số giảm dần, 3: các số ngẫu nhiên
void PhatSinhDaySo(int SoLuong, int SoBatDau, int SoKetThuc, int KieuPhatSinh, const char* TenFile, const char* CheDoMoFile)
{
	FILE* f = fopen(TenFile, CheDoMoFile); // Mở tập tin để ghi

	if (KieuPhatSinh == 1)
	{
		for (int i = 1; i <= SoLuong; ++i)
			fprintf(f, "%d\n", i);
		cout << "\nDu lieu voi n la " << SoLuong << " va co kieu tang dan da duoc ghi vao file " << TenFile;
	}
	else if (KieuPhatSinh == 2)
	{
		for (int i = SoLuong; i >= 1; --i)
			fprintf(f, "%d\n", i);
		cout << "\nDu lieu voi n la " << SoLuong << " va co kieu giam dan da duoc ghi vao file " << TenFile;
	}
	else if (KieuPhatSinh == 3)
	{
		srand(time(0)); // Nếu để trong vòng lặp là sẽ bị cac số giống nhau

		for (int i = 1; i <= SoLuong; ++i)
		{
			int x = SoBatDau + rand() % (SoKetThuc - SoBatDau + 1);
			fprintf(f, "%d\n", x);
		}
		cout << "\nDu lieu voi n la " << SoLuong << " va co kieu ngau nhien da duoc ghi vao file " << TenFile;
	}
	
	
	fclose(f); // Đóng tập tin khi đã dùng xong để giải phóng bộ nhớ
}

// true: Nếu mở được tập tin và đọc dữ liệu thành công
// false: Nếu không mở được tập tin
bool DocDuLieuTuFile(const char* TenFile, const char* CheDoMoFile, int*& MangNguon, int SoLuong)
{
	FILE* f = fopen(TenFile, CheDoMoFile);

	if (f != NULL)
	{
		MangNguon = new int[SoLuong];

		for (int i = 0; i < SoLuong; ++i)
			fscanf(f, "%d", &MangNguon[i]);

		fclose(f);
		return true;
	}

	cout << "Khong tim thay tap file " << TenFile;
	return false;
}

void XuatFileDaSapXep(int* MangNguon, int SoLuong, const char* TenFile, const char* CheDoMoFile)
{
	FILE* f = fopen(TenFile, CheDoMoFile); // Mở tập tin để ghi

	for (int i = 0; i < SoLuong; ++i)
		fprintf(f, "%d\n", MangNguon[i]);

	fclose(f);
}

int main()
{
	FILE* f = fopen("Thoi Gian Chay Cac Thuat Toan\\Thoi Gian Chay Thuat Toan Radix Sort.txt", "w");
	fprintf(f, "\t\t\t\tRadix Sort");
	fprintf(f, "\nTap Du Lieu\tTang Dan\t\tGiam Dan\t\tNgau Nhien\tTrung Binh");

	for (int SoLuong = 1000; SoLuong <= 21000; SoLuong += 2000)
	{
		fprintf(f, "\n%d\t\t", SoLuong);

		// Tạo Tên File
		char buffer[6];
		_itoa(SoLuong, buffer, 10);

		char* s1 = new char[6];
		s1 = (char*)buffer;
		
		char* s2 = new char[6];
		s2 = (char*)".txt";

		int len1 = strlen(s1);
		int len2 = strlen(s2);

		char* TenFile = new char[len1 + len2 + 1]; // tạo ra s3 có độ dài vừa đủ cộng thêm 1 ký tự '\0'
		strcpy(TenFile, s1);

		char* s3 = TenFile + len1; // dịch chuyển con trỏ s3 ra sau để strcat chạy lẹ hơn
		strcat(s3, s2);

		// Đo thời gian thuật toán 3 lần => lấy trung bình
		double TongThoiGianChay = 0;

		for (int i = 1; i <= 3; ++i)
		{
			// Tạo dữ liệu và ghi vào file
			// PhatSinhDaySo(SoLuong, -1000, 1000, i, TenFile, "w"); // => Phát hiện Radix Sort không xử lý được số âm
			PhatSinhDaySo(SoLuong, 0, 1000, i, TenFile, "w");
			
			int* MangNguon;
			bool FileTonTai = DocDuLieuTuFile(TenFile, "r", MangNguon, SoLuong);

			if (FileTonTai)
			{
				// Xử lý sắp xếp và đo thời gian

				clock_t BatDau = clock() ;
				RadixSort(MangNguon, SoLuong);
				clock_t KetThuc = clock();

				// Tính theo mili giây
				double ThoiGianChay = double(KetThuc - BatDau);  // / CLOCKS_PER_SEC;
				TongThoiGianChay += ThoiGianChay;

				// Dữ liệu thời gian được ghi ra file 
				fprintf(f, "%.4lf ms\t", ThoiGianChay);
				cout << "\nVoi n = " << SoLuong << " => Radix Sort chay lan " << i << " mat " << (size_t)ThoiGianChay << " ms";

				// Dữ liệu đã sắp xếp được ghi ra file
				XuatFileDaSapXep(MangNguon, SoLuong, TenFile, "w");
				delete[] MangNguon;
			}
		}

		fprintf(f, "%.4lf ms", TongThoiGianChay / 3);	
		cout << endl;
	}

	cout << "\nDu lieu ve thoi gian chay cua thuat toan da duoc ghi vao tap tin\n";
	fclose(f);

	system("pause");
	return 0;
}