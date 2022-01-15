#include <iostream>
using namespace std;

int main() 
{
	int score;
	char s;
	cin >>score;

	if (score > 100 || score < 0) 
		cout <<"the score mast be 0-100" <<endl;
	switch (score/10)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5: s = 'E'; break;
		case 6: s = 'D'; break;
		case 7: s = 'C'; break;
		case 8: s = 'B'; break;
		case 9:
		case 10: s = 'A'; break;
		default : s = 'X';
	}
	cout <<"score:" <<s <<endl;
	return 0;
}
