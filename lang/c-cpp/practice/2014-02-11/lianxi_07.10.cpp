#include <iostream>
using namespace std;

struct Chan
{
	int data;
	Chan *next;
};

Chan *create();
void insert(Chan *&chanlist, Chan *item);
void del(Chan *&chanlist, Chan *item);
void print(Chan *chanlist);

int main()
{
	int i,n=10;
	Chan *chanlist=NULL,*item;
	for(i=0; i<n; i++)
	{
		item = create();
		insert(chanlist, item);
	}
	print(chanlist);
	item=chanlist;
	while(item!=NULL)
	{
		del(chanlist, item);
		item = item->next;
		print(chanlist);
	}
	return 0;
}

Chan *create()
{
	Chan *item = new Chan;
	item->next = NULL;
	cin >>item->data;
	return item;
}

void insert(Chan *&chanlist, Chan *item)
{
	Chan *tmp;
	if(chanlist == NULL)
	{
		chanlist = item;
	}
	else
	{
		tmp = chanlist;
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = item;
		item->next = NULL;
	}
}

void del(Chan *&chanlist, Chan *item)
{
	Chan *tmp;
	if(chanlist != NULL)
	{
		tmp = chanlist;
		while(tmp->next != NULL && tmp->next != item)
		{
			tmp = tmp->next;
		}
		if(tmp->next == item)
		{
			tmp->next = item->next;
			delete item;
		}
	}
	if(chanlist == item)
	{
		chanlist = item->next;
		delete item;
	}
}

void print(Chan *chanlist)
{
	Chan *item;
	cout <<"[";
	if(chanlist != NULL)
	{
		item = chanlist;
		do
		{
			cout <<item->data;
			if(item->next != NULL) cout <<",";
			item = item->next;
		}
		while(item != NULL);
	}
	cout <<"]";
	cout <<endl;
}
