#include<iostream>

using namespace std;

int main(void)
{
	string str;
	cin >> str;
	for(int i=0; i<str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
	cout << str << endl;
}
