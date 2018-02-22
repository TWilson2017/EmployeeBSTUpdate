#ifndef NODERECORDS_H
#define NODERECORDS_H

		//Declare struct for Binary Tree
		struct NodeRecords
		{			
			//NodeRecords Constructor
			NodeRecords();
			//Initialize Root Node & Read Records From File & Send Data to Insert Function
			void ReadRecord(NodeRecords *& Root);
			//Create a new BST node
            NodeRecords* newNode(int acct_number5, string last_name5, char middle_initial5, 
			              string first_name5, unsigned int month5, unsigned int day5, unsigned int year5, 
			              float annual_salary5, char dept_code5, string phone_number5);
		    //Insert Recieved Data into Binary Tree by Account #
			NodeRecords* Insert(NodeRecords *&, int acct_number2, string last_name2, char middle_initial2, 
			             string first_name2, unsigned int month2, unsigned int day2, unsigned int year2, 
						 float annual_salary2, char dept_code2, string phone_number2);
            //BUILD THE BST
            void ReadFileRecords(NodeRecords *);
			//Search for Record in BST (Checking for Duplicates)
			bool SearchBST(int, NodeRecords*&);
			//Prompt for & Validate Account Number
			void GetAccountNumber(int &);
			//Prompt for & Validate Month
			void GetMonth(unsigned int &);
			//Prompt for & Validate Day
			void GetDay(unsigned int &);
			//Prompt for & Validate Year
			void GetYear(unsigned int &);
			//Prompt for & Validate First Name, Middle Name, Last Name
			void GetName(string &, char &, string &);
			//Check Dates For Being Out Of Bounds
			bool CheckDate(unsigned int Month, unsigned int Day, unsigned int Year);
			//Validate Date Using CheckDate()
			void ValidateDate(unsigned int &, unsigned int &, unsigned int &);
			//Prompt for & Validate Annual Salary
			void GetAnnualSalary(float&);
			//Prompt for & Validate Department Code 
			void GetDepartmentCode(char& );
			//Prompt for Phone Number 
		    void GetPhoneNumber(string&);
			//Validate Phone Number
			void ValidatePhoneNumber(string&);
			//Call PrintSubtitles() & PrintInOrder() to Print BST Subtitles & Contents
			void PrintBST(NodeRecords *);
			//Convert The Month # into Abbreviation
			string DateConversion(int);
			//Print Subtitles for InOrder
			void PrintSubtitles();
			//Print Total Records Processed
			void TotalRecordsProcessed();
			//Print Report in In-Order Form
			void PrintInOrder(NodeRecords * PtrRoot);
			//Store Data in MASTER File - Recursive
			bool SavePrintLevels(NodeRecords * PtrRoot, int Level, ostream& OutF);
			//Function to print level order traversal a tree
			void LevelOrder(NodeRecords *PtrRoot);
			//Modify Nodes
			void Modify(NodeRecords * PtrRoot);
			//Assign Pointer to new Data
			void ModifyData(NodeRecords *&, int acct_number2, string last_name2, char middle_initial2, 
			                string first_name2, unsigned int month2, unsigned int day2, unsigned int year2, 
						    float annual_salary2, char dept_code2, string phone_number2);
			//Pause the System
			void Pause();
			//Press Any Key To Continue
			void PressAnyKey();
			//Return Node - Search Function
			NodeRecords * SearchBSTNODE(int, NodeRecords*);
			//Determines if year is Leap Year
			bool isLeap (unsigned int year);
			//Validates given year
			bool isValidDate(unsigned int, unsigned int, unsigned int);
			void DestroyTree(NodeRecords * Tree);
			int acct_number;  //Account Number
			string last_name; //Last Name
			string first_name; //First Name
			char middle_initial; //Middle Initial
			unsigned int month; //Month in Number Form
			unsigned int day; //Day in Number Form
			unsigned int year; //Year in Number Form
			float annual_salary; // Annual Salary
			char dept_code; //Department Code (Can be entered as UpperCase/Lower)
			string phone_number; //Phone Number in String Form
			NodeRecords *left_child; //Pointer to left child node in tree
			NodeRecords *right_child; //Pointer to right child node in tree
	    };//end struct node	
#endif
