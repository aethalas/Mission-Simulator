// Title  :  Resource Manager
// Purpose:  For both static and random creation of assets
// Author :  Jonathon H. Tyson
// Date   :  07/02/2017

// Using the standard IO library, string library, vector library, ctime library
// and including sqlite3.h.
#include <iostream>
#include <string>
#include "sqlite3.h"
#include <vector>
#include <ctime>

// Using the standard namespace as it is a single programmer project.
using namespace std;
                                            
char InputChar(string prompt) // *In*
{ // Allows user input.    
	cout << prompt ;
	char answer = ' ' ;

	cin >> answer ;
	cin.ignore(999, '\n') ;
	cin.clear() ;

	return answer;
} // InputChar

void DataEntryCompanies(sqlite3* pDatabase) // *In*
{ // Utility to add several Companies into the database.
	cout << "Enter a list of company names. Enter 0 to finish." << endl ;

	string input ;

	cin >> input ;

	while (input != "0")	// Until user enters empty string. Read-ahead loop.
	{
		// String to store the insert command
		string SQLcommand =  "INSERT INTO Company VALUES (\'" ;
		SQLcommand =  SQLcommand+input+"\'" ;					          
		int companySize = rand() % 200 + 100 ;							       
		SQLcommand = SQLcommand+", "+to_string((long long)companySize) ;
		int companyMoney = rand() % 200 + 100 ;
		SQLcommand = SQLcommand+", "+to_string((long long)companyMoney) ;
		SQLcommand = SQLcommand + ");" ;

		sqlite3_stmt* pStatement = nullptr ;			// Pointer to statement.

		cout << SQLcommand<< endl ;

		// Prepare the statement. Returns an error message.
  // The pStatment is returned by reference.
		sqlite3_prepare(pDatabase, SQLcommand.c_str(), -1, &pStatement, NULL) ;

		// Run the statement, get any errors.
		int error = sqlite3_step(pStatement) ;
		if(error == SQLITE_DONE)	
		{
			cout << input << " entered" << endl ;
		}
		else
		{
			cout << "Error. " << input << " not entered." ;
			cout << sqlite3_errmsg(pDatabase) << endl ;	
		}

		// Delete the statement
		sqlite3_finalize(pStatement) ;
		pStatement = nullptr ;

		cin >> input ;			// Next input for read-ahead loop.
	}
} // DataEntryCompanies

void DataEntryAgents(sqlite3* pDatabase) // *In*
{ // Utility to add several Agents into the database.
	cout << "Enter a list of agent names. Enter 0 to finish." << endl ;

	string input ;

	cin >> input ;

	// Get a list of Company names ********************************************
	sqlite3_stmt* pCompanyQuery = nullptr ;			// Used to query company names.
	vector<string> CompanyNames ;
	sqlite3_prepare_v2(pDatabase, "SELECT name FROM Company;", -1, &pCompanyQuery,
                    NULL) ;

	// Read-ahead. Query the company names.
	int companyResult = sqlite3_step(pCompanyQuery); 

	while(companyResult == SQLITE_ROW)			// Until no company rows to query.
	{
		// Get the first column of this row of the query.
  // (Only one column in this case).
		string companyName(reinterpret_cast<const char*>(sqlite3_column_text
  (pCompanyQuery, 0))) ;
		// Add it to the list of names
		CompanyNames.push_back(companyName) ;
		// Step to the next row.
		companyResult = sqlite3_step(pCompanyQuery) ;
	}

	// Delete the query.
	sqlite3_finalize(pCompanyQuery) ;

	while (input != "0")	// Until user enters empty string. Read-ahead loop.
	{
		// String to store the insert command
		string SQLcommand =  "INSERT INTO Agent VALUES (\'" ;
		SQLcommand =  SQLcommand+input+"\'" ;					
		string randomCompany = CompanyNames[rand()%CompanyNames.size()];
  SQLcommand = SQLcommand+", '"+randomCompany+"\'";     
		int agentSkill = rand() % 10 + 1 ;							       
		SQLcommand = SQLcommand+", "+to_string((long long)agentSkill) ;
		int agentSalary = rand() % 200 + 100 ;
		SQLcommand = SQLcommand+", "+to_string((long long)agentSalary) ;
		SQLcommand = SQLcommand + ");" ;

		sqlite3_stmt* pStatement = nullptr ;			// Pointer to statement.

		cout << SQLcommand<< endl ;

		// Prepare the statement. Returns an error message.
  // The pStatment is returned by reference.
		sqlite3_prepare(pDatabase, SQLcommand.c_str(), -1, &pStatement, NULL) ;

		// Run the statement, get any errors.
		int error = sqlite3_step(pStatement) ;
		if(error == SQLITE_DONE)	
		{
			cout << input << " entered" << endl ;
		}
		else
		{
			cout << "Error. " << input << " not entered." ;
			cout << sqlite3_errmsg(pDatabase) << endl ;	
		}

		// Delete the statement
		sqlite3_finalize(pStatement) ;
		pStatement = nullptr ;

		cin >> input ;			// Next input for read-ahead loop.
	}
} // DataEntryAgents

void DataEntryFactories(sqlite3* pDatabase) // *In*
{ // Utility to add several Agents into the database.
	vector<string> ProductTypes ;
 ProductTypes.push_back("Corn") ;
 ProductTypes.push_back("Oats") ;
 ProductTypes.push_back("Rough Rice") ;
 ProductTypes.push_back("Soybeans") ;
 ProductTypes.push_back("Rapeseed") ;
 ProductTypes.push_back("Wheat") ;
 ProductTypes.push_back("Milk") ;
 ProductTypes.push_back("Cocoa") ;
 ProductTypes.push_back("Coffee") ;
 ProductTypes.push_back("Sugar") ;
 ProductTypes.push_back("Ethanol") ;
 ProductTypes.push_back("Propane") ;
 ProductTypes.push_back("Copper") ;
 ProductTypes.push_back("Platinum") ;
 ProductTypes.push_back("Silver") ;
 ProductTypes.push_back("Amber") ;

 cout << "How many Factories do you want to generate?" << endl ;

	int numFactories ;

	cin >> numFactories ;

	// Get a list of Company names ********************************************
	sqlite3_stmt* pCompanyQuery = nullptr ;			// Used to query company names.
	vector<string> CompanyNames ;
	sqlite3_prepare_v2(pDatabase, "SELECT name FROM Company;", -1, &pCompanyQuery, 
                    NULL) ;

	// Read-ahead. Query the company names.
	int companyResult = sqlite3_step(pCompanyQuery); 

	while(companyResult == SQLITE_ROW)			// Until no company rows to query.
	{
		// Get the first column of this row of the query.
  // (Only one column in this case).
		string companyName(reinterpret_cast<const char*>(sqlite3_column_text
  (pCompanyQuery, 0))) ;
		// Add it to the list of names
		CompanyNames.push_back(companyName) ;
		// Step to the next row.
		companyResult = sqlite3_step(pCompanyQuery) ;
	}

	// Delete the query.
	sqlite3_finalize(pCompanyQuery) ;

	for(int i = 0; i < numFactories; ++i)
	{
		// String to store the insert command
  sqlite3_stmt* pNewFactoryCommand = nullptr;
		string SQLcommand =  "INSERT INTO Factory VALUES (" ;			
		SQLcommand = SQLcommand+""+to_string((long long)i) ;
		string randomCompany = CompanyNames[rand()%CompanyNames.size()];
  SQLcommand = SQLcommand+", '"+randomCompany+"\'"; 
		string randomProduct = ProductTypes[rand()%ProductTypes.size()];    		
  SQLcommand = SQLcommand+", '"+randomProduct+"\', NULL" ;				       
		SQLcommand = SQLcommand + ");" ;

		// Print the command for debugging
		cout << SQLcommand<< endl;
		// Prepare the query
		sqlite3_prepare_v2(pDatabase, SQLcommand.c_str(), -1, &pNewFactoryCommand, 
                     NULL);
		// Run the query
		int result = sqlite3_step(pNewFactoryCommand);

		if(result!=SQLITE_DONE)					// If it didn't work
		{
			cout << "Error entering new Factory!"<<endl;
			cout << sqlite3_errmsg(pDatabase)<< endl;		// Prints an iambic sonnet 
                                              // to desribe the error.
		}

		// Delete the query
		sqlite3_finalize(pNewFactoryCommand);
	}
	
} // DataEntryFactories



void DataEntryMissions(sqlite3* pDatabase)
{ // Utility to add several Agents into the database.
 cout << "How many Missions do you want to generate?" << endl ;

	int numMissions ;

	cin >> numMissions ;

	// Get a list of Factory numbers ********************************************
	sqlite3_stmt* pFactoryQuery = nullptr ;			// Used to query factory numbers.
	vector<string> FactoryNumbers ;
	sqlite3_prepare_v2(pDatabase, "SELECT number FROM Factory;", -1, 
                    &pFactoryQuery, NULL) ;

	// Read-ahead. Query the company names.
	int factoryResult = sqlite3_step(pFactoryQuery); 

	while(factoryResult == SQLITE_ROW)			// Until no company rows to query.
	{
		// Get the first column of this row of the query.
  // (Only one column in this case).
		string factoryNumber(reinterpret_cast<const char*>(sqlite3_column_text
  (pFactoryQuery, 0))) ;
		// Add it to the list of names
		FactoryNumbers.push_back(factoryNumber) ;
		// Step to the next row.
		factoryResult = sqlite3_step(pFactoryQuery) ;
	}

	// Delete the query.
	sqlite3_finalize(pFactoryQuery) ;

	// Get a list of Company names ********************************************
	sqlite3_stmt* pCompanyQuery = nullptr ;			// Used to query company names.
	vector<string> CompanyNames ;
	sqlite3_prepare_v2(pDatabase, "SELECT name FROM Company;", -1, &pCompanyQuery, 
                    NULL) ;

	// Read-ahead. Query the company names.
	int companyResult = sqlite3_step(pCompanyQuery); 

	while(companyResult == SQLITE_ROW)			// Until no company rows to query.
	{
		// Get the first column of this row of the query.
  // (Only one column in this case).
		string companyName(reinterpret_cast<const char*>(sqlite3_column_text
  (pCompanyQuery, 0))) ;
		// Add it to the list of names
		CompanyNames.push_back(companyName) ;
		// Step to the next row.
		companyResult = sqlite3_step(pCompanyQuery) ;
	}

	// Delete the query.
	sqlite3_finalize(pCompanyQuery) ;

	for(int i = 0; i < numMissions; ++i)
	{
		// String to store the insert command
  sqlite3_stmt* pNewMissionCommand = nullptr;
		string SQLcommand =  "INSERT INTO Mission VALUES (" ;			
		SQLcommand = SQLcommand+""+to_string((long long)i) ;
		string randomFactory = FactoryNumbers[rand()%FactoryNumbers.size()] ;
  SQLcommand = SQLcommand+", "+randomFactory+"" ;
		string randomCompany = CompanyNames[rand()%CompanyNames.size()];
  SQLcommand = SQLcommand+", '"+randomCompany+"\'"; 
		int missionDeadline = rand() % 20 + 1 ;							       
		SQLcommand = SQLcommand+", "+to_string((long long)missionDeadline) ;
		int missionDifficulty = rand() % 10 + 1 ;							       
		SQLcommand = SQLcommand+", "+to_string((long long)missionDifficulty) ;	       
		int missionFee = rand() % 200 + 1 ;							       
		SQLcommand = SQLcommand+", "+to_string((long long)missionFee) ;			
		SQLcommand = SQLcommand + ", NULL);" ;

		// Print the command for debugging
		cout << SQLcommand << endl ;

		// Prepare the query
		sqlite3_prepare_v2(pDatabase, SQLcommand.c_str(), -1, &pNewMissionCommand, 
                     NULL) ;
		// Run the query
		int result = sqlite3_step(pNewMissionCommand) ;

		if(result != SQLITE_DONE)					// If it didn't work
		{
			cout << "Error entering new Mission!" << endl ;
			cout << sqlite3_errmsg(pDatabase) << endl ;		// Prints an iambic sonnet 
                                                // to desribe the error.
		}

		// Delete the query
		sqlite3_finalize(pNewMissionCommand) ;
	}
	
} // DataEntryMissions

void PrintAvailableAgents(sqlite3* pDatabase)
{
 unsigned int short agentNumber = 1 ;

	string SQLcommand = "SELECT * FROM Agent ORDER BY Agent.name ASC;" ;

	sqlite3_stmt* pStatement = nullptr ;

	// cout << SQLcommand << endl ;

	sqlite3_prepare(pDatabase, SQLcommand.c_str(), -1, &pStatement, NULL) ;

	int error = sqlite3_step(pStatement) ;

 cout << "##############################" << endl ;
 cout << "## LIST OF AVAILABLE AGENTS ##" << endl ;
 cout << "##############################" << endl ;

	while (error == SQLITE_ROW)
	{
	 cout << " -> Agent [" << agentNumber++ << "]: " ;
  cout << sqlite3_column_text(pStatement, 0) ;
  cout << " - " << sqlite3_column_text(pStatement, 1) ;
  cout << " - Skill: " << sqlite3_column_text(pStatement, 2) ;
  cout << " - Salary: " << sqlite3_column_text(pStatement, 3) << endl ;
	 error = sqlite3_step(pStatement) ;
	}

 cout << endl ;

	sqlite3_finalize(pStatement) ;
	pStatement = nullptr ;

} // PrintAvailableAgents

void SearchAgentMissions(sqlite3* pDatabase)
{
 string name ;
 
 while (name != "0")
 {
 cout << " -> Enter an Agent Name: " ;
 cin >> name ;

	string SQLcommand = "SELECT Mission.id, Agent.name, Factory.company, Mission.target, Mission.fee, ";
 SQLcommand = SQLcommand+"Mission.deadline, Mission.difficulty FROM Mission ";
 SQLcommand = SQLcommand+"LEFT JOIN Agent ON Mission.company = Agent.company ";
 SQLcommand = SQLcommand+"LEFT JOIN Factory ON Mission.target = Factory.number ";
 SQLcommand = SQLcommand+"LEFT JOIN MissionAgent ON Mission.agent = MissionAgent.agent ";
 SQLcommand = SQLcommand+"WHERE Agent.skill >= ";
 SQLcommand = SQLcommand+"Mission.difficulty AND Factory.company != ";
 SQLcommand = SQLcommand+"Agent.company AND Agent.company = Mission.company ";
 SQLcommand = SQLcommand+"AND Agent.name = '";
	SQLcommand = SQLcommand+name ;
 SQLcommand = SQLcommand+"' AND Mission.agent IS NULL ORDER BY Mission.deadline ASC;" ;

	sqlite3_stmt* pStatement = nullptr ;

	// cout << SQLcommand << endl ;

	sqlite3_prepare(pDatabase, SQLcommand.c_str(), -1, &pStatement, NULL) ;

	int error = sqlite3_step(pStatement) ;

 if (sqlite3_column_int(pStatement, 5) != NULL)
 {
  string agentName(reinterpret_cast<const char*> (sqlite3_column_text(pStatement, 1))) ;
  cout << "\n#############################################" << endl ;
  cout << "## -> MISSIONS AVAILABLE FOR AGENT : " << agentName << endl ;
  cout << "#############################################" << endl ;

	 while (error == SQLITE_ROW)
	 {
	  cout << " -> Mission [" << sqlite3_column_int(pStatement, 0) << "]: " ;
   cout << sqlite3_column_text(pStatement, 2) ;
   cout << " - Factory: " << sqlite3_column_int(pStatement, 3) ;
   cout << " - Fee: " << sqlite3_column_int(pStatement, 4) ;
   cout << " - " << sqlite3_column_int(pStatement, 5) << " days left" ;
   cout << " - Difficulty: " << sqlite3_column_int(pStatement, 6) << endl ; 
	  error = sqlite3_step(pStatement) ;
 	}
  cout << endl ;
 }
 else
 {
  cout << "No agent exists with this name!" << endl ;
 }

	sqlite3_finalize(pStatement) ;
	pStatement = nullptr ;
}

} // SearchAgentMissions


void PrintAcceptedMissions(sqlite3* pDatabase)
{
 unsigned int short agentNumber = 1 ;

	string SQLcommand = "SELECT MissionAgent.mission, Agent.name, Factory.company, Mission.target, Mission.fee, Mission.deadline, Mission.difficulty FROM MissionAgent LEFT JOIN Agent ON MissionAgent.agent = Agent.name LEFT JOIN Mission ON MissionAgent.mission = Mission.id LEFT JOIN Factory ON MissionAgent.mission = Factory.number;" ;

	sqlite3_stmt* pStatement = nullptr ;

	// cout << SQLcommand << endl ;

	sqlite3_prepare(pDatabase, SQLcommand.c_str(), -1, &pStatement, NULL) ;

	int error = sqlite3_step(pStatement) ;

 cout << "###############################" << endl ;
 cout << "## LIST OF ACCEPTED MISSIONS ##" << endl ;
 cout << "###############################" << endl ;

	while (error == SQLITE_ROW)
	{
	  cout << " -> Mission [" << sqlite3_column_int(pStatement, 0) << "]" ;
   cout << " - Agent: " << sqlite3_column_text(pStatement, 1) ;
   cout << " - Company: " << sqlite3_column_text(pStatement, 2) ;
   cout << " - Factory: " << sqlite3_column_int(pStatement, 3) ;
   cout << " - Fee: " << sqlite3_column_int(pStatement, 4) ;
   cout << " - " << sqlite3_column_int(pStatement, 5) << " days left" ;
   cout << " - Difficulty: " << sqlite3_column_int(pStatement, 6) << endl ;
	  error = sqlite3_step(pStatement) ;
	}

 cout << endl ;

	sqlite3_finalize(pStatement) ;
	pStatement = nullptr ;

} // PrintAcceptedMissions


int main()
{
	srand(unsigned int(time(NULL))) ;
	bool gameover = false ;				// Flag to end the game
	sqlite3* pDatabase = nullptr;		// Pointer to the master database

	// ***** Connecting to database and checking for problems ********************

	// Connect to the database, get the error status returned from the subprogram.
	int error = sqlite3_open("mydb.db", &pDatabase) ;

	// Check that the database opened
	if(error != SQLITE_OK)
	{
		cout << "Database failed to open" << endl ;
		cout << "Problem reported as : " << sqlite3_errmsg(pDatabase) << endl ;
		gameover = true ;
	}
	else	// Check the database is not empty (if filename is wrong, sqlite will 
	{    // just create an empty db!)
		sqlite3_stmt* pStatement = nullptr ;		// Pointer to a prepared sql statement.

		// Prepare the statemenent. Returns an error message.
  // The pStatment is returned by reference.
		sqlite3_prepare_v2(pDatabase, "SELECT * from Company;", -1, &pStatement, NULL) ;

		// Run the statement, get any errors
		int error = sqlite3_step(pStatement) ;

		// Delete the statement
		sqlite3_finalize(pStatement) ;
		pStatement = nullptr ;

		// If this basic query did not work, the database must be a dud.
		if(error!=SQLITE_ROW)
		{
			cout << "***** Caution! Database is empty or not the correct " ;
   cout << "database. *****" << endl ;
		}
		else
		{
			// Activate foreign key integrity
			sqlite3_stmt* pStatement = nullptr ;		// pointer to a prepared sql statement

			// Prepare the statemenent. Returns an error message.
   // The pStatment is returned by reference.
			sqlite3_prepare(pDatabase, "PRAGMA foreign_keys = ON;", -1, &pStatement, 
                   NULL) ;

			// Run the statement, get any errors
			int error = sqlite3_step(pStatement) ;

			if(error == SQLITE_DONE)
			{
				cout << "-> Foreign key integrity constraints active." << endl ; 
			}
			else
			{
				cout << "-> Caution! Foreign key contraints not active!" << endl ;
			}

			// Delete the statement
			sqlite3_finalize(pStatement) ;
			pStatement = nullptr ;
		}
	}

 // **** Print a list of the available agents ****************************
 PrintAvailableAgents(pDatabase) ;

 // **** Print accepted missions *****************************************
 PrintAcceptedMissions(pDatabase) ;

	// **** Enter the game loop *********************************************
 cout << "##############################" << endl ;
 cout << "## MISSION FINDER -> AGENTS ##" << endl ;
 cout << "## Enter 0 to end program   ##" << endl ;
 cout << "##############################" << endl ;

 SearchAgentMissions(pDatabase) ;

 /*
 // For generating assets

	while(!gameover)
	{
		cout << "[1] Generate Companies" << endl ;
  cout << "[2] Generate Agents" << endl ;
  cout << "[3] Generate Factories" << endl ;
  cout << "[4] Generate Missions" << endl ;
		cout << "[X] QUIT" << endl ;

		char option = InputChar("Select an option: ") ;
		option = toupper(option) ;

		switch (option)
		{
		case '1':			
			DataEntryCompanies(pDatabase) ;
			break ;
  case '2':
   DataEntryAgents(pDatabase) ;
   break ;
  case '3':
   DataEntryFactories(pDatabase) ;
   break ;
  case '4':
   DataEntryMissions(pDatabase) ;
		case 'X':
			gameover = true ;
			break ;
		default:
			cout << "Command not recognised." << endl ;
		}
 }
 */

	} // main