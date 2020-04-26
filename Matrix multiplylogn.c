#include <iostream>
using namespace std;

int t1[2][2];
int t2[2][2];
int t3[2][2];

int multi()
{
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++) {
			t3[i][j]=0;
			for (int k=0;k<2;k++)
				t3[i][j] += t2[i][k]*t2[k][j];
		}
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				t2[i][j]=t3[i][j];
}

int multip()
{
	multi();
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++) {
			t3[i][j]=0;
			for (int k=0;k<2;k++)
				t3[i][j] += t2[i][k]*t1[k][j];
		}
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				t2[i][j]=t3[i][j];
}

int power(int n)
{
	if (n<2)
		return 1;
	else if ((n%2)==0)
	{
		power(n/2);
		multi();
	}
	else
	{
	power(n/2);
	multip();
	}
}

int main() {
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++){
			cin>>t1[i][j];
			t2[i][j]=t1[i][j];
		}
	int n,x;
	cin>>n;
	x=power(n);
	for (int i=0;i<2;i++)
	{
		cout<<endl;
		for (int j=0;j<2;j++)
			cout<<t3[i][j]<<" ";
	}
return 0;
}