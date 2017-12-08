/*
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for database management
 * =========================================================================================
 */

#ifndef A01_DBLIB_H
#define A01_DBLIB_H

#include <string>
#include <string.h>
#include <time.h>
#include <iostream>
#include <iomanip>

#include "listLib.h"
#include "eventLib.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define ID_MAX_LENGTH   10

typedef struct NinjaInfo {
    char    id[ID_MAX_LENGTH];
    time_t  timestamp;
    double  longitude, latitude;

    // default constructor
    NinjaInfo() {
        strcpy(id, "");
    }
    NinjaInfo(const char* ninjaID) {
        strcpy(id, ninjaID);
    }
    // copy constructor
    NinjaInfo(NinjaInfo& ninja) : timestamp(ninja.timestamp), longitude(ninja.longitude), latitude(ninja.latitude) {
        strcpy(id, ninja.id);
    }
} NinjaInfo_t;

void    printNinjaInfo(NinjaInfo_t& n);
void    strPrintTime(char* des, time_t& t);
bool    parseNinjaInfo(char* pBuf, NinjaInfo_t& nInfo);
void    loadNinjaDB(char* fName, L1List<NinjaInfo_t> &db);
double  distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

inline bool operator==(NinjaInfo_t& lhs, char* rhs) {
    return strcmp(lhs.id, rhs) == 0;
}
inline bool operator==(char* lhs, NinjaInfo_t& rhs)  {
    return strcmp(rhs.id, lhs) == 0;
}
inline bool operator==(NinjaInfo_t& lhs, NinjaInfo_t& rhs) {
    return strcmp(lhs.id, rhs.id) == 0;
}
inline bool operator!=(NinjaInfo_t& lhs, char* rhs) {
    return !(lhs == rhs);
}
inline bool operator!=(char* lhs, NinjaInfo_t& rhs)  {
    return !(rhs == lhs);
}
inline bool operator!=(NinjaInfo_t& lhs, NinjaInfo_t& rhs) {
    return !(lhs == rhs);
}

bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList, void* pGData);
void process(L1List<ninjaEvent_t>& eventList, L1List<NinjaInfo_t>& nList);

/// NOTE: student may create this function to allocate some global data
bool initNinjaGlobalData(void** pGData);
void releaseNinjaGlobalData(void* pGData);

#endif //A01_DBLIB_H
