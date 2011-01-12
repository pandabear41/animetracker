/*---------------------------------------------------------------------------
Anime Tracker - udp client for http://anidb.net/ 
----------------------------------------------------------------------------*/

#define	BUF_LEN		50000
class udpclient {
public:
	udpclient(int delay, log *rlog);
	~udpclient();
	void udpconnect(const char *server, int port);
	void udpdisconnect();
	void send(const char *buf);
	bool recieve();
	char* get_recieved();

private:
	int udp_delay;
	int s;
	log *udp_log;
	time_t next_send;
	bool connected;
	char gbuf[BUF_LEN];



};
