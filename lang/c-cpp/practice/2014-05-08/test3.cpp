#include <iostream>
#include <map>

using namespace std;

int func1(int*) {}

class Proto_Base{
public:
	typedef uint32_t Proto_Id; //定义协议号
	typedef int(*Callback)(int* message); //协议处理函数
	typedef map<Proto_Id, Callback> Proto_Call_List;
};


typedef uint32_t Proto_Id; //定义协议号
class Proto_Account:public Proto_Base{
public:
	const static Proto_Id PROTOID_REG = 100;
	const static Proto_Id PROTOID_LOGIN = 101;
	const static Proto_Id PROTOID_CHGPWD = 102;
	const static Proto_Id PROTOID_LOGOFF = 103;
	const static Proto_Id PROTOID_LIST = 104;
public:
	int reg(int* message){
		cout << "reg" << endl;
	}
	int login(int* message){
		cout << "login" << endl;
	}
	int chgpwd(int* message){
		cout << "chgpwd" << endl;
	}
	int logoff(int* message){
		cout << "logoff" << endl;
	}
	int list(int* message){
		cout << "list" << endl;
	}

	virtual void fill_list(Proto_Call_List& proto_call_list){
		proto_call_list.insert(Proto_Call_List::value_type( PROTOID_REG, &func1));
		//Callback c = this->reg;
		//proto_call_list[PROTOID_REG] = Proto_Account::reg;
		//proto_call_list.insert(Proto_Call_List::value_type( PROTOID_REG, &Proto_Account::reg));
		//proto_call_list.insert(Proto_Call_List::value_type( PROTOID_LOGIN, this->login));
		//proto_call_list.insert(Proto_Call_List::value_type( PROTOID_CHGPWD, this->chgpwd));
		//proto_call_list.insert(Proto_Call_List::value_type( PROTOID_LOGOFF, this->logoff));
		//proto_call_list.insert(Proto_Call_List::value_type( PROTOID_LIST, this->list));
	}
};

int main() {

	//Proto_Account pa;
	//int j=10;
	//typedef Proto_Account::Proto_Call_List MYProto_Call_List;
	//MYProto_Call_List* list = new MYProto_Call_List();
	//pa.fill_list( list);

	//if(list->begin() != list->end()) {
	//	MYProto_Call_List::iterator iter = list->begin();
	//	int i=0;
	//	for( ; iter < list->end(); iter++) {
	//		i++;
	//		iter->second( &i);
	//	}
	//}
	//int(Proto_Account::*c)(int*);
	//c = &Proto_Account::reg;
	//(pa.*c)(&j);
}
