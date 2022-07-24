#include <iostream>
#include <string>

using namespace std;

string greet(string form, string lastname, string title, string::size_type pos, int length);

string greet(string form, string lastname, string title, string::size_type pos, int length) {
	string::size_type dpos;
	do{
		dpos = form.find( "Daisy");
		if( dpos == string::npos) {
			break;
		}
        form.replace(dpos, 5, lastname);
	}while( 1);

	do{
		dpos = form.find( "Ms");
		if( dpos == string::npos) {
			break;
		}
        form.replace(dpos, 2, title, pos, length);
	}while(1);
	return form;
}

int main() {
	string generic1( "Dear Ms Daisy:");
	string generic2( "MrsMsMissPeople");
	string lastName( "AnnaP");
	string salute = greet( generic1, lastName, generic2, 5, 4);
	cout << salute << endl;
	return 0;
}
