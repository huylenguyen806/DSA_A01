/*
 * =========================================================================================
 * Name        : eventLib.h
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#ifndef A01_EVENTLIB_H
#define A01_EVENTLIB_H

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

#include "listLib.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define EVENT_CODE_SIZE     20
using namespace std;

typedef struct ninjaEvent {
    char        code[EVENT_CODE_SIZE];

    ninjaEvent() {
        strcpy(code, "0");// default event is "0"
    }
    ninjaEvent(char* str) {
        strncpy(code, str, EVENT_CODE_SIZE - 1);
    }
    ninjaEvent(string& str) {
        strncpy(code, str.data(), EVENT_CODE_SIZE - 1);
    }
    ninjaEvent(ninjaEvent& a) { // copy constructor
        memcpy(code, a.code, EVENT_CODE_SIZE);
    }
} ninjaEvent_t;

void loadEvents(char* fName, L1List<ninjaEvent_t> &eList);

#endif //A01_EVENTLIB_H
