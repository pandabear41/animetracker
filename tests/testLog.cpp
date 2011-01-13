/*---------------------------------------------------------------------------
Anime Tracker - udp client for http://anidb.net/ 
----------------------------------------------------------------------------*/

#include <stdio.h>
#include "../log.h"


int main() {
	log *pLog = new log("errors.log");
  	pLog->warning("Going into our loop");
	for(int i = 0; i < 10; i++){
		char c[50];
    		sprintf(c, "Looped: %d times", i);
    		pLog->error(c);
  	}
  	return 0;
}

