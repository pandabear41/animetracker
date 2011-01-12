/*---------------------------------------------------------------------------
Anime Tracker - udp client for http://anidb.net/ 
----------------------------------------------------------------------------*/


class udpclient {
public:
	udpclient(int delay);
	~udpclient();
	int connect(const char *server, int port);
	void disconnect();
	void send(const char *buf, size_t len);
	bool recieve();
	char* get_recieved();

private:
	int delay;
	char* recived;

}
