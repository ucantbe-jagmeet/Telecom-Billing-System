// TELEPHONE BILLING SYSTEM
// using bits/stdc++.h to include all the header files we would need
#include <bits/stdc++.h>
using namespace std;

// two file handlers
// file name is included as #include<fstream>
// fstream is a stream class to both read and write from/to files.
fstream f1,f2;
// Creating class bill
class bill
{
    // Member Declarations
    // username
	char FirstName[20];
	char LastName[20];
    // phone number
	unsigned long int phone_no;
    // customer ID
	long cust_id;
    // email
	char emailID[40];
    // address of customer
	char address[200];
    // bill status
	char status;
    // the price of local calls and std calls ,discounts and taxes
	float localprice,stdprice,discount,taxes;
    // time spent on local,std calls and amounts/net and outstandings
	float localtime,stdtime,amount,netamount,outstanding;

    // member function
    // the net amount calculator
	void calcnet()
	{
		amount=(localtime*localprice)+(stdtime*stdprice);
		netamount=(((amount*(1+taxes))*(1-discount))) +outstanding;
		outstanding=netamount;
	}
	public:
    // The constructor
	bill()
	{
        // setting all strings to have \0 char,and all other stuff like
        // phone,,id to 0 and Status Active and default local/std charges

		strcpy(FirstName,"\0");
		strcpy(LastName,"\0");
		phone_no=0;
		strcpy(emailID,"\0");
		strcpy(address,"\0");
		status='A';
		cust_id=0;
		localtime=stdtime=amount=netamount=outstanding=0.0;
		localprice=0.50;
		stdprice=1.00;
		discount=0.1;
		taxes=0.15;

	}
    // Member functions declarations :
	void input();
	void output();
	void pay();

    // Function to change the status
	void changestatus()
	{
	  if(outstanding>500)
	  {
	   status='U';
	  }
	  if(outstanding<500)
	  {
	  status='A';
      }
	}
    // member function to compare the phone number
	int comparenumber(unsigned long int ph)
	{
		if(ph==phone_no)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
    // member function to return customer id
	char returncustid()
	{
		return cust_id;
	}
    // member function to return the status
	char getstatus()
	{
	return status;
	}
};
// member functions defined outside the class with scope resolution :: operator

// input function to input customer details
void bill::input()
{

    cout<<endl;
		cout<<"Enter the first name of user: ";
		cin>>FirstName;
		cout<<endl;
		
        cout<<"Enter the last name of user: ";
		cin>>LastName;
		cout<<endl;

	    cout<<"Enter the phone no of user(7 digits): ";
		cin>>phone_no;
    cout<<endl;
		cout<<"Enter Customer ID: ";
		cin>>cust_id;
    cout<<endl;
		cout<<"Enter the email ID: ";
		cin>>emailID;
    cout<<endl;
		cin.ignore();
		cout<<"Enter the address of the user: ";
    // used getline to read unformatted string
		cin.getline(address,400,'\n');
    cout<<endl;
		cout<<"Enter Local Call Duration in minutes: ";
		cin>>localtime;
    cout<<endl;
		cout<<"Enter Std Call Duration in minutes: ";
		cin>>stdtime;
    cout<<endl;
    // Then calling the calcnet to calculate the deserved amount
		calcnet();
}
// Function to output the details of customers when called
void bill :: output()
{
        cout<<"******Customer Details******"<<endl<<endl;

		cout<<"Name : "<<FirstName<<" "<<LastName<<endl;
		cout<<"Phone No: "<<phone_no<<endl;
		cout<<"Customer ID: "<<cust_id<<endl;
		cout<<"Email ID: "<<emailID<<endl;
		cout<<"Address: "<<address<<endl;
		cout<<"Status ( A for Active and U for Deactive ) : "<<status<<endl;
		cout<<"Amount (Exlusive of Taxes & Discount): "<<amount<<endl;
		cout<<"Outstanding Amount for next month "<<outstanding<<endl;
		cout<<"Amount (Inclusive of Taxes & Discount): "<<netamount<<endl;

}
// Member function to handle the payment part of billing system when called
void bill::pay()
{
    // paid amount variable
	float paid;
	if(status=='U')
	{
		cout<<"\nYour Account is deactivated.\nYou have been fined Rs 100 for reactivation of your account"<<endl;
		netamount+=100;
	}
    // display the net amount

	cout<<"\nYour Net amount due is : "<<netamount<<" and outstandings is : "<<outstanding<<endl;
    if(netamount<=0){
        cout<<"\nYou are a great customer, Thanks for paying on time"<<endl<<endl;
        return;
    }
    // goto keyword -> to provide an unconditional jump from goto a to here
	a:
	cout<<"\nEnter the amount You wish to pay (0 to cancel): ";
	cin>>paid;
    cout<<endl;
    // if he entered 0 means no transaction
	if (paid==0)
	{
		cout<<"*******Transaction Cancelled*******"<<endl;
	}
    // if paid greater than or = to 80% of net amount
    // clear out and give the outstandings for next month
	else if (paid>=(0.8*netamount))
	{
		outstanding=netamount-paid;
		localtime=stdtime=amount=netamount=0.0;
		cout<<endl<<"*****Amount Paid = "<<paid<<"*****"<<endl;
		cout<<"\nYour Outstanding amount for next Month is: "<<outstanding<<endl;
    cout<<"\nBill will be updated for next month \n"<<endl;
	}
    // if less than 80% he said then give him the warning to pay min of 0.8 of net amount
    //  and jump back to a label using goto keyword
	else
	{
		cout<<"\n-------The Minimum amount to be paid is "<<0.8*netamount<<"---------"<<endl;
		cout<<"\nPlease pay this much amount for your connection to be active"<<endl;

		goto a;
	}

    // Change status depending on the outstandings
	changestatus();

}

// creating global instances of bill class b1,b2;
bill b1,b2;

// function to update the status
void updatestatus()
{
    // if there is no file handles named f1 means no records present yet
	if(!f1)
	{
		cout<<"No records Present"<<endl;
	}
    // f1 is for the bill records , f2 is for the telephone records
	else
	{
        // opening the files
        // ios::in means open the file for input operations
		f1.open("bill.dat",ios::in);
        // ios::out for output operations and ios::app for specifying
        // that all output operations are performed at end of file and the
        // content is appended to the current content of the file

        f2.open("te.dat",ios::out|ios::app);

        // seekg() functions allows to change the location of get positions
        // using this the get function is set to an offset value relative to
        // some specific point determined by parameter direction.
        // offset is of type streamoff

        // ios::beg makes the offset counted from begining of stream
		f1.seekg(0,ios::beg);

        // reading from file , providing the b1 bill object
		f1.read((char*)&b1, sizeof(b1));

        // until filehandle reaches end of file
		while(!f1.eof())
		{
            // change the status of the customer's bill
            b1.changestatus();

            // write the bill records to the file handler f2 named tel.dat
            f2.write((char*)&b1, sizeof(b1));

            // reading again from bill records and updating whenever required
            f1.read((char*)&b1, sizeof(b1));

		}
        // when reached the end
        // close all file handle connections to bill.dat and tel.dat
		f1.close();
		f2.close();
        // removing the bill records (clearing the buffers)
        // and renaming the te.dat as bill.dat
		remove("bill.dat");
		rename("te.dat","bill.dat");
        // status has updated
		cout<<"Status Updated"<<endl;

	}
}
// function to pay the bill based on the phone number entered by the user
// the phone number is our way to recognise the customer
void paybill(unsigned long int ph)
{
    // opening the bill.dat file using file handler f1
	f1.open("bill.dat",ios::in|ios::out);
	f1.seekg(0,ios::beg);

	f1.read((char*)&b1, sizeof(b1));
    // until we reach end of bill.dat file's bill records
	int count = 0;

	while(!f1.eof())
	{
        // comparing the phone number to check whether the customer exits
        // in our bill records
		if(b1.comparenumber(ph)==1)
		{
      // calling the pay member functions of b1 object to initiate the payment
			b1.pay();

			// updating the file
			f1.seekg(count*(sizeof(b1)),ios::beg);
			f1.write((char*)&b1,sizeof(b1));
		}
		f1.read((char*)&b1, sizeof(b1));
		count++;
	}
    // closing the file connection
	f1.close();
	}
// function to add record, provided by the admin
void addrecord()
{


    cout<<endl<<"=======Add Records======="<<endl<<endl;
	cout<<"Enter information of new user: "<<endl<<endl;
	b1.input();
    // opening the file bill.dat through f1 handle with output and append authority
	f1.open("bill.dat",ios::out|ios::app);
	f1.write((char*)&b1,sizeof(b1));
    // closing after writing to file
	f1.close();

	cout<<"***NEW RECORD ADDED***"<<endl;

}

// function to delete the records
void deleterecord()
{

	int ch,m,flag=0;
	unsigned long int ph;
    // Displaying sub menu
    cout<<endl;
	cout<<"*****SUB MENU - DELETION*****"<<endl;
    cout<<endl;
	cout<<" 1.Delete Using Customer ID"<<endl;
	cout<<" 2.Delete Using Phone number"<<endl;
    // goto label
	a1:
    cout<<"Enter choice (1/2) : ";
	cin>>ch;
	switch(ch)
	{
        // case 1 : to delete the record using customer id
		case 1:
		cout<<" \n Enter customer ID you want to delete: ";
		cin>>m;
        cout<<endl;
        // bill.dat file opening and temp.dat file
		f1.open("bill.dat",ios::in)  ;
		f2.open("temp.dat",ios::out|ios::app);
		f1.seekg(0,ios::beg);
		f1.read((char*)&b1,sizeof(b1));
        // if bill records no there display no records
		if(!f1)
		{
		cout<<"======No records present======"<<endl;
		}
		else
		{
        // until end of file
            while(!f1.eof())
            {
                // check if cutomer id matches with given
                // by using the member funciton returncustid() of b1 object
                if(b1.returncustid()!=m)
                {
                    // if not matches write to temp.dat file
                    f2.write((char*)&b1,sizeof(b1));
                }
                // if matches , we need to delete it
                if(b1.returncustid()==m)
                {
                   // raise the flag
                   flag=1;
                }
                // reading from file
                f1.read((char*)&b1,sizeof(b1));
            }
        }
        // closing connections
		f1.close();
		f2.close();
        // clearing record buffer
		remove("bill.dat");
        // renaming the temp file as new bill.dat file
		rename("temp.dat","bill.dat");
        // If flag is raised means record was deleted thus display message
		if(flag==1)
		{
			cout<<endl<<"*****Record Deleted*****"<<endl;
		}
        // If flag not raised means record was not present
		else
		{
			cout<<"-----Record not present-----"<<endl;
		}
		break;
        // case 2 : to delete record using phone number
		case 2:
		cout<<" \n Enter phone number you want to delete(7 digits): ";
		cin>>ph;
        cout<<endl;
        // opening files with appropriate rights
		f1.open("bill.dat",ios::in)  ;
		f2.open("temp.dat",ios::out|ios::app);
		f1.seekg(0,ios::beg);
		f1.read((char*)&b1,sizeof(b1));
        // not present if
		if(!f1)
		{
		cout<<"=====No records present====="<<endl;
		}
		else
		{
            // until end of file reached
            while(!f1.eof())
            {
                // comparing phone number using comparenumber method of b1 object
                // if non zeros write to b1 object details to temp.dat file
                if(b1.comparenumber(ph)!=0)
                {
                    f2.write((char*)&b1,sizeof(b1));
                }
                // if phone is 0 , raise the flag
                if(b1.comparenumber(ph)==0)
                {
                    flag=1;
                }
                f1.read((char*)&b1,sizeof(b1));
            }
		}
        // close connections
		f1.close();
		f2.close();
        // flag if raised
		if(flag==1)
		{
			cout<<"*****Record Deleted*****"<<endl;
		}
		else
		{
			cout<<"=====Record not present====="<<endl;
		}
        // clearing bill.dat and renaming temp.dat as new bill.dat
		remove("bill.dat");
		rename("temp.dat","bill.dat");
		break;
		default:
		cout<<"Invalid Choice Entered.....Please Retry"<<endl;
        // goto keyword
		goto a1;
	}

}

// display function to display records when admin calls
void display(unsigned long int ph=0)
	{
		if(ph!=0)
		{
			goto dis;
		}
		else
		{

			int ch,m;
            cout<<endl<<endl;
			cout<<"*****SUB MENU - DISPLAY*****"<<endl;
			cout<<" 1.Display All records"<<endl;
			cout<<" 2.Display unactivated connections"<<endl;
			cout<<" 3.Search and display using Customer ID"<<endl;
			cout<<" 4.Search and display using Phone No"<<endl;
			cout<<"Enter choice: ";
			cin>>ch;
            cout<<endl;
			switch(ch)
			{
                // displaying all records
				case 1:
                // open bill.dat file with input operation authority
				f1.open("bill.dat",ios::in);
				f1.seekg(0,ios::beg);
				f1.read((char*)&b1, sizeof(b1));
				if(!f1)
				{
					cout<<"=====No records present====="<<endl;
				}
				else
                {
                    // until end of file is reached
                    while(!f1.eof())
                    {
                        // calling output member function of object b1 to display details
                        b1.output();
                        cout<<endl;

                        f1.read((char*)&b1, sizeof(b1));
                    }
				}
				f1.close();
				break;

                // displaying unactive connections
				case 2:
				f1.open("bill.dat",ios::in);
				f1.seekg(0,ios::beg);
				f1.read((char*)&b1, sizeof(b1));
				if(!f1)
				{
					cout<<"=====No records present====="<<endl;
				}
				else
                {
                    while(!f1.eof())
                    {
                        // using toupper stl function to convert the status to Upper case
                        // if unactive
                        if(toupper(b1.getstatus())=='U')
                        {
                            // output the details
                            b1.output();
                        }

                        f1.read((char*)&b1, sizeof(b1));
                    }
				}
				f1.close();
				break;

                // search and display using customer id
				case 3:
				cout<<"Enter the Customer ID: ";
				cin>>m;
                cout<<endl;

				f1.open("bill.dat",ios::in);
				f1.seekg(0,ios::beg);
				f1.read((char*)&b1, sizeof(b1));

				if(!f1)
				{
					cout<<"=====No records present====="<<endl;
				}
				else
				{
                    while(!f1.eof())
                    {
                        if(b1.returncustid()==m)
                        {
                            b1.output();
                        }

                        f1.read((char*)&b1, sizeof(b1));
                    }
				}
				f1.close();
				break;

                // search and displaying using phone number
				case 4:
				cout<<"Enter the Phone No(7 digits)"<<endl;
				cin>>ph;
                // the goto keyword
				dis:
				f1.open("bill.dat",ios::in);
				f1.seekg(0,ios::beg);
				f1.read((char*)&b1, sizeof(b1));
				if(!f1)
				{
					cout<<"=====No records present====="<<endl;
				}
				else
				{
                    while(!f1.eof())
                    {
                        if(b1.comparenumber(ph))
                        {
                            b1.output();
                        }

                        f1.read((char*)&b1, sizeof(b1));
                    }
				}
				f1.close();
				break;
				default:
				cout<<"***Wrong Choice***"<<endl;
			}
		}

}
// Function to update the records based on phone number
void updaterecord()
{
		unsigned long int ph;
		int flag=0;
        cout<<endl;
		cout<<"******The record can be changed exclusively on the basis of Phone no only******"<<endl;
		cout<<endl<<"Enter the Phone No whose record has to be modified(7 digits): ";
		cin>>ph;
        cout<<endl;

        // opening bill records file
		f1.open("bill.dat",ios::in|ios::out);
		f1.seekg(0,ios::beg);
		f1.read((char*)&b1, sizeof(b1));
		if(!f1)
		{
			cout<<"=====No records present====="<<endl;
		}
		else
        {
            // until end of file reached
            while(!f1.eof())
            {
                // if the phone number is non zero
                if(b1.comparenumber(ph))
                {
                    // ask for input details using input member function of b1 object
                    b1.input();
                    // write on f1 file
                    f1.write((char*)&b1,sizeof(b1));
                    // display message
                    cout<<"*****Record Updated*****"<<endl;
                    // raise flag
                    flag=1;
                }
                f1.read((char*)&b1, sizeof(b1));
            }
            // if flag was not raised then display message of no record present
            if(flag==0)
            {
             cout<<"-----Record Not present Please add the record first-----"<<endl;
            }
		}
		f1.close();


}
// Function for the functionality of user in the billing system
void user()
{

	int flag=0;
	unsigned long int number;
	char chbill;
    // Asking phone number : based on which whole access takes place
	cout<<"Enter your phone number(7 digits): ";
	cin>>number;
    cout<<endl;
    // open the bill records
	f1.open("bill.dat",ios::in);
	f1.seekg(0,ios::beg);
	f1.read((char*)&b1,sizeof(b1));

    // until end of file reached
	while(!f1.eof())
	{
        // checking the authenticity of user
		if(b1.comparenumber(number)==1)
		{
            // raise flag
			flag=1;
			break;
		}
        // keep reading until not found
		f1.read((char*)&b1,sizeof(b1));
	}
	f1.close();
    // if logged in :
	if (flag==1)
	{
		cout<<" \n******* Login Successful*******"<<endl;

		cout<<endl;
		cout<<"Your Bill For this Month is as Follows : "<<endl;
        cout<<endl;
        // display the details based on the number
		display(number);

		cout<<"\n \n Do you Wish to pay the bill now ? (y/n): ";
		cin>>chbill;
        cout<<endl;

        // tolower stl function to convert the answer to lower case
		if(tolower(chbill)=='y')
		{
            // calling the paybill function for the given number
            paybill(number);
		}
		else
		{
			cout<<"---****Thank you for using the Billing Services****---"<<endl;

			exit(0);
		}
	}
	else
	{
		cout<<"Invalid phone number entered"<<endl;
	}
}
// Function for functionality of admin in the billing system
void admin(char choice='n')
{
    // if choice entered is y
	if (tolower(choice) =='y')
	{
        // goto the label
        goto adminlo;
	}
	else
	{
        // enter the password
		char pass[20];
		cout<<"Enter Password : ";
		cin>>pass;
        cout<<endl;
		//cin.ignore();
		//cout<<pass;
        // using the string compare function
		if(strcmp(pass,"g10")==0)
		{
			adminlo:

            // Menu displaying
            cout<<"\n--------Welcome Admin!--------"<<endl<<endl;
			cout<<"Choose An Option: "<<endl;
			cout<<"\n 1. Add a Record \n 2. Delete a Record \n 3. Update a Record \n 4. Display a Record \n 5. Auto Change Status of the connections"<<endl;
			int adminch;
			adminre:
            cout<<endl;
            cout<<"Enter Choice : ";
			cin>>adminch;

			switch(adminch)
			{
                // adding records
				case 1 : addrecord();
				break;
                // deleting records
				case 2:
				deleterecord();
				break;
                // updating records
				case 3:
				updaterecord();
				break;
                // displaying records
				case 4:
				display();
				break;
                // update the status
				case 5:
				updatestatus();
				break;
				default :
				cout<<"Invalid Choice Entered \n Please Enter again : "<<endl;
				goto adminre;
			}
		}
		else
		{
			cout<<"Invalid Password Entered  ABORTING...."<<endl;

		exit(0);
		}
	}
}
int main()
{

	int login,ans;
	char ch='n',chapp;
	do
	{
		cout<<"----------------------------------------------------------------------------\n\n";
		cout<<"******* Welcome To IT G1 Group 10's Telephone Billing System ***************"<<endl;
        cout<<"\n----------------------------------------------------------------------------\n";
		cout<<"\n*****Choose an Option***** "<<endl;
		cout<<"\n 1. Login as an Administrator "<<endl;
		cout<<" 2. Login as an User "<<endl;
        cout<<endl;
        cout<<"Choice : ";
		cin>>login;
        cout<<endl;
        // switch case for login authority
		switch(login)
		{
            // if admin
			case 1:
                do{
                    // calling the admin function
                    admin(ch);
                    cout<<" \n \n Do you wish to continue as Administrator (y/n): ";
                    cin>>ch;
                    cout<<endl;
                }
                while(tolower(ch)=='y');
                break;
            // if user
			case 2:
                // calling the user function
                user();
                break;
			default:
                cout<<"Invalid Option entered, Please Enter (1 or 2) "<<endl;
		}
		ch='n';
		cout<<"Do you wish to continue with the application (y/n)"<<endl;
        cout<<"Enter (y/n): ";
		cin>>chapp;
        cout<<endl;
		}
        while(tolower(chapp)=='y');

		return 0;
}
