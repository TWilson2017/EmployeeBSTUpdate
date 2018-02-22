//------------------------------------------------------------------
// File name:   EmployeeBSTUpdate.cpp
// Assign ID:   Project 3B
// Due Date:    2/13/18 at 12:30 pm
//
// Purpose:     Implement a menu to allow the user to select the desired function.
//              The program will create a BST using the data stored on the MASTER input file
//              when it is launched.
//       
// Author:      Tishauna Wilson
//------------------------------------------------------------------
#include "EmployeeDataUpdate.cpp"
#include <cctype>
using namespace std;

//-|----------------------------------------------------------------
//-|Display The Main Menu Commands
//-|----------------------------------------------------------------
void ShowCommands()
{
	//Show The Commands
	cout << "BST UPDATE SYSTEM" << endl << endl;
	cout << "A) To Add an New Record" << endl;
	cout << "M) To MODIFY a Record" << endl;
	cout << "P) To Print a Report In-Order" << endl;
	cout << "S) Save Changes {write current BST to MASTER FILE}" << endl;
	cout << "Q) Quit [Exit System]" << endl;
	cout << endl;
}//ShowCommands

//-|----------------------------------------------------------------
//-|Perform The User Commands To Manipulate The Program
//-|----------------------------------------------------------------
void PerformCommand(char Command, NodeRecords *& Root, NodeRecords Data)
{
    //Switch to Perform the Desired Command
	switch(Command)
	{
		case 'A': //Add a New Record into the Binary Search Tree
			      Data.ReadRecord(Root);
			      break;
		case 'M': //Modify a Record
		          Data.Modify(Root);
			      break;
		case 'P': //Print Report InOrder
			      Data.PrintBST(Root);
			      break;
		case 'S': //Save Changes
				  Data.LevelOrder(Root);
			      Data.DestroyTree(Root);
			      break;
		case 'Q'://Quit the Program
			     cout << endl << "TERMINATING PROGRAM." << endl;
			     cout << "(c) 2018, Tishauna Wilson" << endl << endl;
			     Data.Pause();
			     Data.DestroyTree(Root);
			     exit(1);
			     break;
		default:break;	
	}//switch
}//PerformCommand

int main()
{
   //-|------------------------------------------------------------------------
   //-| Declare Variables
   //-|------------------------------------------------------------------------
   char Command = ' '; //Variable to hold Command
   bool isCommand = true; //Variable to allow do-while loop to continue looping
   static NodeRecords Data;  //Declare a Object
   static NodeRecords *Root = NULL; //Declare a pointer object
   Data.ReadRecord(Root);   //Call ReadRecord to Place File items into BST

   //-| ----------------------------------------------------------------------
   //-| Print the copyright notice declaring authorship.
   //-| ----------------------------------------------------------------------
   cout << endl << "(c) 2018, Tishauna Wilson" << endl << endl; 

   //-| ----------------------------------------------------------------------
   //-| 1. Show The Commands of the Menu and Choose Perform A Command
   //-| ----------------------------------------------------------------------
   ShowCommands();
	
   //Prompt for Command
   cout << "Enter Option: ";
   cin >> Command;
   Command = toupper(Command); //Make Command Uppercase To Lessen While Statement
	 
   //Loop through do-while loop until program terminates
   do
   {
	   //Check for Commands that are out of Boundaries
	   while((Command != 'A') && (Command != 'M') && (Command != 'P') && (Command != 'S') && (Command != 'Q'))
	   {
			  cout << "Error <Re-Enter Valid Option>: ";
		      cin >> Command;
		      Command = toupper(Command);
	   }//while
	 
	   //Once a valid Command is entered, call the PerformCommand() function
	   PerformCommand(Command, Root, Data);
	   
	   //Show Commands Again
	   ShowCommands();
	   
	   // Prompt for & enter in another Command
	   cout << "Enter Option: ";
       cin >> Command;
	   Command = toupper(Command);
	   
   }while(isCommand == true);//do-while
	
   //-| ----------------------------------------------------------------------
   //-| Print the copyright notice declaring authorship again.
   //-| ----------------------------------------------------------------------
   cout << endl << "(c) 2018, Tishauna Wilson" << endl << endl; 
   return 0;
}//main
