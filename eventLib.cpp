/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "eventLib.h"

/// NOTE: each event will be separated by spaces, or endline character
void loadEvents(char* fName, L1List<ninjaEvent_t> &eList) {
	//TODO
	fstream f;
	f.open(fName, ios::in); // open file

	/// Read, store DB into eList
	string EventsDB;
	while (!f.eof()) {
		getline(f, EventsDB);
		if (EventsDB == "") continue;
		stringstream ss(EventsDB);
		while (!ss.eof()) {
			string str;
			ss >> str;
			if (str == "") continue;
			if(str[str.length() - 1] == ';'){
				str = str.substr(0,str.length() - 1);
			}
			ninjaEvent_t temp(str);
			eList.insertTail(temp);
			str.clear();
		}
		ss.str("");
		ss.clear();
		EventsDB.clear();
	}
	f.close(); //close file
}
