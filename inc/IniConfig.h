#ifndef INICONFIG_H
#define INICONFIG_H

#include <iostream>
#include <map>
#include <vector>
using namespace std;

class IniConfig{
public:
	IniConfig(string addr);
	~IniConfig();
	bool readIni();
	bool writeIni();
	void display();
	void clear();
	void append(string section, string key, string value);
	string getObject(string section, string key, string value);
	vector<string> getProject(string addr);

private:
	typedef map<string, string> object;
	map<string, object>* project;
	string path;
};

#endif
