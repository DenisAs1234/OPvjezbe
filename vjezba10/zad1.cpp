#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>
using namespace std;

bool podstr(string s)
{
	return s.find("es") != string::npos;
}

void funkcija(vector<string> v)
{
	ifstream fin("words.txt");

	istream_iterator<string> it(fin);
	istream_iterator<string> eos;
	copy(it, eos, back_inserter(v));

	ostream_iterator<string> it2(cout, "\n");
	copy(v.begin(), v.end(), it2);
	cout << endl;

	v.erase(remove_if(v.begin(), v.end(), podstr), v.end());
	copy(v.begin(), v.end(), it2);

	vector<int> pozicije;
	vector<string>::iterator iter;
	int br = 0;
	while (find(v.begin() + br, v.end(), "jabuka") != v.end())
	{
		iter = find(v.begin() + br, v.end(), "jabuka");
		br = distance(v.begin(), iter);
		pozicije.push_back(br);
		br++;
	}

	ostream_iterator<int> it3(cout, " ");
	copy(pozicije.begin(), pozicije.end(), it3);

	vector<string> v2(v.size());
	transform(v.begin(), v.end(), v2.begin(), ::toupper);
	copy(v2.begin(), v2.end(), it2);
}

int main()
{
	vector<string> v;
	funkcija(v);
}