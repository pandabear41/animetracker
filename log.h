#include <fstream>

using namespace std;

class Log {
  public:
    Log(char* filename);
    ~Log();
    void Write(const char* logline, ...);
  private:
    ofstream m_stream;
};
