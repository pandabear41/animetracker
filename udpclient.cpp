/*---------------------------------------------------------------------------
Anime Tracker - udp client for http://anidb.net/ 
----------------------------------------------------------------------------*/

/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sysexits.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>


#include "log.h"
#include "udpclient.h"



udpclient::udpclient(int delay,log *rlog) {
	udp_delay = delay;
	s= -1;
	udp_log = rlog;
	connected = false;
	udp_log->write("Connection: UDP client loaded");
}

void udpclient::udpconnect(const char *server, int port) {
	struct hostent *hp;
	struct in_addr iaddr;
	struct sockaddr_in sock_in;
	struct sockaddr_in local_in;
	struct timeval resp_timeout = { 30, 0 };
	int x = 1;
	int rc;
	udp_log->write("Connection: Connecting..");
	if (connected) {
		udp_log->write("Connection: Already made a connection");
		return ;
	}
	
	bzero((char *)&sock_in, sizeof(sock_in));
	iaddr.s_addr = inet_addr(server);
	if (iaddr.s_addr != INADDR_NONE) {
		struct hostent *hp;
		hp = gethostbyaddr((char *)&iaddr, sizeof(iaddr), AF_INET);
		udp_log->write("Connection: Can not relolve ip %s: %s", server, hstrerror(h_errno));
		errx(EX_NOHOST, "cannot resolve ip %s: %s", server, hstrerror(h_errno));
		
	} else { 
		hp = gethostbyname(server);
		if (!hp) {
			udp_log->write("Connection: Can not relolve %s: %s", server, hstrerror(h_errno));
			errx(EX_NOHOST, "cannot resolve %s: %s", server, hstrerror(h_errno));
		}
		if ((unsigned)hp->h_length > sizeof(sock_in.sin_addr) ||
				hp->h_length < 0) {
			udp_log->write("Connection: Illegal address");
			errx(1, "gethostbyname: illegal address");
		}
	}
	sock_in.sin_family = hp->h_addrtype;
	//sock_in.sin_len = sizeof(sock_in); Is not used anymore
	memcpy(&sock_in.sin_addr, hp->h_addr_list[0],(unsigned)(hp->h_length));
	sock_in.sin_port = htons(port);
	s = socket(sock_in.sin_family, SOCK_DGRAM, IPPROTO_UDP);
	if (s < 0) {
		udp_log->write("Connection: Can not open socket");
		err(EX_PROTOCOL, "cannot open socket");
	}
	rc = setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &resp_timeout, sizeof(resp_timeout));
	if (rc < 0) {
		udp_log->write("Connection: Can not set timeout");
		err(EX_OSERR, "cannot set timeout");
	}
	rc = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &x, sizeof(x));
	if (rc < 0) {
		udp_log->write("Connection: Can not set address");
		err(EX_OSERR, "cannot set addr");
	}
	bzero((char *)&local_in, sizeof(local_in));
	//local_in.sin_len = sizeof(local_in); Is not used anymore
	local_in.sin_family = sock_in.sin_family;
	local_in.sin_port = htons(port);
	rc = bind(s, (struct sockaddr *)(&local_in), sizeof(local_in));
	if (rc < 0) {
		udp_log->write("Connection: Can not bind local port");
		err(EX_OSERR, "cannot bind");
	}
	if (connect(s, (struct sockaddr *)(&sock_in), sizeof(sock_in)) < 0) {
		udp_log->write("Connection: Can not connect to server");
		err(EX_OSERR, "cannot connect");
	}
	
	next_send = time(NULL);	
	connected = true;

	udp_log->write("Connection: Connected");
	return ;

}



void udpclient::udpdisconnect() {
	int rc;
	rc = shutdown(s, SHUT_RDWR);
	connected = false;
	udp_log->write("Connection: Disconnected");
}



bool udpclient::recieve() {
	long len;
	
	if (!connected) {
		udp_log->write("Connection: Make a connection before sending/receiving");
		return false;
	}
	bzero(gbuf, sizeof(gbuf));
	len = read(s, gbuf, sizeof(gbuf));
	if (len < 0) {
		udp_log->write("Connection: Read Failed");
		return false;
	}
	return true;
}

char* udpclient::get_recieved() {
	return gbuf;
}


void udpclient::send(const char *buf){
	time_t now;
	long delay;

	if (!connected) {
		udp_log->write("Connection: Make a connection before sending/receiving");
		return ;
	}
	now = time(NULL);
	delay = next_send - now;
	if (delay > 0) {
		udp_log->write("Connection: %i delay before send", delay);
		sleep((unsigned int)delay);
	}
	if ( write (s, buf, strlen (buf)) != strlen (buf)) {
		udp_log->write("Connection: Write Failed");
	}
	udp_log->write("Connection: Sent Packet: %s", buf);

	next_send = time(NULL) + udp_delay;
}


