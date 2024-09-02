#include<bits/stdc++.h>
using namespace std;

int main(){
	int x, y, r;
	for(int i = 1; i <= 100000; i += 199){
		cout << "query " << i << " 0 " << i << " 100000" << endl;
		long double d;
		cin >> d;
		if(d > 0){
			cout << "query " << i+1 << " 0 " << i+1 << " 100000" << endl;
			long double d2;
			cin >> d2;

			d /= 2;
			d2 /= 2;

			int dx = round((d2*d2-d*d+1)/2);
			x = i+dx;

			r = round(sqrt((d2*d2-d*d+1)/2*(d2*d2-d*d+1)/2+d*d));
			break;
		}
	}
	for(int i = 1; i <= 100000; i += 199){
		cout << "query 0 " << i << " 100000 " << i << endl;
		long double d;
		cin >> d;
		if(d > 0){
			cout << "query 0 " << i+1 << " 100000 " << i+1 << endl;
			long double d2;
			cin >> d2;

			d /= 2;
			d2 /= 2;

			int dy = round((d2*d2-d*d+1)/2);
			y = i+dy;

			break;
		}
	}
	cout << "answer " << x << ' ' << y << ' ' << r << endl;
	return 0;
}
