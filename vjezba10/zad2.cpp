#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>
using namespace std;

struct point {
	int x, y;
	
	friend istream& operator>>(istream& is, point& p);
	friend ostream& operator<<(ostream& os, const point& p);
};

istream& operator>>(istream& is, point& p)
{
	is >> p.x >> p.y;
	return is;
}

ostream& operator<<(ostream& os, const point& p)
{
	os << p.x << " " << p.y;
	return os;
}

void funkcija(vector<point> v)
{
	ifstream fin("points.txt");

	istream_iterator<point> it(fin);
	istream_iterator<point> eop;
	copy(it, eop, back_inserter(v));

	ostream_iterator<point> it2(cout, "\n");
	copy(v.begin(), v.end(), it2);
	cout << endl;
}

int main()
{
	vector<point> v;
	funkcija(v);
	return 0;
}