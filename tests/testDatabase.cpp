/*---------------------------------------------------------------------------
Anime Tracker - udp client for http://anidb.net/ 
----------------------------------------------------------------------------*/

#include <stdio.h>
#include "../database.h"


#include <iostream>
using namespace std;


int main() {
	Connection conn;
	conn.open("mydb.db"); // the argument is the database name.
	Statement* stmt = conn.createStatement();
	stmt->execute("create table IF NOT EXISTS albums(title,artist)"); // creates a table

	//stmt->execute(
	// "insert into albums values('Brothers in Arms','Dire Straits')");
	    // insert some data

	//stmt->execute("insert into albums values('Unplugged','Eric Clapton')");
	
	ResultSet* rslt = stmt->executeQuery("select * from albums");
	ResultSetMetaData* r_mtdt = rslt->getMetaData();
	int cols = r_mtdt->getColumnCount();
	while(rslt->next()) {
	  	for(int i=0;i<cols;i++) {
	    		printf("%s (%s): %s  ",r_mtdt->getColumnName(i+1).c_str(),
	    		r_mtdt->getColumnType(i+1).c_str(),rslt->getString(i+1).c_str());
	  	}
	  	printf("\n");
	}

}


