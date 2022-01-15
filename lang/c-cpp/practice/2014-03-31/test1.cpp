#include <cstdint>
#include <iostream>
using namespace std;

void printBinary( const char val);

int main() 
{
	uint32_t num = 1024;
	int i, size = sizeof(num);
	char * val;
	cout <<"&num:" <<&num <<endl;
	cout <<"sizeof:" <<size <<endl;
	cout <<"reinterpret_cast<char*>(&num):" <<reinterpret_cast<char*>(&num) <<endl;
	cout <<"printBinary:";
	for( i=size-1,val=reinterpret_cast<char*>(&num); i>=0; i--)
	{
		printBinary( *(val+i));
	}
	cout <<endl;
	return 0;
}

void printBinary( const char val)
{
	for(int i=7; i>=0; --i)
	{
		if( val&(1<<i))
			cout<<"1";
		else
			cout<<"0";
	}
}
//
//void printBinary( const char val)
//{
//	for(int i=0; i<8; i++)
//	{
//		if( val&(1<<i))
//			cout<<"1";
//		else
//			cout<<"0";
//	}
//}
