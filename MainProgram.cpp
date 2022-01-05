/*
Mohamed kaid
CIS-230
Final Project
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include<fstream>
#include<stdlib.h>

using namespace std;

struct loginCredentials
{
	string id;
	string password;
};

struct badge
{
	string firstName;
	string lastName;
	string email;
	string age;
	string postion;
	string id;
	string password;
};


class Person
{
private:
	string firstName;
	string lastName;
	string email;
public:
	Person(string firstName, string lastName, string email)
	{
		this->firstName = firstName;
		this->lastName = lastName;
		this->email = email;
	}
	Person() {

	}
	string getFristName() { return firstName; }
	string getLastName() { return lastName; }
	string getEmail() { return email; }

	virtual void employeeCard()
	{
		ofstream idCard;
		idCard.open("card.txt");
		idCard << "FirstName: " << firstName << "\nLastName: " << lastName << "\nEmail: " << email << endl;
		idCard.close();


	}

};

class Transaction
{
private:
	Person customerInfo;
	string itemName;
	int units;
	double price;
	double tax;
	double total;
	string transactionDate;
public:
	Transaction() {};
	Transaction(string name, double price, string Date, Person customer)
	{
		this->customerInfo = customer;
		this->itemName = name;
		this->price = price;
		this->transactionDate = Date;
	}

	string getName() { return itemName; }
	int getUnits() { return units; }
	double getPrice() { return price; }
	double getTax() { return tax; }
	double getTotal() { return total; }
	string getTransactionDate() { return transactionDate; }

	void setName(string n) { itemName = n; }
	void setPrice(double pr) { price = pr; }
	void setTransactionDate(string Date) { this->transactionDate = Date; }
	void setUnits(int units) { this->units = units; }
	void setTax(double tax) { this->tax = tax; }
	void setTotal(double total) { this->total = total; }

	void display() {

		cout << "produt type: " << this->itemName << "," << this->units << "," << this->price << "," << this->tax
			<< "," << this->total << "," << this->transactionDate << endl;

	}

};


class Employee : public Person
{
private:
	string id;
	string age;
	string postion;
	string password;
	vector<Transaction> myItems;
public:
	Employee(string firstName, string lastName, string email, string age, string postion, string id, string password) :Person(firstName, lastName, email)
	{
		this->id = id;
		this->age = age;
		this->postion = postion;
		this->password = password;
	}
	string getID() { return id; }
	string getAge() { return age; }
	string getPosition() { return postion; }
	string getPassword() { return password; }

	virtual void employeeCard()
	{
		ofstream idCard;
		idCard.open("card.txt");
		idCard << "FirstName: " << getFristName() << "\nLastName: " << getLastName() << "\nEmail: " << getEmail() << "\nAge: " << getAge() << "\nPostion: " << postion << "\nID: " << id << "\nPassword: " << password << endl;
		idCard.close();

		ifstream find;
		find.open("card.txt");
		vector<badge>workCard;
		badge temp;
		while (getline(find, temp.firstName, '\n'))
		{
			getline(find, temp.lastName, '\n');
			getline(find, temp.email, '\n');
			getline(find, temp.age, '\n');
			getline(find, temp.postion, '\n');
			getline(find, temp.id, '\n');
			getline(find, temp.password);
			workCard.push_back(temp);
		}
		find.close();


	}
};

string getTadaDate();
bool regesterEmployee(vector<Employee>& ourRegEmp);
bool login(string id, string pass);
void addProducts(vector <Employee>& ourRegEmp, string empid);
void loadTransactions(vector<Transaction>& transactions);
void reportGenetration(vector<Transaction>& transactions);
void managerLobby(vector<Employee>& ourRegEmp, vector<Transaction>& transactions);
void addItem();
void employesLobby(vector<Employee>& ourRegEmp);

int main()
{


	vector<Employee> ourRegEmp;
	vector<Transaction> ourtransaction;

	int choice;
	do {
		

		while (1)
		{
			cout << "   ---------Welcome To Your C.S.O. System---------" << endl;
			cout << "press 1--->Empolyee \npress 2--->Mnager\nPress 0--->Logout\n   select >>";
			cin >> choice;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(123, '\n');
				cout << "Enter a Number from the Menu\n\n";
			}
			else if (choice == 1 || choice == 2 || choice == 0)
			{
				break;
			}
			else
				cout << "Invalid Entry Please Try again\n\n";
		}
		if (choice == 1) {
			employesLobby(ourRegEmp);
		}
		else if (choice == 2) {
			managerLobby(ourRegEmp, ourtransaction);
		}
		else if (choice == 0)
		{
			cout << "*****Thank You Have A Nice Day :)*****\n\n";
			return 0;
		}


	} while (choice != 0);


	return 0;
}


string getTadaDate() 
{
	time_t now = time(0);
	char* dt = ctime(&now);
	string todayDate = "";
	for (int x = 0; x < 10; x++) {
		todayDate = todayDate + dt[x];
	}
	return todayDate;

}

bool regesterEmployee(vector<Employee>& ourRegEmp) 
{
	string firstName; string lastName; string email; string age; string postion;
	string id, password;
	cout << "Enter firstname: ";
	cin >> firstName;
	cout << "Enter lastname: ";
	cin >> lastName;
	cout << "Enter email: ";
	cin >> email;
	cout << "Position: ";
	cin >> postion;
	cout << "Enter age: ";
	cin >> age;
	cout << "Enter an ID: ";
	cin >> id;
	cout << "Enter password: ";
	cin >> password;

	Employee emp(firstName, lastName, email, age, postion, id, password);

	ourRegEmp.push_back(emp);
	ofstream fout("employee.txt", ios::app);
	fout << emp.getID() << "," << emp.getPassword() << endl;
	fout.close();

	cout << "\tEmployee was added successfully\nID-> " << emp.getID() << ",\tPassword->" << emp.getPassword() << endl;

	return true;

}

bool login(string id, string pass) 
{

	ifstream find;
	try {
		find.open("employee.txt");
		if (!find.is_open()) {
			throw "file Not found\n\n";
		}

		vector< loginCredentials> empInfo;
		loginCredentials temp;


		while (getline(find, temp.id, ','))
		{
			getline(find, temp.password);
			empInfo.push_back(temp);
		}


		for (int x = 0; x < empInfo.size(); x++) {
			if (empInfo.at(x).id == id && empInfo.at(x).password == pass) {
				return true;
			}

		}

		return false;
	}
	catch (const char* msg) {
		cout << msg << endl;
		return false;
	}


}

void addProducts(vector <Employee>& ourRegEmp, string empid)
{
	int indexOfEmpoyees = 0;
	for (int x = 0; x < ourRegEmp.size(); x++) {
		if (ourRegEmp.at(x).getID() == empid) {
			indexOfEmpoyees = x;
		}
	}
	int choice;
	do {
		cout << "press 1 --->To add a item \npress 0 ---> Exit \n";
		cin >> choice;
	} while (choice != 0);

}

void loadTransactions(vector<Transaction>& transactions) 
{
	ifstream find("salesLogFile.txt");
	string stringTemp;
	int units;
	double price;
	double tax;
	double total;
	cin.ignore();
	while (getline(find, stringTemp, ':')) {
		Transaction temp;
		temp.setName(stringTemp);

		getline(find, stringTemp, ',');
		units = stoi(stringTemp);
		temp.setUnits(units);

		getline(find, stringTemp, ',');
		price = stod(stringTemp);
		temp.setPrice(price);

		getline(find, stringTemp, ',');
		tax = stod(stringTemp);
		temp.setTax(tax);

		getline(find, stringTemp, ',');
		total = stod(stringTemp);
		temp.setTotal(total);

		getline(find, stringTemp);
		temp.setTransactionDate(stringTemp);

		transactions.push_back(temp);

	}



}

void reportGenetration(vector<Transaction>& transactions) 
{
	string todayDate = getTadaDate();
	int choice;
	do {
		system("Cls");
		cout << "---------------Please select one from below --------------" << endl;
		cout << "press 1 --->to display today's report " << endl;
		cout << "press 2 --->to display  overall Report" << endl;
		cout << "press 0 --->to exit " << endl;
		cout << "   input >>";
		cin >> choice;

		if (choice == 1)
		{
			system("Cls");
			cout << "*************************************************************************************\n" << endl;
			cout << "_________________________________CSOS CITGO______________________________\n" << endl;
			cout << "_____________________Daily Report for the date " << todayDate << "______________________\n" << endl;
			cout << "*************************************************************************************\n" << endl;
			double totalSale = 0;
			double totalTax = 0;
			int counter = 1;
			for (int x = 0; x < transactions.size(); x++) {

				if (transactions.at(x).getTransactionDate() == todayDate) {
					cout << (counter) << " )  ";
					counter++;
					transactions.at(x).display();
					totalSale = totalSale + transactions.at(x).getTotal();
					totalTax = totalTax + transactions.at(x).getTax();
				}

			}
			cout << "*************************************************************************************\n" << endl;
			cout << "Total Sale        : $ " << totalSale << endl
				<< "total Tax        : $ " << totalTax << endl
				<< "total Sale + Tax : $ " << (totalSale + totalTax) << endl;
			cout << "*************************************************************************************\n" << endl;


			int x;
			cout << "Enter any Number to continue: ";
			cin >> x;
		}
		else if (choice == 2) {
			system("Cls");
			cout << "*************************************************************************************\n" << endl;
			cout << "______________________________CSOS Cash And Carry______________________________\n" << endl;
			cout << "_____________________ Report of overall transactions" << todayDate << "______________________\n" << endl;
			cout << "*************************************************************************************\n" << endl;
			double totalSale = 0;
			double totalTax = 0;
			int counter = 1;
			for (int x = 0; x < transactions.size(); x++) {

				if (transactions.at(x).getTransactionDate() == todayDate) {
					cout << (counter) << " )  ";
					counter++;
					transactions.at(x).display();
					totalSale = totalSale + transactions.at(x).getTotal();
					totalTax = totalTax + transactions.at(x).getTax();
				}

			}
			cout << "*************************************************************************************\n" << endl;
			cout << "Total Sale       : $ " << totalSale << endl
				<< "Total Tax        : $ " << totalTax << endl
				<< "Total Sale + Tax : $ " << (totalSale + totalTax) << endl;
			cout << "*************************************************************************************\n" << endl;

			int x;
			cout << "Enter any Number to continue: ";
			cin >> x;

		}
		//else if (choice == 0) {}

	} while (choice != 0);


}

void managerLobby(vector<Employee>& ourRegEmp, vector<Transaction>& transactions) 
{

	string id, pass;
	cout << "**For the sake of the project the id and password are**\n\t\tID:\t\tadmin\n\t\tPassword:\tadmin123\n\n";
	cout << "Please enter ID: ";
	cin >> id;
	cout << "Please enter Password: ";
	cin >> pass;
	int choice;
	if (id == "admin" && pass == "admin123") 
	{
		loadTransactions(transactions);

		do {
			system("Cls");

			cout << "---------------Admin Menu--------------" << endl;
			cout << "press 1 --->To add Employee " << endl;
			cout << "press 2 --->To display a report" << endl;
			cout << "press 0 --->To logout " << endl;
			cout << "   input >>";
			cin >> choice;
			if (choice == 1) 
			{
				regesterEmployee(ourRegEmp);
				ourRegEmp.back().employeeCard();
			}
			else if (choice == 2) 
			{
				reportGenetration(transactions);
			}
			else if (choice == 0) 
			{
				system("Cls");
				break;
			}
			else
			{
				cout << "Invalid";
			}
		} while (choice != 0);
	}
	else
	{
		cout << "Invalid Credentials\n" << endl;
	}


}

void addItem() 
{
	string firstName, lastName, email;
	
	cout << "Enter customer first name: ";
	cin >> firstName;
	cout << "Enter customer's last name:";
	cin >> lastName;
	cout << "Enter customer's email:";
	cin >> email;

	int choice;
	Person temp(firstName, lastName, email);
	ofstream fileWrite("salesLogFile.txt", ios::app);
	double amount;
	double units;
	double totalBill = 0;
	system("Cls");

	string todayDate = getTadaDate();

	cout << "----------------Product Type Menu---------------" << endl;
	int itemNumber = 0;
	do {
		while (1)
		{
			cout << "1. Tobacco\n2. Non-Taxable \n3. Taxable \n4. Gas\n0. exit \n   select >> ";
			cin >> choice;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(123, '\n');
				cout << "Enter a Number from the Menu\n\n";
			}
			else
				break;
		}
		
		if (choice == 1) 
		{
			itemNumber++;
			double taxRate = 0.06;
			while (1)
			{
				cout << "\nNumber of Tobacco units: ";
				cin >> units;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(123, '\n');
					cout << "Enter a Number\n\n";
				}
				else
					break;
			}

			while (1)
			{
				cout << "Enter price: $";
				cin >> amount;
				
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(123, '\n');
					cout << "Enter a Number\n\n";
				}
				else
					break;
			}
			cout << "-----------------------------------------\n\n";
			double thisTransactionPrice = amount * units;
			double tax = thisTransactionPrice * taxRate;
			thisTransactionPrice = thisTransactionPrice + tax;
			totalBill = totalBill + thisTransactionPrice;
			fileWrite << "Tobacco:" << units << "," << amount << "," << tax << "," << thisTransactionPrice << "," << todayDate << endl;



		}
		else if (choice == 2) {
			itemNumber++;
			double taxRate = 0.00;
			while (1)
			{
				cout << "\nNumber of Non-Taxable units: ";
				cin >> units;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(123, '\n');
					cout << "Enter a Number\n\n";
				}
				else
					break;
			}

			while (1)
			{
				cout << "Enter price: $";
				cin >> amount;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(123, '\n');
					cout << "Enter a Number\n\n";
				}
				else
					break;
			}
			cout << "-----------------------------------------\n\n";

			double thisTransactionPrice = amount * units;
			double tax = 0.0;
			thisTransactionPrice = thisTransactionPrice + tax;
			totalBill = totalBill + thisTransactionPrice;
			fileWrite << "Non-Taxable:" << units << "," << amount << "," << tax << "," << thisTransactionPrice << "," << todayDate << endl;
		}
		else if (choice == 3) {
			itemNumber++;

			double taxRate = 0.06;
			while (1)
			{
				cout << "\nNumber of Taxable units: ";
				cin >> units;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(123, '\n');
					cout << "Enter a Number\n\n";
				}
				else
					break;
			}

			while (1)
			{
				cout << "Enter price: $";
				cin >> amount;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(123, '\n');
					cout << "Enter a Number\n\n";
				}
				else
					break;
			}

			double thisTransactionPrice = amount * units;
			double tax = thisTransactionPrice * taxRate;
			thisTransactionPrice = thisTransactionPrice + tax;
			totalBill = totalBill + thisTransactionPrice;
			fileWrite << "Taxable:" << units << "," << amount << "," << tax << "," << thisTransactionPrice << "," << todayDate << endl;
			cout << "\n-----------------------------------------\n\n";


		}
		else if (choice == 4) {
			itemNumber++;

			double taxRate = 0.00;
			int type;
			cout << "---------- Chose the type of Gas --------" << endl;
			do {
				cout << "1.Regular\n2.Premium\n0.exit\n  select >>";

				cin >> type;
				if (type == 1) 
				{
					while (1)
					{
						cout << "\nEnter the number of Gallons of Regular(Price of Reg. is $2.50): ";
						cin >> units;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(123, '\n');
							cout << "Enter a Number\n\n";
						}
						else
							break;
					}
					amount = 2.50;
					double thisTransactionPrice = amount * units;
					double tax = 0.0;
					thisTransactionPrice = thisTransactionPrice + tax;
					totalBill = totalBill + thisTransactionPrice;
					fileWrite << "Gas Regular:" << units << "," << amount << "," << tax << "," << thisTransactionPrice << "," << todayDate << endl;

					cout << "\n-----------------------------------------\n\n";


				}
				else if (type == 2) 
				{

					while (1)
					{
						cout << "\nEnter the number of Gallons of Premium(Price of Premium is $3.50): ";
						cin >> units;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(123, '\n');
							cout << "Enter a Number\n\n";
						}
						else
							break;
					}
					amount = 3.50;
					double thisTransactionPrice = amount * units;
					double tax = 0.0;
					thisTransactionPrice = thisTransactionPrice + tax;
					totalBill = totalBill + thisTransactionPrice;
					fileWrite << "Gas Premium:" << units << "," << amount << "," << tax << "," << thisTransactionPrice << "," << todayDate << endl;
					cout << "\n-----------------------------------------\n\n";

				}
				else if (type == 0) {
					itemNumber--;

					cout << "-----------------------\n\n\n";
					break;
				}
				else {
					cout << "\n\n------------invalid type try again--------\n\n " << endl;
				}
			} while (type < 1 || type >2);
		}
		else if (choice == 0) {
			fileWrite.close();
		}
		else
		{
			cout << "\n\n------------invalid type try again-------- \n" << endl;

		}


	} while (choice != 0);

	cout << "Total number of transaction: " << itemNumber << ", Total price: $" << totalBill << endl;
	int x;
	cout << "\n\nEnter 0 to continue: ";
	cin >> x;





}

void employesLobby(vector<Employee>& ourRegEmp) 
{
	int choice;

	string password, id;
	while (1)
	{
		cout << "Enter your emploee ID: ";
		cin >> id;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(123, '\n');
			cout << "Enter a Number\n\n";
		}
		else
			break;

	}
	while (1)
	{
		cout << "Enter your Password: ";
		cin >> password;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(123, '\n');
			cout << "Enter a Number from the Menu\n\n";
		}
		else
			break;
	}
	if (login(id, password)) {
		int choice;
		system("Cls");
		do {
			
			while (1)
			{
				cout << "---------------Employee Menu --------------" << endl;
				cout << "press 1---> to add item " << endl;
				cout << "press 0---> to logout " << endl;
				cout << "   input >>";
				cin >> choice;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(123, '\n');
					cout << "Enter a Number from the Menu\n\n";
				}
				else
					break;
			}
			if (choice == 1) 
			{
				system("Cls");
				cout << "--------------- Add Item Menu--------------\n\n";
				addItem();
			}
			else if (choice == 0) 
			{
				break;
			}
			else
			{
				cout << "__________________Invalid____________________" << endl;
			}
		} while (choice != 0);
	}
	else 
	{
		cout << "Invalid Credentials\n" << endl;
	}


}
