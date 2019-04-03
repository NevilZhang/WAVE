#include<math.h>
using namespace std;
#define PI 3.14159


void swap(complex<double> &a, complex<double> &b)
{
	complex<double> t;
	t = a;
	a = b;
	b = t;
}


////////////////////////////////////////////////////////////////����
void bitrp(vector<complex<long double>> Tdata, int n)
{
	// λ��ת�û� Bit-reversal Permutation
	int i, j, a, b, p;
	for (i = 1, p = 0; i < n; i *= 2)
	{
		p++;							//ͳ���������ݽ״�
	}
	for (i = 0; i < n; i++)
	{
		a = i;
		b = 0;
		for (j = 0; j < p; j++)
		{
			b = (b << 1) + (a & 1);     // b����һλ��a���λ���������
			a >>= 1;					 // a����һλ
		}
		if (b > i)
		{
			swap(Tdata[b], Tdata[i]);
		}
	}

}
////////////////////////////////////////////////////����Ҷ�任
bool FFT(vector<complex<long double>> X, int n) {
	
	int i = n,count = 0;
	vector<complex<long double>> weight;
	while (i > 1)
	{
		if (i % 2)
		{
			return false;
		}
		i /= 2;
	}
	for (int i = 0, double angle=0; i < n / 2; i++) {
		angle = -i*PI * 2 / n;//��IFFT����������
		weight.push_back(complex<long double>(cos(angle), sin(angle)));
	}
	bitrp(X, n);		//��������е������
	for (i = 1; i<n; i <<= 1)
	{
		count++;
	}
	int p = n;
	for (int l= 1; l <= count; l++) {
		p /= 2;



	}

}

////////////////////////////////////////////////////sgn����
int sgn(long double X) {
	/*
	function:sgn����
	*/
	return (X >= 0) ? 1 : -1;
}
