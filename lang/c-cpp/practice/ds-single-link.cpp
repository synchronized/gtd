#include <iostream>
using namespace std;

struct Chain {
	int data;
	Chain *next;
};

Chain *create();
void insert(Chain *&chainlist, Chain *item);
void del(Chain *&chainlist, Chain *item);
void print(Chain *chainlist);

Chain *create() {
	Chain *item = new Chain;
	item->next = NULL;
	cin >>item->data;
	return item;
}

void insert(Chain *&chainlist, Chain *item) {
	Chain *tmp;
	if(chainlist == NULL) {
		chainlist = item;
	} else {
		tmp = chainlist;
		while(tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = item;
		item->next = NULL;
	}
}

void del(Chain *&chainlist, Chain *item) {
	Chain *tmp;
	if(chainlist != NULL) {
		tmp = chainlist;
		while(tmp->next != NULL && tmp->next != item) {
			tmp = tmp->next;
		}
		if(tmp->next == item) {
			tmp->next = item->next;
			delete item;
		}
	}
	if(chainlist == item) {
		chainlist = item->next;
		delete item;
	}
}

void print(Chain *chainlist) {
	Chain *item;
	cout <<"[";
	if(chainlist != NULL) {
		item = chainlist;
		do {
			cout <<item->data;
			if(item->next != NULL) cout <<",";
			item = item->next;
		}
		while(item != NULL);
	}
	cout <<"]";
	cout <<endl;
}

int main() {
	int i,n=10;
	Chain *chainlist=NULL,*item;
	for(i=0; i<n; i++) {
        item = create();
        insert(chainlist, item);
    }
	print(chainlist);
	item=chainlist;
	while(item!=NULL) {
        del(chainlist, item);
        item = item->next;
        print(chainlist);
    }
	return 0;
}
