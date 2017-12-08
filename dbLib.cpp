/*
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This file implements functions used for database management
 * =========================================================================================
 */

#include "dbLib.h"

#include <time.h>
#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <cmath>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;

void strPrintTime(char *des, time_t &t)
{
    tm *pTime = gmtime(&t);
    strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);
}

void StoreEvent(L1List<ninjaEvent_t> &eList, void* pGData)
{
  GData *ptr = (GData*)pGData;
  L1Item<ninjaEvent_t> *p = eList.pointerHead();
  while(p)
  {
    ptr->eve += string((p->data).code) + " ";
    p = p->pNext;
  }
  (ptr->eve).pop_back();
}

void loadNinjaDB(char *fName, L1List<NinjaInfo_t> &db)
{
    // TODO: write code to load information from file into db
    fstream f;
    f.open(fName, ios::in);
    string temp;
    string time;
    string id;
    string _longitude, _latitude;
    string s1;
    getline(f, s1);
    while (getline(f, s1, '\n'))
    {
        if (s1 == "")
            continue;
        stringstream s(s1);
        NinjaInfo_t Info;

        //TO DO get data from csv file on 1 line
        getline(s, temp, ',');
        getline(s, time, ',');
        getline(s, id, ',');
        getline(s, _longitude, ',');
        getline(s, _latitude, ',');
        getline(s, temp, ',');
        getline(s, temp, ',');
        getline(s, temp, ',');
        getline(s, temp, '\n');

        stringstream ss(time);
        //TO DO convert the time from string to time_t in UTC
        tm t;
        stringstream((time.substr(0, 2))) >> t.tm_mon;
        t.tm_mon--;
        stringstream((time.substr(3, 2))) >> t.tm_mday;
        stringstream((time.substr(6, 4))) >> t.tm_year;
        t.tm_year -= 1900;
        stringstream((time.substr(11, 2))) >> t.tm_hour;
        stringstream((time.substr(14, 2))) >> t.tm_min;
        stringstream((time.substr(17, 2))) >> t.tm_sec;
        Info.timestamp = timegm(&t);
        ss.clear();

        if (id.length() < 4)
            id = string(4 - id.length(), '0') + id;
        //TO DO copy string id to char* id of Info
        strcpy(Info.id, id.data());

        ss.str(_longitude);
        //TO DO store longitude
        ss >> Info.longitude;
        ss.clear();

        ss.str(_latitude);
        //TO DO store latitude
        ss >> Info.latitude;
        ss.clear();
        db.insertTail(Info);
    }
    f.close();
}

bool parseNinjaInfo(char *pBuf, NinjaInfo_t &nInfo)
{
    // TODO: write code to parse information from a string buffer, ignore if you don't use it

    return true;
}

void process(L1List<ninjaEvent_t> &eventList, L1List<NinjaInfo_t> &bList)
{
    void *pGData = NULL;
    initNinjaGlobalData(&pGData);
    StoreEvent(eventList, pGData);

    while (!eventList.isEmpty())
    {
        if (!processEvent(eventList[0], bList, pGData))
            cout << eventList[0].code << " is an invalid event\n";
        eventList.removeHead();
    }

    releaseNinjaGlobalData(pGData);
}

bool initNinjaGlobalData(void **pGData)
{
    /// TODO: You should define this function if you would like to use some extra data
    /// the data should be allocated and pass the address into pGData
    GData *ptr = new GData();
    *(pGData) = (void *)(ptr);
    return true;
}

void releaseNinjaGlobalData(void *pGData)
{
    /// TODO: You should define this function if you allocated extra data at initialization stage
    /// The data pointed by pGData should be released
    GData *ptr = (GData *)pGData;
    delete ptr;
    pGData = NULL;
    ptr = NULL;
}

void printNinjaInfo(NinjaInfo_t &b)
{
    printf("%s: (%0.5f, %0.5f), %s\n", b.id, b.longitude, b.latitude, ctime(&b.timestamp));
}

/// This function converts decimal degrees to radians
double deg2rad(double deg)
{
    return (deg * pi / 180);
}

///  This function converts radians to decimal degrees
double rad2deg(double rad)
{
    return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d)
{
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r) / 2);
    v = sin((lon2r - lon1r) / 2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}
