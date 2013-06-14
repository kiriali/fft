#include<iostream>
#define Pi 3.14159
#define Two 2
#define One 1

using namespace std;

double* b2fft(double x0[],double x1[])
{
	int X_len = (sizeof(x0)>sizeof(x1))?(sizeof(x1)):(sizeof(x0));
	double *X = new double[X_len];
	int len;
	cout<<"intput len(l<=10) = "<<endl;
	cin>>len;
	/*求逆序列*/
	int M = int(pow((double)Two,len));
	for(int j=1; j<M; j++)
	{
		int i=0;
		int s = M/2;
		while(i>=s)
		{
			i = i-s;
			s = s/2;
		}
		i = i+s;
		if(j<i)
		{
			double temp;
			temp = x0[j];
			x0[j] = x0[i];
			x0[i] = temp;
			temp = x1[j];
			x1[j] = x1[i];
			x1[i] = temp;
		}
	}
	/*碟式运算处理x0,x1*/
	int r,m1,m2,m3,m4,k1,k2;
	double u,v;
	int N = pow((double)Two,len);
	for(int i=1;i<len+1;i++)
	{
		m1 = pow((double)One,i-1);
		m2 = 2*m1;
		m3 = N/m2;
		for(int j=0;j<m3;j++)
		{
			m4 = j*m2;
			for(r=0;r<m1;r++)
			{
				k1 = m4 + r;
				k2 = k1 + m1;
				u = x0[k2]*cos(2*Pi*r/m2)+x1[k2]*sin(2*Pi*r/m2);
				v = x1[k2]*cos(2*Pi*r/m2)-x0[k2]*sin(2*Pi*r/m2);
				x0[k2] = x0[k1] - u;
				x1[k2] = x1[k1] - v;
				x0[k1] = x0[k1] + u;
				x1[k1] = x1[k1] = v;
			}
		}
	}

	for(int i=0;i<N; i++)
		X[i] = sqrt(x0[i]*x0[i]+x1[i]*x1[i]);
	return X;
}