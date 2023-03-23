#include<iostream>
#include<fstream>

using namespace std;

class store
{
	private:
		int code;
		string name;
		float price;
		float dis;
	public:
		void menu();
		void admin();
		void buyer();
		void add();
		void edit();
		void del();
		void list();
		void receipt();
};

void store::menu()
{
	start:
	int ch;	
	string email;
	string pwd;
	cout<<"\t\t========================================\n";
	cout<<"\t\t                Store Menu              \n";
	cout<<"\t\t========================================\n";
	cout<<"\t\t\t\t1) Admin  \n";
	cout<<"\t\t\t\t2) Buyer  \n";
	cout<<"\t\t\t\t3) Exit  \n";
	cout<<"\t\t\t\tPlease select : ";
	cin>>ch;

	switch(ch)
	{
		case 1:	cout<<"\t\t Login \n";
				cout<<"\t\t Email : ";
				cin>>email;
				cout<<"\t\t Password : ";
				cin>>pwd;

				if(email=="admin@email.com" && pwd=="admin@1234")
				{
					admin();
				}
				else
				{
					cout<<"\t\t Invalid email or password \n";
				}
				break;
		case 2: buyer();
				break;
		case 3:	exit(0);
		default:cout<<"\t\tSelect a valid option\n";
	}
	goto start;
}

void store::admin()
{
	start:
	int ch;
	cout<<"\t\t========================================\n";
	cout<<"\t\t                Admin Menu              \n";
	cout<<"\t\t========================================\n";
	cout<<"\t\t\t\t1) Add Product  \n";
	cout<<"\t\t\t\t2) Modify Product  \n";
	cout<<"\t\t\t\t3) Delete Product  \n";
	cout<<"\t\t\t\t4) List Product  \n";
	cout<<"\t\t\t\t5) Back to Main Menu  \n";
	cout<<"\t\t\t\tPlease select : ";
	cin>>ch;
	switch(ch)
	{
		case 1:	add();
				break;
		case 2:	edit();
				break;
		case 3:	del();
				break;
		case 4:	list();
				break;
		case 5:	menu();
				break;
		default:cout<<"\t\tSelect a valid option\n";
	}
	goto start;
}

void store::buyer()
{
	start:
	int ch;
	cout<<"\t\t========================================\n";
	cout<<"\t\t                Buyer Menu              \n";
	cout<<"\t\t========================================\n";
	cout<<"\t\t\t\t1) Buy Product  \n";
	cout<<"\t\t\t\t2) Back to Main Menu  \n";
	cout<<"\t\t\t\tPlease select : ";
	cin>>ch;
	switch(ch)
	{
		case 1:	receipt();
				break;
		case 2:	menu();
				break;
		default:cout<<"Select a valid option\n";
	}
	goto start;
}

void store::add()
{
	start:
	fstream data;
	int c;
	int token=0;
	float p;
	float d;
	string n;
	cout<<"\t\t========================================\n";
	cout<<"\t\t               Add Product              \n";
	cout<<"\t\t========================================\n";
	cout<<"\t\t\t\tProduct Code : ";
	cin>>c;
	cout<<"\t\t\t\tProduct Name : ";
	cin>>n;
	cout<<"\t\t\t\tPrice : ";
	cin>>p;
	cout<<"\t\t\t\tDiscount : ";
	cin>>d;

	data.open("database.txt",ios::in);
	if(!data)
	{
		data.open("database.txt",ios::app|ios::out);
		data<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<endl;
		data.close();
	}
	else
	{
		data>>code>>name>>price>>dis;
		while(!data.eof())
		{
			if(c==code)
			{
				token++;
			}
			data>>code>>name>>price>>dis;
		}
		data.close();
	}

	if(token==1)
		goto start;
	else
	{
		data.open("database.txt",ios::app|ios::out);
		data<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<endl;
		data.close();
	}
	cout<<"\t\tRecord Added\n";
}

void store::edit()
{
	fstream d1,d2;
	int key;
	int token=0;
	int c;
	float p;
	float d;
	string n;
	cout<<"\t\tModify Product\n";
	cout<<"\t\tProduct Code : ";
	cin>>key;
	d1.open("database.txt",ios::in);
	if(!d1)
	{
		cout<<"\t\tProduct doesn't exist\n";
	}
	else
	{
		d2.open("tmp.txt",ios::app|ios::out);
		d1>>code>>name>>price>>dis;
		while(!d1.eof())
		{
			if(key==code)
			{
				cout<<"\t\tNew Product Code : ";
				cin>>c;
				cout<<"\t\tNew Product Name : ";
				cin>>n;
				cout<<"\t\tNew Product Price : ";
				cin>>p;
				cout<<"\t\tNew Product Discount : ";
				cin>>d;	
				d2<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<endl;
				cout<<"\t\tProduct Updated\n";
				token++;
			}
			else
			{
				d2<<" "<<code<<" "<<name<<" "<<price<<" "<<dis<<endl;
			}
			d1>>code>>name>>price>>dis;
		}
		d1.close();
		d2.close();
		remove("database.txt");
		rename("tmp.txt","database.txt");

		if(token==0)
		{
			cout<<"\t\tProduct Not Found\n";
		}
	}
}

void store::del()
{
	fstream d1,d2;
	int key;
	int token;
	int c;
	float p;
	float d;
	string n;
	cout<<"\t\tDelete Product\n";
	cout<<"\t\tProduct Code : ";
	cin>>key;
	d1.open("database.txt",ios::in);
	if(!d1)
	{
		cout<<"\t\tProduct doesn't exist\n";
	}
	else
	{
		d2.open("tmp.txt",ios::app|ios::out);
		d1>>code>>name>>price>>dis;
		while(!d1.eof())
		{
			if(key==code)
			{
				cout<<"\t\tProduct Deleted\n";
				token++;
			}
			else
			{
				d2<<" "<<code<<" "<<name<<" "<<price<<" "<<dis<<endl;
			}
			d1>>code>>name>>price>>dis;
		}
		d1.close();
		d2.close();
		remove("database.txt");
		rename("tmp.txt","database.txt");

		if(token==0)
		{
			cout<<"\t\tProduct Not Found\n";
		}
	}
}

void store::list()
{
	fstream data;
	data.open("database.txt",ios::in);
	cout<<"\t\t========================================\n";
	cout<<"\t\tCode\tName\tPrice\tDiscount\n";
	cout<<"\t\t========================================\n";
	data>>code>>name>>price>>dis;
	while(!data.eof())
	{
		cout<<"\t\t"<<code<<"\t"<<name<<"\t"<<price<<"\t"<<dis<<endl;
		data>>code>>name>>price>>dis;
	}
	data.close();
}

void store::receipt()
{
	fstream data;
	int arrc[100];
	int arrq[100];
	char ch;
	int i=0;
	float amt=0;
	float dist=0;
	float total=0;

	cout<<"\t\t\t\tRECEIPT\n";
	data.open("database.txt",ios::in);
	if(!data)
	{
		cout<<"\t\tEmpty Database\n";
	}
	else
	{
		data.close();
		list();

		do
		{
			cout<<"\t\tProduct Code : ";
			cin>>arrc[i];
			cout<<"\t\tQuantity : ";
			cin>>arrq[i];
			for(int j=0;j<i;j++)
			{
				if(arrc[i]==arrc[j])
				{
					cout<<"\t\tDuplicate Product Code\n";
					//goto 
				}
			}
			i++;
			cout<<"\t\tContinue Shopping : ";
			cin>>ch;
		}while(ch=='y');
		cout<<"\t\t=======================================================\n";
		cout<<"\t\tNo\tName\tQty\tPrice\tDiscount\tAmount\n";
		for(int j=0;j<i;j++)
		{
			data.open("database.txt",ios::in);
			data>>code>>name>>price>>dis;
			while(!data.eof())
			{
				if(arrc[j]==code)
				{
					amt=price*arrq[j];
					dist=(amt*dis/100);
					total=total+(amt-dist);
					cout<<"\t\t"<<code<<"\t"<<name<<"\t"<<arrq[j]<<"\t"<<price<<"\t"<<dist<<"\t"<<amt-dist<<endl;
				}
				data>>code>>name>>price>>dis;
			}
			data.close();
		}
	}
	cout<<"\t\t=======================================================\n";
	cout<<"\t\t\t\tTOTAL AMOUNT : "<<total<<endl;
	cout<<"\t\t=======================================================\n";
}

int main()
{
	store s;
	s.menu();
}