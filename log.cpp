#include <stdarg.h>


#include "log.h"

log::log(char* filename) {
  m_stream.open(filename, ios_base::app);
}

log::~log(){
  m_stream.close();
}

void log::write(const char* logline, ...){
  va_list argList;
  char cbuffer[1024];
  va_start(argList, logline);
  vsnprintf(cbuffer, 1024, logline, argList);
  va_end(argList);
  m_stream << cbuffer << endl;
}
