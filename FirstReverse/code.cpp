#include <iostream>
using namespace std;

string FirstReverse(string str)
{
  int len = str.length();
  int tmp = 0;

  for(int i = 0; i < len/2;i++)
  {
	tmp = str[len-i-1];
	str[len-i-1] = str[i];
	str[i] = tmp;

	/**
	  OR:

	  string tmp = str;

	  for(int i = 0; i <  len;i++)
	  {
		str[i] = tmp[len-i-1];
	  }
	*/

  }

  return str;
}

int main(int argc, char *argv[])
{
	string str;

	cin >> str;
	cout << FirstReverse(str);

	return 0;
}
