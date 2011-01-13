/*
    This file is part of Kompex SQLite Wrapper.
	Copyright (c) 2008-2010 Sven Broeske

    Kompex SQLite Wrapper is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Kompex SQLite Wrapper is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Kompex SQLite Wrapper. If not, see <http://www.gnu.org/licenses/>.
*/

#include "KompexSQLitePrerequisites.h"
#include "KompexSQLiteDatabase.h"
#include "KompexSQLiteStatement.h"
#include "KompexSQLiteException.h"
#include "KompexSQLiteStreamRedirection.h"

#include <iostream>
#include <exception>

void FunctionWithLocalVariable(Kompex::SQLiteStatement *stmt);

int main()
{
	// uncomment to redirect streams to a file
	//Kompex::CerrRedirection cerrRedirection("error.log");
	//Kompex::CoutRedirection coutRedirection("output.log");

	try
	{
		// create and open database
		Kompex::SQLiteDatabase *pDatabase = new Kompex::SQLiteDatabase("test.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0);
		// create statement instance for sql queries/statements
		Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(pDatabase);

		std::cout << "SQLite version: " << pDatabase->GetLibVersionNumber() << std::endl;

		// ---------------------------------------------------------------------------------------------------------
		// create table and insert some data
		pStmt->SqlStatement("CREATE TABLE user (userID INTEGER NOT NULL PRIMARY KEY, lastName VARCHAR(50) NOT NULL, firstName VARCHAR(50), age INTEGER, weight DOUBLE)");
		pStmt->SqlStatement("INSERT INTO user (userID, lastName, firstName, age, weight) VALUES (1, 'Lehmann', 'Jamie', 20, 65.5)");
		pStmt->SqlStatement("INSERT INTO user (userID, lastName, firstName, age, weight) VALUES (2, 'Burgdorf', 'Peter', 55, NULL)");
		pStmt->SqlStatement("INSERT INTO user (userID, lastName, firstName, age, weight) VALUES (3, 'Lehmann', 'Fernando', 18, 70.2)");
		pStmt->SqlStatement("INSERT INTO user (userID, lastName, firstName, age, weight) VALUES (4, 'Lehmann', 'Carlene ', 17, 50.8)");

		// ---------------------------------------------------------------------------------------------------------
		// insert some data with Bind..() methods
		pStmt->Sql("INSERT INTO user (userID, lastName, firstName, age, weight) VALUES(?, ?, ?, ?, ?);");
		pStmt->BindInt(1, 5);
		pStmt->BindString(2, "Murahama");
		pStmt->BindString(3, "Yura");
		pStmt->BindInt(4, 28);
		pStmt->BindDouble(5, 60.2);
		// executes the INSERT statement and cleans-up automatically
		pStmt->ExecuteAndFree();

		// ---------------------------------------------------------------------------------------------------------
		// lets have a look on a query which is shown in console
		std::cout << std::endl;
		pStmt->GetTable("SELECT firstName, userID, age, weight FROM user WHERE lastName = 'Lehmann';", 13);
		std::cout << std::endl;

		// some example SQLite aggregate functions
		std::cout << "COUNT(*): " << pStmt->SqlAggregateFuncResult("SELECT COUNT(*) FROM user WHERE lastName = 'Lehmann';") << std::endl;
		std::cout << "COUNT(weight): " << pStmt->SqlAggregateFuncResult("SELECT COUNT(weight) FROM user;") << std::endl;
		std::cout << "MAX(age): " << pStmt->SqlAggregateFuncResult("SELECT MAX(age) FROM user;") << std::endl;
		std::cout << "MIN(age): " << pStmt->SqlAggregateFuncResult("SELECT MIN(age) FROM user;") << std::endl;
		std::cout << "AVG(age): " << pStmt->SqlAggregateFuncResult("SELECT AVG(age) FROM user;") << std::endl;
		std::cout << "SUM(age): " << pStmt->SqlAggregateFuncResult("SELECT SUM(age) FROM user;") << std::endl;
		std::cout << "TOTAL(age): " << pStmt->SqlAggregateFuncResult("SELECT TOTAL(age) FROM user;") << std::endl;

		// ---------------------------------------------------------------------------------------------------------
		// sql query - searching for all people with lastName "Lehmann"
		pStmt->Sql("SELECT firstName FROM user WHERE lastName = 'Lehmann';");

		// after a Sql() call we can get some special information
		std::cout << "GetColumnName: " << pStmt->GetColumnName(0) << std::endl;
		std::cout << "GetColumnCount: " << pStmt->GetColumnCount() << std::endl;
		std::cout << "GetColumnDatabaseName: " << pStmt->GetColumnDatabaseName(0) << std::endl;
		std::cout << "GetColumnTableName: " << pStmt->GetColumnTableName(0) << std::endl;
		std::cout << "GetColumnOriginName: " << pStmt->GetColumnOriginName(0) << "\n" << std::endl;

		// do not forget to clean-up
		pStmt->FreeQuery();

		// ---------------------------------------------------------------------------------------------------------
		// another sql query
		pStmt->Sql("SELECT * FROM user WHERE firstName = 'Jamie';");
		// after a Sql() call we can get some other special information
		std::cout << "GetColumnName(0): " << pStmt->GetColumnName(0) << std::endl;
		std::cout << "GetColumnName(1): " << pStmt->GetColumnName(1) << std::endl;
		std::cout << "GetColumnName(2): " << pStmt->GetColumnName(2) << std::endl;
		std::cout << "GetColumnName(3): " << pStmt->GetColumnName(3) << std::endl;
		std::cout << "GetColumnName(4): " << pStmt->GetColumnName(4) << std::endl;
		std::cout << "GetColumnCount: " << pStmt->GetColumnCount() << std::endl;	
		std::cout << "GetColumnDeclaredDatatype(0): " << pStmt->GetColumnDeclaredDatatype(0) << std::endl;
		std::cout << "GetColumnDeclaredDatatype(1): " << pStmt->GetColumnDeclaredDatatype(1) << std::endl;
		std::cout << "GetColumnDeclaredDatatype(2): " << pStmt->GetColumnDeclaredDatatype(2) << std::endl;
		std::cout << "GetColumnDeclaredDatatype(3): " << pStmt->GetColumnDeclaredDatatype(3) << std::endl;
		std::cout << "GetColumnDeclaredDatatype(4): " << pStmt->GetColumnDeclaredDatatype(4) << std::endl;

		// process all results
		while(pStmt->FetchRow())
		{
			std::cout << "GetDataCount: " << pStmt->GetDataCount() << std::endl;
			std::cout << "SQL query - GetColumnDouble(0): " << pStmt->GetColumnDouble(0) << std::endl;
			std::cout << "SQL query - GetColumnString(1): " << pStmt->GetColumnString(1) << std::endl;
			std::cout << "SQL query - GetColumnString(2): " << pStmt->GetColumnString(2) << std::endl;
			std::cout << "SQL query - GetColumnString(3): " << pStmt->GetColumnString(3) << std::endl;
			std::cout << "SQL query - GetColumnString(4): " << pStmt->GetColumnString(4) << std::endl;
			std::cout << "\nColumnTypes (look at the documentation for the meaning of the numbers):\n";
			std::cout << "GetColumnType(0): " << pStmt->GetColumnType(0) << std::endl;
			std::cout << "GetColumnType(1): " << pStmt->GetColumnType(1) << std::endl;
			std::cout << "GetColumnType(2): " << pStmt->GetColumnType(2) << std::endl;
			std::cout << "GetColumnType(3): " << pStmt->GetColumnType(3) << std::endl;
			std::cout << "GetColumnType(4): " << pStmt->GetColumnType(4) << std::endl;
		}
		// do not forget to clean-up
		pStmt->FreeQuery();

		// ---------------------------------------------------------------------------------------------------------
		// a little example for prepared statements
		std::cout << "\nPrepared statement:\n";
		std::string preparedQuery = "SELECT * FROM user WHERE userID=@id";
		pStmt->Sql(preparedQuery);
			
		for(int i = 1; i <= 3; ++i)
		{
			// bind an integer to the prepared statement
			pStmt->BindInt(1, i);

			// and now fetch all results
			while(pStmt->FetchRow())
				std::cout << pStmt->GetColumnCString(0) << pStmt->GetColumnCString(1) << std::endl;

			// reset the prepared statement
			pStmt->Reset();
		}
		// do not forget to clean-up
		pStmt->FreeQuery();

		// ---------------------------------------------------------------------------------------------------------
		// get some instant results
		std::cout << "\nSELECT lastName FROM user WHERE userID = 3;\n" << pStmt->GetSqlResultString("SELECT lastName FROM user WHERE userID = 3");
		std::cout << "\nSELECT age FROM user WHERE userID = 4;\n" <<  pStmt->GetSqlResultInt("SELECT age FROM user WHERE userID = 4");
		std::cout << "\nSELECT weight FROM user WHERE userID = 3;\n" <<  pStmt->GetSqlResultDouble("SELECT weight FROM user WHERE userID = 3");

		// ---------------------------------------------------------------------------------------------------------
		// DELETE statement and get afterwards the number of affected rows
		pStmt->SqlStatement("DELETE FROM user WHERE lastName = 'Lehmann'");
		std::cout << "\n\nGetDatabaseChanges: " << pDatabase->GetDatabaseChanges() << std::endl;

		// let's see, how many changes we have done
		std::cout << "GetTotalDatabaseChanges: " << pDatabase->GetTotalDatabaseChanges() << std::endl;
		std::cout << std::endl;

		// ---------------------------------------------------------------------------------------------------------
		// get all metadata from one column
		pStmt->GetTableColumnMetadata("user", "userID");
		std::cout << std::endl;

		// ---------------------------------------------------------------------------------------------------------
		// now we want try a transaction
		// if an error occurs, a rollback is automatically performed
		// note: you must use Transaction()
		pStmt->BeginTransaction();
		pStmt->Transaction("INSERT INTO user (userID, lastName, firstName, age, weight) VALUES (10, 'Kanzaki', 'Makoto', 23, 76.9)");
		FunctionWithLocalVariable(pStmt);
		pStmt->Transaction("INSERT INTO user (userID, lastName, firstName, age, weight) VALUES (12, 'Kanzaki', 'Peter', 63, 101.1)");
		pStmt->CommitTransaction();

		// if you want react on errors by yourself, you can use a own try() and catch() block
		// note: you must use SqlStatement()
		try
		{
			pStmt->BeginTransaction();
			pStmt->SqlStatement("INSERT INTO user (userID, lastName, firstName, age, weight) VALUES (10, 'Kanzaki', 'Makoto', 23, 76.9)");
			pStmt->SqlStatement("INSERT INTO user (userID, lastName, firstName, age, weight) VALUES (11, 'Kanzaki', 'Yura', 20, 56.9)");
			pStmt->SqlStatement("INSERT INTO user (userID, lastName, firstName, age, weight) VALUES (12, 'Kanzaki', 'Peter', 63, 101.1)");
			pStmt->SqlStatement("INSERT INTO user (userID, lastName, firstName, age, weight) VALUES (10, 'Henschel', 'Robert', 10, 34.5)");
			pStmt->CommitTransaction();
		}
		catch(Kompex::SQLiteException &exception) 
		{
			std::cerr << "\nException Occured: " << exception.GetString();
			pStmt->RollbackTransaction();
			std::cerr << "Rollback was executed!" << std::endl;
			std::cerr << "This is our own catch() block!" << std::endl;
		}

		// clean-up
		delete pStmt;
		delete pDatabase;
	}
	catch(Kompex::SQLiteException &exception)
	{
		std::cerr << "\nException Occured" << std::endl;
		exception.Show();
	}

	/*
	complete example for the usage of file and memory databases
	(database layout is only fictitious)

	Kompex::SQLiteDatabase *pDatabase = new Kompex::SQLiteDatabase("scores.db", SQLITE_OPEN_READWRITE, 0);
	// move database to memory, so that we are work on the memory database hence
	pDatabase->MoveDatabaseToMemory();

	Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(pDatabase);
	// insert some data sets into the memory database
	pStmt->SqlStatement("INSERT INTO score(id, lastScore, avgScore) VALUES(1, 429, 341)");
	pStmt->SqlStatement("INSERT INTO score(id, lastScore, avgScore) VALUES(2, 37, 44)");
	pStmt->SqlStatement("INSERT INTO score(id, lastScore, avgScore) VALUES(3, 310, 280)");

	// save the memory database to a file
	// if you don't do it, all database changes will be lost after closing the memory database
	pDatabase->SaveDatabaseFromMemoryToFile("newScores.db");

	delete pStmt;
	delete pDatabase;
	*/

	std::cin.get();
	return 0;
}

void FunctionWithLocalVariable(Kompex::SQLiteStatement *stmt)
{
	const wchar_t *localVariable = L"INSERT INTO user (userID, lastName, firstName, age, weight) VALUES (11, 'Kanzaki', 'Yura', 20, 56.9)";
	// use SecureTransaction() which creates a internal copy of localVariable
	stmt->SecureTransaction(localVariable);
	// localVariable will be deleted on this end of scope now!
}
