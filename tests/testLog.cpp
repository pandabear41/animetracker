
#include <stdio.h>
#include "../log.h"


int main() {
	log *pLog = new log("errors.log");
  	pLog->write("Going into our loop");
	for(int i = 0; i < 10; i++){
		char c[50];
    		sprintf(c, "Looped: %d times", i);
    		pLog->write(c);
  	}
  	return 0;
}

