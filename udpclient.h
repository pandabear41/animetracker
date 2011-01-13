/*---------------------------------------------------------------------------
Anime Tracker - udp client for http://anidb.net/ 
----------------------------------------------------------------------------*/

#define	BUF_LEN		50000
#define RETRY_TIMES	2
class udpclient {
public:
	udpclient(int delay, log *rlog);
	~udpclient();
	bool udpconnect(const char *server, int port);
	void udpdisconnect();
	void send(const char *buf);
	bool recieve();
	char* get_recieved();

private:
	int udp_delay;
	int s;
	int retry;
	log *udp_log;
	time_t next_send;
	bool connected;
	char gbuf[BUF_LEN];



};
