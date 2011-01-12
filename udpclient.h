/*---------------------------------------------------------------------------
Anime Tracker - udp client for http://anidb.net/ 
----------------------------------------------------------------------------*/

#define	MAX_BUF		40000
class udpclient {
public:
	udpclient(int delay, log *rlog);
	~udpclient();
	int udpconnect(const char *server, int port);
	void udpdisconnect();
	void send(const char *buf);
	bool recieve();
	char* get_recieved();

private:
	int udp_delay;
	char* udp_recived;
	log *udp_log;
	
	int s;
	char rbuf[MAX_BUF];
	//struct sockaddr_in sock_in;
	//truct sockaddr_in local_in;


};
