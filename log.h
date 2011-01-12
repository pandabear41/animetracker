

using namespace std;

class log {
  public:
    log(char* filename);
    ~log();
    void write(const char* logline, ...);
  private:
    ofstream m_stream;
};
