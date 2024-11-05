#include<iostream>
#include<cstring>
using namespace std;
class Person 
{
 protected: string name;
            int age;
 public: Person():name("Unknown"), age(0) {}
         Person(string n, int a):name(n), age(a) {}
		 Person(const Person &p):name(p.name), age(p.age) {}
		 virtual void display()
		 {
          cout<<"Name: "<<name<<", Age: "<<age<<endl;
         }
};
class Employee;
void displaySalary(Employee &e);
class Employee:public Person 
{
 private: int empId;
          double salary;
          static int count; 
 public: Employee(string n="Abhi", int a=33, int id=111, double sal=0.0): Person(n, a), empId(id), salary(sal) 
         {
          count++;
         }
		 Employee(const Employee &e):Person(e), empId(e.empId), salary(e.salary) 
		 {
          count++;
         }
		 static int getCount() 
		 {
          return count;
         }
		 friend void displaySalary(Employee &e);
		 void setSalary(double sal) 
		 {
          salary=sal;
         }
		 void setSalary(double base, double bonus) 
		 {
          salary=base+bonus;
         }
		 Employee operator++() 
		 { 
          ++age;
          return *this;
         }
		 Employee operator+(const Employee &e)
		 {
          Employee temp;
          temp.salary=this->salary+e.salary;
          return temp;
        }
		double operator[](int index)  
		{
         return(index==0)?salary:0.0;
        }
		virtual void display()
		{
         Person::display();
         cout<<"Employee ID: "<<empId<<", Salary: "<<salary<<endl;
        }
		~Employee() 
		{
         count--;
        }
};

int Employee::count=0;
void displaySalary(Employee &e) 
{
 cout<<"Salary: "<<e.salary<<endl;
}
class Manager:public Employee 
{
 private: int teamSize;
 public: Manager(string n, int a, int id, double sal, int team): Employee(n, a, id, sal), teamSize(team) {}
         Manager(int team=0):Employee("Manager", 40, 0, 50000.0), teamSize(team) {}
		 void display()
		 {
          Employee::display();
          cout<<"Team Size: "<<teamSize<<endl;
         }
};
class Department 
{
 protected: string deptName;
 public: Department(string dept="General"):deptName(dept) {}
         void showDepartment() 
		 {
         cout<<"Department: "<<deptName<<endl;
         }
};
class HR:public Employee, public Department 
{
 private: int hrRating;
 public: HR(string n, int a, int id, double sal, string dept, int rating): Employee(n, a, id, sal), Department(dept), hrRating(rating) {}
         void display()
		 {
          Employee::display();
          showDepartment();
          cout<<"HR Rating: "<<hrRating<<endl;
         }
};
class Payroll 
{
 private: double *bonus;
 public: Payroll(double b) 
         {
          bonus=new double(b);
         }
		 ~Payroll()
		 {
          delete bonus;
         }
		 void showBonus()
		 {
          cout<<"Bonus: "<<*bonus<<endl;
         }
};
int main() 
{
 cout<<"Total Employees before creation: "<<Employee::getCount()<<endl;
 Employee emp1("Rashmitha", 28, 101, 30000);
 Manager mgr("Sanath", 35, 102, 60000, 5);
 emp1.setSalary(30000);
 emp1.setSalary(30000, 5000);
 emp1.display();
 mgr.display();
 Employee emp2(emp1);
 cout<<"\nEmployee copied using Copy Constructor:"<<endl;
 emp2.display();
 displaySalary(emp1);
 ++emp1; 
 Employee emp3=emp1+emp2;
 cout<<"\nAfter incrementing age using Unary Operator:"<<endl;
 emp1.display();
 cout<<"\nNew Employee after Salary addition using Binary Operator:"<<endl;
 emp3.display();
 cout<<"Accessing Salary with subscript operator: "<<emp1[0]<<endl;
 Payroll payroll(5000);
 payroll.showBonus();
 HR hr("Sushan", 30, 103, 45000, "HR", 9);
 cout<<"\nHR Details (Hybrid Inheritance):"<<endl;
 hr.display();
 cout<<"\nTotal Employees after creation: "<<Employee::getCount()<<endl;
 return 0;
}

