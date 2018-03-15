#include <iostream>
#include <IniConfig.h>
#include <fstream>
#include <string>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;

IniConfig::IniConfig(string addr){
	project = new map<string, object>();
	this->path = addr;
}

IniConfig::~IniConfig(){
	delete(project);
}

bool IniConfig::readIni(){
	string line;
	string section;
	int index;
	ifstream f(path.c_str());
	if(!f.is_open()){
		return false;
	}
	while(getline(f, line)){
		if(line.substr(0, 1) == "#" || line.empty()){
			continue;
		}
		if(line.substr(0, 1) == "["){
			section = line.substr(1, line.length()-2);
			continue;
		}
		if(section.empty()){
			continue;
		}
		index = line.find("=");
		if(index == -1){
			continue;
		}
		if(project->find(section) == project->end()){
			object obj;
			(*project)[section] = move(obj);
		}
		object obj = (*project)[section];
		obj[line.substr(0, line.find("="))] = line.substr(line.find("=")+1, line.length());
		(*project)[section] = move(obj);
	}
	f.close();
	return true;
}

bool IniConfig::writeIni(){
	string data;
	ofstream f(path.c_str());
	if(!f.is_open()){
		return false;
	}
	map<string, object>::iterator it;
	for(it = project->begin(); it != project->end(); it++){
		data.append("[");
		data.append((*it).first);
		data.append("]");
		data.append("\n");
		object obj = (*it).second;
		map<string, string>::iterator ivalue;
		for(ivalue = obj.begin(); ivalue != obj.end(); ivalue++){
			data.append((*ivalue).first);
			data.append("=");
			data.append((*ivalue).second);
			data.append("\n");
		}
	}
	f.write(data.c_str(), strlen(data.c_str()));
	f.flush();
	f.close();
	return true;
}

void IniConfig::display(){
	map<string, object>::iterator it;
	for(it = project->begin(); it != project->end(); it++){
		cout << "[" << (*it).first << "]" << endl;
		object obj = (*it).second;
		map<string, string>::iterator ivalue;
		for(ivalue=obj.begin();ivalue != obj.end();ivalue++){
			cout << (*ivalue).first << "=" << (*ivalue).second << endl;
		}
	}
}

void IniConfig::clear(){
	map<string, object>::iterator it;
	for(it = project->begin(); it != project->end(); it++){
		project->erase((*it).first);
	}
}

void IniConfig::append(string section, string objt, string value){
	if(project->find(section) == project->end()){
		object obj;
		(*project)[section] = move(obj);
	}
	object obj = (*project)[section];
	obj[objt] = value;
	(*project)[section] = move(obj);
}

string IniConfig::getObject(string section, string key, string default_value){
	if(project->find(section) == project->end()){
		return default_value;
	}
	object obj = (*project)[section];
	if(obj.find(key) == obj.end()){
		return default_value;
	}
	return obj[key];
}

vector<string> IniConfig::getProject(string section){
	vector<string> list;
	map<string, object>::iterator it;
	for(it = project->begin(); it != project->end(); it++){
		if((*it).first == section){
			object obj = (*it).second;
			map<string, string>::iterator ivalue;
			for(ivalue = obj.begin(); ivalue != obj.end(); ivalue++){
				list.push_back((*ivalue).first);
			}
		}
	}
	return move(list);
}
