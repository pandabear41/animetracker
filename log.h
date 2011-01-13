/*---------------------------------------------------------------------------
Anime Tracker - udp client for http://anidb.net/ 
----------------------------------------------------------------------------*/

#include <fstream>

using namespace std;

class log {
  public:
    log(char* filename);
    ~log();
    void write(const char* type, const char* logline);
    void error(const char* logline, ...);
    void warning(const char* logline, ...);
    void fatal(const char* logline, ...);
    void message(const char* logline, ...);
    void debug(const char* logline, ...);
  private:
    FILE *fp;
    void _open(char* filename);
    void _close();
};
