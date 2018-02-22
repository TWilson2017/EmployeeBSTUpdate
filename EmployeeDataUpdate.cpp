#include <iostream>
using namespace std;
#include <fstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <string>
#include <ctime>
#include <limits>
#include <unistd.h>
#include <sstream>
#include "EmployeeDataUpdate.h"
static int TotalRecords = 0; //Global Variable that counts the Total Records

//-|---------------------------------
//-| 1. NodeRecords Constructor
//-|---------------------------------
 NodeRecords :: NodeRecords()
 {
 }//NodeRecords Constructor

//-|----------------------------------------------------------------------------------
//-| 2. Read Records From File & Send To Insert Insert into Binary Tree by Account #
//-|----------------------------------------------------------------------------------
void NodeRecords :: ReadRecord(NodeRecords *& Root)
{
	//Declare Variables
    int acct_number3 = 0; 
	string last_name3 = "", first_name3 = "", phone_number3 = "";
	char middle_initial3 = ' ', dept_code3 = ' '; 
	unsigned int month3 = 0, day3 = 0, year3 = 0;
	float annual_salary3 = 0.00;
        static int Counter = 0; //Variable to keep track of entering data from file into BST
	ifstream inF; //Variable to Enter Data from File into BST

	//Open File
	inF.open("MASTER");
	
       //Test File For Error
	if(inF.fail())
	{
           cout << endl << "FATAL ERROR: UNABLE TO OPEN FILE \"MASTER\" TERMINATING..."
                << endl << endl;
           exit (1);
	}//if
	else
	{
		//-|-----------------------------------
		//-| 2b. Enter data from File into BST
		//-|-----------------------------------
	
		//Enter If Statement, if Counter < 1
		if(Counter < 1)
		{
				//Read in Data from File
				while(inF >> acct_number3 >> last_name3 >> middle_initial3 >> first_name3 >> month3 
					  >> day3 >> year3 >> annual_salary3 >> dept_code3 >> phone_number3)
				{
					//Check to see if the Account Number or the Annual Salary is Negative
					if(acct_number3 < 0 || annual_salary3 < 0.00)
						continue;
					
					//Else, send the data to Insert() function
					else
					{
						//Add 1 to TotalRecords
						TotalRecords++;
						
						//Capitalize dept_code3
						dept_code3 = toupper(dept_code3);
					
						//Send Data to Insert() Funtion
						Root = Insert(Root, acct_number3, last_name3, middle_initial3, first_name3, month3, day3, year3, 
							     annual_salary3, dept_code3, phone_number3);
					}//else
				}//while		
			//Ignore Until End 
			inF.ignore(numeric_limits<streamsize>::max(),'\n');
			//Clear the MASTER File
			inF.clear();
			//Close File
			inF.close();
			//Add Counter By One
			Counter++; 
		}//if
	
		//-|------------------------------------
		//-| 2c. Enter Data From User into BST
		//-|------------------------------------
		
		//Enter the else Statement once Counter >= 1
		else
		{
			//Call GetAccountNumber() to Prompt & Validate Account Number 
			GetAccountNumber(acct_number3);
		
			//Search Tree For a Duplicate Account Number
			if (SearchBST(acct_number3, Root) == true)
			{
				cout << endl << "DUPLICATES ARE NOT ALLOWED" << endl;
				
				//Call PressAnyKey()
				PressAnyKey();
			}//if
		
			//If SearchBST() == false, Insert New Record into BST
			else
			{
				//Call GetName() to Prompt for Last Name, Middle Initial, & First Name
				GetName(last_name3, middle_initial3, first_name3);
			
				//Call GetMonth() to Prompt for Month & Validate Month
				GetMonth(month3);
			
				//Call GetDay() to Prompt for Day & Validate Day
				GetDay(day3);
			
				//Call GetYear() to Prompt for Year & Validate Year 
				GetYear(year3);
				
				//Validate the User Input Date as One
				ValidateDate(month3, day3, year3);
				
				//Call GetAnnualSalary() to Prompt for Annual Salary & Validate Annual Salary
				GetAnnualSalary(annual_salary3);
			
				//Call GetDepartmentCode() to Prompt for Department Code & Validate Department Code
				GetDepartmentCode(dept_code3);
			
				//Call GetPhoneNumber() to Prompt for Phone Number & Validate Phone Number
				GetPhoneNumber(phone_number3);
			
				//Once Data Passes each test, Send Data to Insert() Funtion
				Root = Insert(Root, acct_number3, last_name3, middle_initial3, first_name3, month3, day3, year3, 
					      annual_salary3, dept_code3, phone_number3);
			
				//Count the Total Records Inputted into BST
				TotalRecords++;
	
				//Call PressAnyKey()
				PressAnyKey();
			}//else
		}//else
	}//else
}//ReadRecord


//-|--------------------------------
//-| 3. Create a new BST NodeRecords
//-|--------------------------------
NodeRecords* NodeRecords :: newNode(int acct_number5, string last_name5, char middle_initial5, 
			            string first_name5, unsigned int month5, unsigned int day5, unsigned int year5, 
			             float annual_salary5, char dept_code5, string phone_number5)
{
	//Create a temp node & Assign Inserted to temp
	NodeRecords *temp = new NodeRecords();
	temp->acct_number = acct_number5;
	temp->last_name = last_name5;
	temp->middle_initial = middle_initial5;
	temp->first_name = first_name5;
        temp->month = month5;
	temp->day = day5;
	temp->year = year5;
	temp->annual_salary = annual_salary5;
	temp->dept_code = dept_code5;
	temp->phone_number = phone_number5;
	temp->left_child = temp->right_child = NULL;
	return temp;
}//newNode


//-|-----------------------------------------------------------------
//-| 4. Insert Recieved Data into Binary Tree by Account #
//-|-----------------------------------------------------------------
NodeRecords* NodeRecords :: Insert(NodeRecords *& PtrRoot,int acct_number2, string last_name2, char middle_initial2,
				   string first_name2, unsigned int month2, unsigned int day2, unsigned int year2, 
			           float annual_salary2, char dept_code2, string phone_number2)
{	
	//if PtrRoot == NULL, return new node
	if(PtrRoot == NULL)
	{
		return newNode(acct_number2, last_name2, middle_initial2, first_name2, month2, day2, year2, annual_salary2, dept_code2, phone_number2);
	}//if
	
	//Otherwise, recursive down the tree
	//If, given acct_number2 is less than the root node, then, call for left subtree. Else, call for right subtree
	if(acct_number2 < PtrRoot->acct_number)
		PtrRoot->left_child = Insert(PtrRoot->left_child, acct_number2, last_name2, middle_initial2, first_name2, month2, 
									 day2, year2, annual_salary2, dept_code2, phone_number2);
	
	else if(acct_number2 > PtrRoot->acct_number)    //acct_number2 > PtrRoot->acct_number
		PtrRoot->right_child = Insert(PtrRoot->right_child, acct_number2, last_name2, middle_initial2, first_name2, 
									  month2, day2, year2, annual_salary2, dept_code2, phone_number2);
	//return unchanged PtrRoot pointer
	return PtrRoot;
}//Insert

//-|--------------------------------------------
//-| 5. Prompt for & Validate Account Number
//-|--------------------------------------------
void NodeRecords :: GetAccountNumber(int & AccountNumber)
{
	//Declare Variable
	string PhoneNumber2;  //Variable to input AccountNumber into
	bool isPhoneNumber = false;  //Flag to determine if string is a number
	int i = 0;    //Loop Contol Variable
	AccountNumber = 0; //Assign AccountNumber to Zero to put string number into AccountNumber
	
	//Prompt for Account Number
	cout << "Enter Account Number: ";
	cin >> PhoneNumber2;
	
    //Validate Account Number
    while(isPhoneNumber == false && i < PhoneNumber2.size())
    {
		//If any PhoneNumber2 characters do not contain a number, prompt user for a valid input
		if((PhoneNumber2[i] >= '0' && PhoneNumber2[i] <= '9') == false)
		{
			cin.clear(); // clears error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore until maxed/newline is reached
			
			//Re-Prompt for Account Number
 			cout << "Enter Account Number: ";
	                cin >> PhoneNumber2;
		}//if
		else
		{
			//If char is a number, increment i by one
			i++;
		}//else
    }//while
	
    //Create a object from the class stringstream to convert string into integer
    stringstream Convert(PhoneNumber2);
 
    //Stream value into AccountNumber
    Convert >> AccountNumber;
}//GetAccountNumber


//-|-----------------------------------------------------------------------------
//-| 6. Search for Record in BST (Checking for Duplicates) (Iterative Approach)
//-|-----------------------------------------------------------------------------
bool NodeRecords :: SearchBST(int Account_Number, NodeRecords *&Root)
{
	//Declare Variable
	NodeRecords* Temp = Root; //Temp Variable assigned the Root
	
   //Search for Account_Number in BST while BST isn't NULL
	while (Temp != NULL) 
	{
		//Base Case: Check For if Account Number is Present at Root, IF SO, Return true
		if(Account_Number == Temp->acct_number)
			return true;
        
		//Check either the Right Tree OR Left Tree
        else 
		{
			//Else if, Account Number is greater than Root's Account Number, then, search right side of Tree
			if(Account_Number > Temp->acct_number)
				Temp = Temp->right_child;
			
            //Else, Account Number is less than Root's Account Number. SO, Search left side of Tree
			else
			   Temp = Temp->left_child;
        }//Outer-else
    }//while
	
    //If Account Number is not found, return false
    return false;
}//SearchBST

//-|----------------------------------
//-| 7. Prompt for & Validate Month
//-|----------------------------------
void NodeRecords :: GetMonth(unsigned int &Month)
{
	//Prompt for Month ----> 02
	cout << "Enter Month (EX: 02 OR 2): ";
	cin >> Month;
		
	//Validate Month
	while (Month < 1 || Month > 12)
	{
		//Re-Prompt for Month
		cout << "Enter Month (EX: 02 OR 2): ";
		cin >> Month; 
	}//while
}//GetMonth52

//-|----------------------------------
//-| 8. Prompt for & Validate Day
//-|----------------------------------
void NodeRecords :: GetDay(unsigned int &Day)
{
	//Prompt for Day ----> 03
	cout << "Enter Day (EX: 03 OR 3): ";
	cin >> Day;
		
	//Validate Day
	while(Day < 1 || Day > 31)
	{
		//Re-Prompt for Day
		cout << "Enter Day (EX: 03 OR 3): ";
		cin >> Day;
	}//while
}//GetDay

//-|----------------------------------
//-| 9. Prompt for & Validate Year
//-|----------------------------------
void NodeRecords :: GetYear(unsigned int &Year)
{
	//Prompt for Year ---> 2018
	cout << "Enter Year (EX: 2018): ";
	cin >> Year;
	
	//Validate Year
	while(Year == 0)
	{
		//Re-Prompt for Year
		cout << "Enter Year (EX: 2018): ";
		cin >> Year;
	}//while
}//GetYear

//-|-----------------------------------------------
//-| 10. Prompt for & Validate Last Name, Middle Name, First Name
//-|-----------------------------------------------
void NodeRecords :: GetName(string &LastName, char &MiddleInitial, string &FirstName)
{
	    //Prompt for Last Name
		cout << "Enter Last Name: ";
		cin >> LastName;
			
		//Prompt for Middle Initial
		cout << "Enter Middle Initial: ";
		cin >> MiddleInitial;
		
		//Prompt for First Name
		cout << "Enter First Name: ";
		cin >> FirstName;
}//GetName

//-|---------------------------------------
//-| 11. Determines if year is Leap Year
//-|---------------------------------------
bool NodeRecords :: isLeap (unsigned int year)
{
	//Return true if the year is a multiple of 4 and not a multiple of 100.
	return(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}//isLeap

//-|-----------------------------
//-| 12. Validates given year
//-|-----------------------------
bool NodeRecords :: isValidDate(unsigned int month, unsigned int day, unsigned int year)
{
	//Declare Max & Min Valid Years
	const int MAX_YEAR = 9999;
	const int MIN_YEAR = 1800;
	
	 // If year, month and day are not in given range, return false
    if(year > MAX_YEAR || year < MIN_YEAR)
      return false;
 
    //Handle February month with leap year
    if(month == 2)
    {
        if (isLeap(year))
           return (day <= 29);
        else
           return (day <= 28);
    }//if
 
    //Handle the months of April, June, Sept and Nov.
    if(month == 4 || month == 6 || month == 9 || month == 11)
        return (day <= 30);
 
    //Return true, if date is valid
    return true;
}//isValidDate

//-|------------------------------------------
//-| 13. Check Dates For Being Out Of Bounds
//-|------------------------------------------
bool NodeRecords :: CheckDate(unsigned int Month, unsigned int Day, unsigned int Year)
{
	//Get Today's Date
	time_t t = time(0);
	tm* ltm = localtime(&t);
	
	//Return False If Today's Year Is Less Than or Equal To File's Year
	if((ltm->tm_year + 1900) < Year)
	   return false;
	
	//Return False If Today's Month Is Less Than or Equal To User's Input Month, Today's Day Is Less Than User's Input, 
	//and Today's Year Is Less Than or Equal To User's Input 
	//(e.g - Today: 2/19/2018 ----> User's Input Date: 2/20/2018)
	else if((ltm->tm_mon + 1) <= Month && (ltm->tm_mday) < Day && (ltm->tm_year + 1900) <= Year)
	   return false;
	
	//Return False If Today's Month Is Less Than User's Input Month, Today's Day Is Less Than User's Input Day, 
	//and Today's Year Is Less Than or Equal To User's Input Year 
	//(e.g - Today: 2/21/2018 ----> User's Input Date: 2/27/2018)
	else if((ltm->tm_mon + 1) < Month && (ltm->tm_mday) < Day && (ltm->tm_year + 1900) <= Year)
	   return false;
	
	//Return False If Today's Month Is Less Than User's Input Month, Today's Day Is Less Than or Equal To User's Input Day, 
	//and Today's Year Is Less Than or Equal To User's Input Year 
	//(e.g - Today: 2/19/2018 ----> User's Input Date: 3/19/2018)
	else if((ltm->tm_mon + 1) < Month && (ltm->tm_mday) <= Day && (ltm->tm_year + 1900) <= Year)
	   return false;
	
	//Return True if User's Input Date Doesn't FAIL Test
	else 
	   return true;
}//CheckDate
		
//-|------------------------------------
//-| 14. Validate Date Using CheckDate()
//-|------------------------------------
void NodeRecords :: ValidateDate(unsigned int &Month2, unsigned int &Day2, unsigned int &Year2)
{
	//Validate Date as One (Make Sure Date is not out of Boundaries)
	while(CheckDate(Month2, Day2, Year2) == false || isValidDate(Month2, Day2, Year2) == false)
	{
		//Prompt for Correct Date
		cout << endl << "Invalid Date: " << endl << endl;
		
		//Call Pause() Funtion
		Pause();
		
		//Call GetMonth()
		GetMonth(Month2);
		
		//Call GetDay()
		GetDay(Day2);
		
		//Call GetYear()
		GetYear(Year2);
	}//while
}//ValidateDate

//-|-----------------------------------------
//-| 15. Prompt for & Validate Annual Salary
//-|-----------------------------------------
void NodeRecords :: GetAnnualSalary(float &AnnualSalary)
{
	//Prompt for Annual Salary
	cout << "Enter Annual Salary: ";
	cin >> AnnualSalary;
	
	//Validate Annual Salary
	while(AnnualSalary < 0.00)
	{
		//Re-Prompt for Annual Salary
		cout << "Enter Annual Salary: ";
		cin >> AnnualSalary;
	}//while
}//GetAnnualSalary

//-|---------------------------------------------
//-| 16. Prompt for & Validate Department Code 
//-|---------------------------------------------
void NodeRecords :: GetDepartmentCode(char& DepartmentCode)
{
	//Prompt for Department Code
	cout << "Enter Department Code: ";
	cin >> DepartmentCode;
	
	//Validate Department Code
	while(!isalpha(DepartmentCode))
	{
		//Re-Prompt for Annual Salary
		cout << "Enter Department Code: ";
		cin >> DepartmentCode;
	}//while
	
	//Make DepartmentCode Uppercase To Lessen Readability
	DepartmentCode = toupper(DepartmentCode);
}//GetDepartmentCode

//-|----------------------------------------
//-| 17. Prompt for Phone Number
//-|----------------------------------------
void NodeRecords :: GetPhoneNumber(string& PhoneNumber)
{
	//Prompt for Phone Number
	cout << "Enter Phone Number (EX: 813-555-7469): ";
	cin >> PhoneNumber;

	//Call ValidatePhoneNumber()
	ValidatePhoneNumber(PhoneNumber);
}//ValidatePhoneNumber

//-|------------------------------------------------------
//-| 18. Validate Phone Number
//-|------------------------------------------------------
void NodeRecords :: ValidatePhoneNumber(string &PhoneNumber2)
{
	//Declare Variable
	bool isPhoneNumber2 = true; //Variable to confirm if Phone Number is Valid
	int PhoneNumberCounter2 = 0; //Variable to count Phone Number values
	int DashesCounter = 0; //Variable to count Phone Number dashes
	const int PhoneNumValue2 = 10; //Variable to determine if Phone Number has 10 values
	const int DashesValue = 2; //Variable to determine if Phone Number has 2 dashes
	int i = 0; //Loop Control Variable

	//-|-----------------------------
	//-| 18b. Validate Phone Number
	//-|-----------------------------
	
	//Check size of string
	while(PhoneNumber2.size() == 0)
	{
		//Re-Prompt for Phone Number
		GetPhoneNumber(PhoneNumber2);
	}//1st while
		
	//Check for Phone Number containing ANYTHING ELSE other than #'s & dashes's
	while(isPhoneNumber2 == true && i < (PhoneNumber2.size()))
	{	
		//Check for if Phone Number Contains Number's
		if(PhoneNumber2[i] >= '0' && PhoneNumber2[i] <= '9')
		{
			//Count PhoneNumberCounter by 1
			PhoneNumberCounter2++;
		}//if
		
		//Check for if Phone Number Contains Dashes
		else if(PhoneNumber2[i] == '-')
			//Count DashesCounter by 1
			DashesCounter++;

		//Else, the User Input is not a Phone Number
		else
			isPhoneNumber2 = false;
					
		//Iterate i by 1
		i++;	
	}//while
	
	//If |isPhoneNumber == false| OR |PhoneNumberCounter > 10 OR < 10| OR |DashesCounter > 2 OR < 2|, 
	//Call ValidatePhoneNumber() to Re-Prompt for Phone Number
	if((isPhoneNumber2 == false) || (PhoneNumberCounter2 > PhoneNumValue2) || (PhoneNumberCounter2 < PhoneNumValue2)
	                             || (DashesCounter > DashesValue) || (DashesCounter < DashesValue))
	{	
		GetPhoneNumber(PhoneNumber2);
	}//if
}//GetPhoneNumber

//-|-------------------------------------------------------------------------------
//-| 19. Call PrintSubtitles() & PrintInOrder() to Print BST Subtitles & Contents
//-|-------------------------------------------------------------------------------
void NodeRecords :: PrintBST(NodeRecords *Root)
{
	//Call PrintSubtitles, PrintInOrder(OutF,NodeRecords *PtrRoot), TotalRecordsProcessed & Close the OutF File
	PrintSubtitles();
    PrintInOrder(Root);
	TotalRecordsProcessed();
	PressAnyKey();
}//PrintBST

//-|--------------------------------------------
//-| 20. Convert The Month # into Abbreviation
//-|--------------------------------------------
string NodeRecords :: DateConversion(int Month)
{
	//Declare Array of Month Abbreviations
	const string DateAbbr[12] = {"Jan. ", "Feb. ", "Mar. ", "Apr. ", 
		                     "May ", "Jun. ", "Jul. ", "Aug. ", 
				     "Sep. ", "Oct. ", "Nov. ", "Dec. "};
	
   //Use Switch to return the respective Date Abbreviation
   switch(Month)
   {
	   case 1: return DateAbbr[0];
		           break;
	   case 2: return DateAbbr[1];
		           break;
	   case 3: return DateAbbr[2];
		           break;
	   case 4: return DateAbbr[3];
			   break;
	   case 5: return DateAbbr[4];
		           break;
	   case 6: return DateAbbr[5];
			   break;
	   case 7: return DateAbbr[6];
			   break;
	   case 8: return DateAbbr[7];
			   break;
	   case 9: return DateAbbr[8];
		           break;
	   case 10: return DateAbbr[9];
			   break;
	   case 11: return DateAbbr[10];
		           break;
	   case 12: return DateAbbr[11];
			   break;
	   default: return ("Wrong Month Inserted....");
		           break;
   }//Switch
}//DateConversion

//-|---------------------------------------
//-| 21. Print Subtitles for InOrder
//-|---------------------------------------
void NodeRecords :: PrintSubtitles()
{
	    //Print Title & Subtitles
	    cout << setw(50) << "Employee Report" << endl << endl;
	    cout << left << setw(6) << "Acct#" << right << setw(12) << "Last Name" 
		 << right << setw(13) << "First Name" << right << setw(17) << "Date of birth"
		 << right << setw(19) << "Annual Salary" << right << setw(22) << "Department Code" << endl; 
		
}//PrintSubtitles
	
//-|------------------------------------
//-| 22. Print Total Records Processed
//-|------------------------------------
void NodeRecords :: TotalRecordsProcessed()
{
	cout << endl << endl << endl << left << "Total Records Processed: " << TotalRecords << endl << endl;
}//TotalRecordsProcessed

//-|-------------------------------------
//-| 23. Print Report in In-Order Form
//-|-------------------------------------
void NodeRecords :: PrintInOrder(NodeRecords *PtrRoot)
{
	//Print The Contents in the B-Tree in InOrder
	if(PtrRoot != NULL)
	{
		//Traverse through left-subtree
		PrintInOrder(PtrRoot->left_child);
			
		//Visit the Root
		cout << setfill('0') << setw(3) << PtrRoot->acct_number;
		cout << setfill(' ') << right << setw(12) << PtrRoot->last_name << right << setw(12) 
		     << PtrRoot->first_name << right << setw(12) << DateConversion(PtrRoot->month)
		     << PtrRoot->day << ", " << PtrRoot->year << right << setw(7) << '\t' << '$' 
		     << fixed << setprecision(2)  << PtrRoot->annual_salary << right << setw(14) 
		     << '\t' << PtrRoot->dept_code << endl;
			
		//Traverse through the right-subtree
		PrintInOrder(PtrRoot->right_child);
	}//if
}//PrintInOrder

//-|-------------------------------------------
//-| 24. Store Data in MASTER File - Recursive
//-|-------------------------------------------
bool NodeRecords :: SavePrintLevels(NodeRecords *PtrRoot, int Level, ostream& OutF)
{

		//Check to see if PtrRoot is NULL
		if(PtrRoot == NULL)
		{
			return false;
		}//if
		//Check to see if Level == 1, if so, print out the data
		if(Level == 1)
		{
			OutF << setfill('0') << setw(3) << PtrRoot->acct_number;
			OutF << setfill(' ') << right << setw(12) << PtrRoot->last_name << right << setw(12) 
			     << PtrRoot->middle_initial << setw(12) << PtrRoot->first_name << right 
			     << setw(12) <<PtrRoot->month << setw(11) << PtrRoot->day << setw(11) << PtrRoot->year 
			     << right << setw(7) << '\t' << '$' << fixed << setprecision(2) << PtrRoot->annual_salary << right << setw(4) 
			     << '\t' << PtrRoot->dept_code << right << setw(18) << PtrRoot->phone_number << endl;
			return true;
		}//if
		
		//Else if level is greater than 1, decrease the level by one, for both subtrees
		else if(Level > 1)
		{
			//Set booleans to recrusive function
			bool left = SavePrintLevels(PtrRoot->left_child, Level-1, OutF);
			bool right = SavePrintLevels(PtrRoot->right_child, Level-1, OutF);
			
			//Return either the left and right value at different times
			return left||right;
		}//else-if
}//SavePrintLevels

//-|--------------------------------------------------
//-| 25. Function to print level order traversal a tree
//-|--------------------------------------------------
void NodeRecords :: LevelOrder(NodeRecords *PtrRoot)
{
	ofstream OutF;
	OutF.open("MASTER");
	
	
	//Check for if PtrRoot is NULL, if so, exit out of function
	if(PtrRoot == NULL)
		return;
	//Start from level 1 until height of tree is reached
	int Level = 1;
    //Call SavePrintLevels() Function until SavePrintLevels() returns false
	while(SavePrintLevels(PtrRoot,Level, OutF))
		Level++;
	
	//Once SavePrintLevels() returns false, Print statement, Close file, Pause system & Terminate program
	//Display Statement
	cout << endl << endl << "CHANGES SAVED " << TotalRecords << " records written to MASTER FILE" << endl << endl;
	
	//Clear the File
	OutF.clear();
	//Flush the File
	OutF.flush();
	//Close Out File
	OutF.close();
	//Call Pause() Function
	Pause();
	//Terminate Program
	exit(1);
}//LevelOrder

//-|---------------------------------
//-| 26. Return Node - Search Function
//-|---------------------------------
NodeRecords* NodeRecords :: SearchBSTNODE(int Account_Number, NodeRecords* Root)
{
	//Declare Variable
	NodeRecords* Temp = Root; //Temp Variable assigned the Root
	
   //Search for Account_Number in BST while BST isn't NULL
	while (Temp != NULL) 
	{
		//Base Case: Check For if Account Number is Present at Root, IF SO, Return the node
		if(Account_Number == Temp->acct_number)
			return Temp;
        
		//Check either the Right Tree OR Left Tree
        else 
		{
			//Else if, Account Number is greater than Root's Account Number, then, search right side of Tree
			if(Account_Number > Temp->acct_number)
			   Temp = Temp->right_child;
			
            //Else, Account Number is less than Root's Account Number. SO, Search left side of Tree
			else
			   Temp = Temp->left_child;
        }//Outer-else
    }//while
	
	//If Account Number is not found, return NULL
    return NULL;
}//SearchBSTNODE

//-|-------------------------
//-| 27. Modify Nodes
//-|-------------------------
void NodeRecords :: Modify(NodeRecords * PtrRoot)
{
	//Declare Variables
    int acct_number3 = 0; 
	string last_name3 = "", first_name3 = "", phone_number3 = "";
	char middle_initial3 = ' ', dept_code3 = ' '; 
	unsigned int month3 = 0, day3 = 0, year3 = 0;
	float annual_salary3 = 0.00;
	
	//Call GetAccountNumber() to Prompt & Validate Account Number 
	GetAccountNumber(acct_number3);
	
	//Create new pointer & Assign it to SearchBSTNODE() Function, Search Tree For Account Number
	NodeRecords* temp = new NodeRecords();
	temp = SearchBSTNODE(acct_number3, PtrRoot);
	
	//If Number is found, Proceed to Modify Data
	if (temp != NULL)
	{
		//Call GetName() to Prompt for Last Name, Middle Initial, & First Name
		GetName(last_name3, middle_initial3, first_name3);
		
		//Call GetMonth() to Prompt for Month & Validate Month
		GetMonth(month3);
		
		//Call GetDay() to Prompt for Day & Validate Day
		GetDay(day3);
		
		//Call GetYear() to Prompt for Year & Validate Year 
		GetYear(year3);
			
		//Validate the User Input Date as One
		ValidateDate(month3, day3, year3);
			
		//Call GetAnnualSalary() to Prompt for Annual Salary & Validate Annual Salary
		GetAnnualSalary(annual_salary3);
		
		//Call GetDepartmentCode() to Prompt for Department Code & Validate Department Code
		GetDepartmentCode(dept_code3);
		
		//Call GetPhoneNumber() to Prompt for Phone Number & Validate Phone Number
		GetPhoneNumber(phone_number3);
		
		//Once Data Passes each test, Send Data to Insert() Funtion to Modify
		ModifyData(temp, acct_number3, last_name3, middle_initial3, first_name3, month3, day3, year3, 
				  annual_salary3, dept_code3, phone_number3);

		//Display Statement
		cout << endl << "RECORD " << acct_number3 << " MODIFIED" << endl << endl;
		
		//Call PressAnyKey() Funtion to Continue
		PressAnyKey();
	}//if
	
	//Else, Display that the record wasn't found
	else
	{
		//Display Statement
		cout << endl << "RECORD " << acct_number3 << " is NOT FOUND" << endl;
		
		//Call PressAnyKey() Funtion to Continue
		PressAnyKey();
	}//else
}//Modify

//-|-------------------------------
//-| 28. Assign Pointer to new Data
//-|-------------------------------
void NodeRecords :: ModifyData(NodeRecords *& PtrRoot, int acct_number2, string last_name2, char middle_initial2, 
			       string first_name2, unsigned int month2, unsigned int day2, unsigned int year2, 
		               float annual_salary2, char dept_code2, string phone_number2)
{
	//Create a new pointer & allocate its memory
	NodeRecords *temp = new NodeRecords;
	
	//Create a new BST Record by calling newNode() Function
    temp = newNode(acct_number2, last_name2, middle_initial2, first_name2, month2, day2, year2, annual_salary2, 
		   dept_code2, phone_number2);
	
	//Assign temp's data to PtrRoot's data
	PtrRoot->last_name = temp->last_name;
	PtrRoot->middle_initial = temp->middle_initial;
	PtrRoot->first_name = temp->first_name;
	PtrRoot->month = temp->month;
	PtrRoot->day = temp->day;
	PtrRoot->year = temp->year;
	PtrRoot->annual_salary = temp->annual_salary;
	PtrRoot->dept_code = temp->dept_code;
	PtrRoot->phone_number = temp->phone_number;
	temp = NULL;
}//ModifyData

//-|---------------------------
//-| 29. Pause the System
//-|---------------------------
void NodeRecords :: Pause()
{
	//Pause The System for 2 Seconds
	sleep(2);
}//Pause

//-|---------------------------------
//-| 30. Press Any Key To Continue
//-|---------------------------------
void NodeRecords :: PressAnyKey()
{
	//Wait Until Any Key is Pressed BEFORE returning to Main Menu
	cout << endl << "Press ANY KEY to return to MAIN MENU: ";
	cin.ignore();
	cin.get();
	cout << endl << endl;
}//PressAnyKey

//-|-----------------------------------------------------------
//-| 31. Destructor function helper function.
//-|-----------------------------------------------------------
void NodeRecords :: DestroyTree(NodeRecords * Tree)
{
   // Delete node and it's children
   if (Tree != NULL)
   {
      DestroyTree(Tree->left_child);
      DestroyTree(Tree->right_child);
      delete Tree;
   }//if
}//DestroyTree
