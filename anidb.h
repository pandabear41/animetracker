/*---------------------------------------------------------------------------
Anime Tracker - udp client for http://anidb.net/ 
----------------------------------------------------------------------------*/



class anidb {
public:
	anidb(const char *server, int port, bool cached, log logfile);
	~anidb();
	
	int send_version();
	int send_uptime();
	bool send_ping(bool nat);

	
	int status();
	void alive();


private:
	log *ani_log;
	char* last_command;
	int cur_status;
	
	processpacket(const char *packet);

}
