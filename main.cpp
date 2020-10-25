#include <iostream>
#include <string.h>
#include <time.h>
#include<fstream>
#include<iomanip>
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
	cout<<"Choose:\n1)Add Bill\n2)Add Customer details/rating\n3)View Customer details/rating\n4)Item Details"<<endl;
	cin>>choice;
	return (choice==1 || choice==2 || choice==3 || choice==4)?choice:0;
}

//---------------------------------------------------------------------------------------------------------------------------------

class Accounts: public Cafeteria//Use static methods
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
		    cout<<"balance has been updated "<<endl;
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
		char *name;
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
	cout<<"Enter id,name,salary,phone number:";
	cin>>eid>>name>>salary>>phno;
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

class Customer {
private:
    int rating;

public:
    void getRating();
    void displayRating();
    void addtodatabase();

};

void Customer::getRating() {
}

void Customer::displayRating() {
}

void Customer::addtodatabase() {
}


int main()
{
	cout<<"Welcome to the Cafeteria!"<<endl;
	Cafeteria cafe;
	Accounts a;
	if(cafe.chooseuser()==1)
	{
		switch(cafe.owneroperations())
		{
			case 1:
				{

					if(a.owneraccop()==1)
					{
						float amt;
						cout<<"Enter Amount:";
						cin>>amt;
						a.addBill(amt);

					}
					else if(a.owneraccop()==2)
					{
						float amt;
						cout<<"Enter Amount:";
						cin>>amt;
						a.deductExpenses(amt);

					}
				}
			case 2:
				{
					Employee e;
					if(e.empopp()==1)
						e.getData();
					else if(e.empopp()==2)
						e.displayData();
					else if(e.empopp()==3)
						e.addSalary();
				}
			case 3:
				{
				    char ch1[20],ch2[20],ch3[20],ch4[20],ch5[20];
				    float a1,a2,a3,a4,a5,price;
				    cout<<"enter 5 ingredients for item 1"<<endl;
				    gets(ch1);gets(ch2);gets(ch3);gets(ch4);gets(ch5);
				    cout<<"enter the price"<<endl;
				    cin>>price;
				    cout<<"enter their amounts"<<endl;
				    cin>>a1>>a2>>a3>>a4>>a5;
					Item item1(1,price,ch1,a1,ch2,a2,ch3,a3,ch4,a4,ch5,a5);
					cout<<"enter 5 ingredients for item 1"<<endl;
				    gets(ch1);gets(ch2);gets(ch3);gets(ch4);gets(ch5);
				    cout<<"enter the price"<<endl;
				    cin>>price;
				    cout<<"enter their amounts"<<endl;
				    cin>>a1>>a2>>a3>>a4>>a5;
					Item item2(2,price,ch1,a1,ch2,a2,ch3,a3,ch4,a4,ch5,a5);
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
				}
		}
	}
	else if(cafe.chooseuser()==2)
	{
		switch(cafe.employeeoperations())
		{
			case 1:
				{
					float amt;
					cout<<"Enter Amount:";
					cin>>amt;
					a.addBill(amt);

				}
			case 2:
				{
					Customer c;
					c.getRating();
					c.addtodatabase();
				}
			case 3:
				{
					Customer c;
					c.displayRating();
				}
			case 4:
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
				}
		}
	}
}
