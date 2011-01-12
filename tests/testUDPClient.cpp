


#include "../log.h"
#include "../udpclient.h"

int main() {
	log *pLog = new log("connection.log");
	udpclient *udp = new udpclient(5,pLog);
	udp->udpconnect("api.anidb.net",9000);
	udp->send("PING");
	udp->recieve();
	pLog->write("Recieved text from PING: %s",udp->get_recieved());	
	udp->send("PING");
	udp->recieve();
	pLog->write("Recieved text from PING: %s",udp->get_recieved());	
	udp->udpdisconnect();
}
