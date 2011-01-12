


#include "../log.h"
#include "../udpclient.h"

int main() {
	log *pLog = new log("connection.log");
	udpclient *udp = new udpclient(4,pLog);
	udp->udpconnect("api.anidb.net",9000);
	udp->send("PING");
	udp->recieve();
	sleep(1);
	udp->send("PING");
	udp->recieve();
	udp->udpdisconnect();
}
