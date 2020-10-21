#include <iostream>
#include <string.h>
#include <time.h>
#include<fstream>
using namespace std;

class Cafeteria
{
	public:
		int chooseuser();
		int owneroperations();
		int employeeoperations();
};

int Cafeteria::chooseuser()
{
	int choice;
	cout<<"Choose:\n1)Owner\n2)Employee"<<endl;
	cin>>choice;
	return (choice==1 || choice==2)?choice:0;
}

int Cafeteria::owneroperations()
{
	int choice;
	cout<<"Choose:\n1)Account Details\n2)Employee related operations\n3)Item Details"<<endl;
	cin>>choice;
	return (choice==1 || choice==2 || choice==3)?choice:0;
}

int Cafeteria::employeeoperations()
{
	int choice;
	cout<<"Choose:\n1)Add Bill\n2)Item Details"<<endl;
	cin>>choice;
	return (choice==1 || choice==2)?choice:0;
}

//---------------------------------------------------------------------------------------------------------------------------------

class Accounts: public Cafeteria
{
	private:
		float balance;
	public:
		int owneraccop()
		{
			int choice;
			cout<<"Choose:\n1)Add Bill\n2)Give Salary\n3)Deduct Expenses"<<endl;
			cin>>choice;
			return (choice==1 || choice==2 || choice==3)?choice:0;
		};
        void addBill(float amount)
		{
		    ofstream file;
            file.open("accounts.csv",ios::app);

		    file<<amount<<"  , "
		        <<"\n";
		    file.close();
		   cout<<"The balance has been updated"<<endl;
		};
		void giveSalarytoEmployee()
		{   float salary; string name;
		    cout<<"Enter the amount of salary and employee name to be given to the employee";
		    cin>>salary>>name;
		    ofstream file;
		    file.open("salary.csv",ios::app);
		    file<<name<<","
		        <<salary<<","

		        <<"\n";
		    cout<<"balance is updated"<<endl;
		};
		void deductExpenses(float amount)
		{
		    ofstream file;
            file.open("accounts.csv",ios::app);
		    file<<"-"<<amount<<","
		        <<"\n";
		    file.close();
		    cout<<"Expenses had been kept aside for next week."<<endl;
		};

};

//----------------------------------------------------------------------------------------------------------------------------------------

class Item: public Cafeteria,public Accounts// An object of the type item must be s=created for each item. Can use array of objects.
{
	private://Ingridieants required for the item
		int item_id;
		int price;
		char *ingridient1;
		float amt1;
		char *ingridient2;
		float amt2;
		char *ingridient3;
		float amt3;
		char *ingridient4;
		float amt4;
		char *ingridient5;
		float amt5;
		int stock;
	public:
		Item(int id,int p,char *i1,float a1,char *i2,float a2,char *i3,float a3,char *i4,float a4,char *i5,float a5)
		{
			item_id=id;
			price=p;
			ingridient1=i1;ingridient2=i2;ingridient3=i3;ingridient4=i4;ingridient5=i5;
			amt1=a1;amt2=a2;amt3=a3;amt4=a4;amt5=a5;
		};//constructor. Specified in main function by program. Owner or Employee cannot make changes.
		void personBoughtItem(){
		addBill(price);};
		void ingridientsForNextWeek(){
		    deductExpenses(amt1+amt2+amt3+amt4+amt5);
		};
};



//---------------------------------------------------------------------------------------------------------------------------------------------

class Employee: public Cafeteria,public Accounts//Create object of type employee
{
	private:
		int eid;
		char name[20];
		float salary;
		long phno;
	public:
		int empopp();
		void getData();//Owner
		void displayData();//Owner
		void addSalary(){giveSalarytoEmployee();};//Owner
};

void Employee::getData()
{
	cout<<"Enter employee id:";
	cin>>eid;
	cout<<"Enter name:";
	cin>>name;
	cout<<"Enter salary:";
	cin>>salary;
	cout<<"Enter phone number:";
	cin>>phno;
}

void Employee::displayData()
{
	cout<<"Id: "<<eid<<"\nName: "<<name<<"\nSalary: "<<salary<<"\nPhone number: "<<phno<<endl;
}


int Employee::empopp()
{
	int choice;
	cout<<"Choose:\n1)Enter employee data\n2)View Employee Data\n3)Give salary to employee"<<endl;
	cin>>choice;
	return (choice==1 || choice==2 || choice==3)?choice:0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	cout<<"Welcome to the Cafeteria!"<<endl;
	Cafeteria cafe;
	Accounts a;
	Employee e;
	while(1)
	{
	switch(cafe.chooseuser())
	{
	case 0:
		break;
	case 1:
	{
		switch(cafe.owneroperations())
		{
			case 0:
				break;
			case 1:
				{
					switch(a.owneraccop())
					{
					case 1:
					{
						float amt;
						cout<<"Enter Amount:";
						cin>>amt;
						a.addBill(amt);
						break;

					}
					case 2:
					{
						a.giveSalarytoEmployee();
						break;
					}
					case 3:
					{
						float amt;
						cout<<"Enter Amount:";
						cin>>amt;
						a.deductExpenses(amt);
						break;
					}
					}
					break;
				}
			case 2:
				{
					switch(e.empopp())
					{
					case 1:
						e.getData();
						break;
					case 2:
						e.displayData();
						break;
					case 3:
						e.addSalary();
						break;
					}
					break;
				}
			case 3:
				{
					Item item1(1,20,"a",1,"b",2,"",0,"",0,"",0);
					Item item2(2,50,"c",0.5,"a",1,"",0,"",0,"",0);
					int choice;
					cout<<"Do you want to buy item 1 or item 2?";
					cin>>choice;
					if(choice==1)
					{
						item1.personBoughtItem();
						item1.ingridientsForNextWeek();
					}
					else if(choice==2)
					{
						item2.personBoughtItem();
						item2.ingridientsForNextWeek();
					}
					break;
				}
		}
		break;
	}
	case 2:
	{
		switch(cafe.employeeoperations())
		{
			case 0:
				break;
			case 1:
				{
					float amt;
					cout<<"Enter Amount:";
					cin>>amt;
					a.addBill(amt);
					break;
				}
			case 2:
				{
					Item item1(1,20,"a",8,"b",5,"",0,"",0,"",0);
					Item item2(2,50,"c",0.5,"a",1,"",0,"",0,"",0);
					int choice;
					cout<<"Do you want to buy item 1 or item 2?";
					cin>>choice;
					if(choice==1)
					{
						item1.personBoughtItem();
						item1.ingridientsForNextWeek();
					}
					else if(choice==2)
					{
						item2.personBoughtItem();
						item2.ingridientsForNextWeek();
					}
					break;
				}
		}
	}
	break;
	}
	int choice;
	cout<<"Do you want to exit? Press 0"<<endl;
	cin>>choice;
	if(choice==0)
		break;
	}
	return 0;
}
