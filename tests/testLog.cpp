
#include <stdio.h>
#include "../log.h"


int main() {
	Log *pLog = new Log("errors.log");
  	pLog->Write("Going into our loop");
	for(int i = 0; i < 10; i++){
		char c[50];
    		sprintf(c, "Looped: %d times", i);
    		pLog->Write(c);
  	}
  	return 0;
}

