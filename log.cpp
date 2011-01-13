#include <stdarg.h>
#include <stdio.h>

#include "log.h"

#define DEBUG

log::log(char* filename) {
	this->_open(filename);
}

log::~log(){
	this->_close();
}

void log::_open(char* filename) {
	if(filename != NULL) {
		fp = fopen(filename, "a+");
		if (fp != NULL)
			fseek(fp, 0, SEEK_END);
	}
}

void log::_close() {
	if(fp != NULL) 
		fclose(fp); 
	fp = NULL;
}
	
void log::fatal(const char* logline, ...) {
	va_list argList;
	char cbuffer[1024];
	va_start(argList, logline);
	vsnprintf(cbuffer, 1024, logline, argList);
	va_end(argList);
	this->write("FATAL", cbuffer);
}

void log::error(const char* logline, ...) {
	va_list argList;
	char cbuffer[1024];
	va_start(argList, logline);
	vsnprintf(cbuffer, 1024, logline, argList);
	va_end(argList);
	this->write("Error", cbuffer);
}

void log::warning(const char* logline, ...) {
	va_list argList;
	char cbuffer[1024];
	va_start(argList, logline);
	vsnprintf(cbuffer, 1024, logline, argList);
	va_end(argList);
	this->write("Warning", cbuffer);
}

void log::message(const char* logline, ...) {
	va_list argList;
	char cbuffer[1024];
	va_start(argList, logline);
	vsnprintf(cbuffer, 1024, logline, argList);
	va_end(argList);
	this->write("Message", cbuffer);
}

void log::debug(const char* logline, ...) {
#ifdef DEBUG
	va_list argList;
	char cbuffer[1024];
	va_start(argList, logline);
	vsnprintf(cbuffer, 1024, logline, argList);
	va_end(argList);
	this->write("Debug", cbuffer);
#endif
}


void log::write(const char* type, const char* logline) {
	if (fp != NULL) 
		fprintf(fp, "%s: %s\n", type, logline);
}
