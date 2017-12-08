/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"
#include <cmath>
#define MeasurementError 0.005
#define epsilon 0.005
////////////////// Needed functions /////////////////////
bool IsStopped(NinjaInfo_t &n1, NinjaInfo_t &n2)
{
    return (abs(distanceEarth(n1.latitude, n1.longitude, n2.latitude, n2.longitude)) <= 0.005) ? true : false;
}
double GetDistance(NinjaInfo_t &n1, NinjaInfo_t &n2)
{
    return abs(distanceEarth(n1.latitude, n1.longitude, n2.latitude, n2.longitude));
}
double GetTime(NinjaInfo_t &n1, NinjaInfo_t &n2)
{
    return abs(difftime(n2.timestamp, n1.timestamp));
}
bool CoordinateEqual(NinjaInfo_t &n1, NinjaInfo_t &n2)
{
    if (GetDistance(n1, n2) <= MeasurementError)
        return true;
    return false;
}
bool IsGreater(NinjaData &n1, NinjaData &n2)
{
    return n1 > n2;
}
bool CheckID(GData *&ptr, char *&id)
{
    NinjaData t(id);
    return ((ptr->ninjas)->data).traverse(Ninjas::Equal, t);
}
////////////////// Event Function ///////////////////////
int Code3(GData *&ptr)
{
    //The number of attending ninjas
    return ((ptr->ninjas)->data).getSize();
}
char *Code4(GData *&ptr)
{
    //Get the largest ninja's id number
    char *x = new char[ID_MAX_LENGTH];
    if (((ptr->ninjas)->data).isEmpty())
    {
        strcpy(x, "empty");
    }
    else
    {
        NinjaData ans((((ptr->ninjas)->data).at(0)).id);
        ((ptr->ninjas)->data).traverseGreater(IsGreater, ans);
        strcpy(x, ans.id);
    }
    return x;
}
bool Code5(L1List<NinjaInfo_t> &db, char *&id, time_t &t)
{
    //ninja's first_start_moving_time
    L1Item<NinjaInfo_t> *p = db.pointerHead();
    bool first = false;
    NinjaInfo_t Info;
    NinjaInfo_t startStop;
    bool move = true;
    bool first_move = true;
    while (p)
    {
        if (strcmp((p->data).id, id) == 0)
        {
            if (!first)
            {
                first = true;
                Info = p->data;
                t = Info.timestamp;
                p = p->pNext;
                continue;
            }
            else
            {
                if (move)
                {
                    if (IsStopped(Info, p->data))
                    {
                        startStop = Info;
                        move = false;
                    }
                    else
                    {
                        t = Info.timestamp;
                        return true;
                    }
                }
                else
                {
                    if (!IsStopped(startStop, p->data))
                    {
                        t = (p->data).timestamp;
                        return true;
                    }
                }
                first_move = false;
            }
            Info = p->data;
        }
        p = p->pNext;
    }
    if (first_move)
        return true;
    return false;
}
bool Code6(L1List<NinjaInfo_t> &db, char *&id, time_t &t)
{
    //Last_start_stopping time
    L1Item<NinjaInfo_t> *p = db.pointerHead();
    NinjaInfo_t Info;
    NinjaInfo_t startStop;
    bool first = false;
    bool move = true;
    bool have_stopped = false;
    while (p)
    {
        if (strcmp((p->data).id, id) == 0)
        {
            if (!first)
            {
                first = true;
                Info = p->data;
                p = p->pNext;
                continue;
            }
            else
            {
                if (move)
                {
                    if (IsStopped(Info, p->data))
                    {
                        startStop = Info;
                        t = Info.timestamp;
                        have_stopped = true;
                        move = false;
                    }
                }
                else
                {
                    if (!IsStopped(startStop, p->data))
                    {
                        move = true;
                    }
                }
            }
            Info = p->data;
        }
        p = p->pNext;
    }
    return have_stopped;
}
int Code7(L1List<NinjaInfo_t> &db, char *&id)
{
    int count = 0;
    L1Item<NinjaInfo_t> *p = db.pointerHead();
    NinjaInfo_t Info;
    NinjaInfo_t startStop;
    bool first = false;
    bool move = true;
    while (p)
    {
        if (strcmp((p->data).id, id) == 0)
        {
            if (!first)
            {
                first = true;
                Info = p->data;
                p = p->pNext;
                continue;
            }
            else
            {
                if (move)
                {
                    if (IsStopped(Info, p->data))
                    {
                        startStop = Info;
                        count++;
                        move = false;
                    }
                }
                else
                {
                    if (!IsStopped(startStop, p->data))
                    {
                        move = true;
                    }
                }
            }
            Info = p->data;
        }
        p = p->pNext;
    }
    return count;
}
double Code8(L1List<NinjaInfo_t> &db, char *&id)
{
    //Moving distance
    double count = 0;
    L1Item<NinjaInfo_t> *p = db.pointerHead();
    NinjaInfo_t Info;
    bool first = false;
    while (p)
    {
        if (strcmp((p->data).id, id) == 0)
        {
            if (!first)
            {
                first = true;
                Info = p->data;
                p = p->pNext;
                continue;
            }
            else
            {
                count += GetDistance(Info, p->data);
            }
            Info = p->data;
        }
        p = p->pNext;
    }
    return count;
}
char *Code9(L1List<NinjaInfo_t> &db, GData *&ptr)
{
    //moved longest distance
    if (!(ptr->_code9))
    {
        L1Item<NinjaData> *p = ((ptr->ninjas)->data).pointerHead();
        char *maxid = new char[ID_MAX_LENGTH];
        strcpy(maxid, "-1");
        if (p)
        {
            double max = -1;
            while (p)
            {
                L1Item<NinjaInfo_t> *d = db.pointerHead();
                NinjaInfo_t Info;
                bool first = false;
                while (d)
                {
                    if (strcmp((d->data).id, (p->data).id) != 0)
                    {
                        d = d->pNext;
                        continue;
                    }
                    if (!first)
                    {
                        first = true;
                        Info = d->data;
                    }
                    else
                    {
                        (p->data).moving_distance += GetDistance(Info, d->data);
                    }
                    Info = d->data;
                    d = d->pNext;
                }
                if ((p->data).moving_distance > max)
                {
                    max = (p->data).moving_distance;
                    strcpy(maxid, (p->data).id);
                }
                p = p->pNext;
            }
        }
        (ptr->_code9) = true;
        return maxid;
    }
    else
    {
        L1Item<NinjaData> *p = ((ptr->ninjas)->data).pointerHead();
        char *maxid = new char[ID_MAX_LENGTH];
        strcpy(maxid, "-1");
        if (p)
        {
            double max = (p->data).moving_distance;
            strcpy(maxid, (p->data).id);
            p = p->pNext;
            while (p)
            {
                if ((p->data).moving_distance > max)
                {
                    max = (p->data).moving_distance;
                    strcpy(maxid, (p->data).id);
                }
                p = p->pNext;
            }
        }
        return maxid;
    }
}
char *Code10(L1List<NinjaInfo_t> &db, GData *&ptr)
{
    //ninja's id having longest moving time
    if (!(ptr->_code10))
    {
        L1Item<NinjaData> *p = ((ptr->ninjas)->data).pointerHead();
        char *maxid = new char[ID_MAX_LENGTH];
        strcpy(maxid, "-1");
        if (p)
        {
            double max = -1;
            while (p)
            {
                L1Item<NinjaInfo_t> *d = db.pointerHead();
                NinjaInfo_t Info;
                NinjaInfo_t startStop;
                bool first = false;
                bool move = true;
                while (d)
                {
                    if (strcmp((d->data).id, (p->data).id) != 0)
                    {
                        d = d->pNext;
                        continue;
                    }
                    if (!first)
                    {
                        first = true;
                        Info = d->data;
                    }
                    else
                    {
                        if (move)
                        {
                            if (IsStopped(Info, d->data))
                            {
                                move = false;
                                startStop = Info;
                            }
                            else
                            {
                                (p->data).moving_time += GetTime(Info, d->data);
                            }
                        }
                        else
                        {
                            if (!IsStopped(startStop, d->data))
                            {
                                move = true;
                                if (GetTime(startStop, Info) != 0)
                                    (p->data).moving_time += GetTime(Info, d->data);
                            }
                        }
                    }
                    Info = d->data;
                    d = d->pNext;
                }
                if ((p->data).moving_time > max)
                {
                    max = (p->data).moving_time;
                    strcpy(maxid, (p->data).id);
                }
                p = p->pNext;
            }
        }
        (ptr->_code10) = true;
        return maxid;
    }
    else
    {
        L1Item<NinjaData> *p = ((ptr->ninjas)->data).pointerHead();
        char *maxid = new char[ID_MAX_LENGTH];
        strcpy(maxid, "-1");
        if (p)
        {
            double max = (p->data).moving_time;
            strcpy(maxid, (p->data).id);
            p = p->pNext;
            while (p)
            {
                if ((p->data).moving_time > max)
                {
                    max = (p->data).moving_time;
                    strcpy(maxid, (p->data).id);
                }
                p = p->pNext;
            }
        }
        return maxid;
    }
}
char *Code11(GData *&ptr, const char *id)
{
    //Attacked ninja
    L1Item<NinjaData> *p = ((ptr->ninjas)->data).pointerHead();
    char *maxid = new char[ID_MAX_LENGTH];
    strcpy(maxid, "-1");
    if (p)
    {
        bool first = false;
        while (p)
        {
            if (!first)
            {
                if (strcmp((p->data).id, id) < 0)
                {
                    strcpy(maxid, (p->data).id);
                    first = true;
                }
            }
            else
            {
                if (strcmp((p->data).id, id) < 0 && strcmp((p->data).id, maxid) > 0)
                {
                    strcpy(maxid, (p->data).id);
                }
            }
            p = p->pNext;
        }
        (ptr->ninjas)->remove(maxid);
    }
    return maxid;
}
char *Code12(L1List<NinjaInfo_t> &db, GData *&ptr)
{
    //ninja who has the longest stopping time
    if (!(ptr->_code12))
    {
        L1Item<NinjaData> *p = ((ptr->ninjas)->data).pointerHead();
        char *maxid = new char[ID_MAX_LENGTH];
        strcpy(maxid, "-1");
        if (p)
        {
            double max = -1;
            while (p)
            {
                L1Item<NinjaInfo_t> *d = db.pointerHead();
                NinjaInfo_t Info;
                NinjaInfo_t startStop;
                bool first = false;
                bool move = true;
                while (d)
                {
                    if (strcmp((d->data).id, (p->data).id) != 0)
                    {
                        d = d->pNext;
                        continue;
                    }
                    if (!first)
                    {
                        first = true;
                        Info = d->data;
                    }
                    else
                    {
                        if (move)
                        {
                            if (IsStopped(Info, d->data))
                            {
                                move = false;
                                startStop = Info;
                                (p->data).stopping_time += GetTime(Info, d->data);
                            }
                        }
                        else
                        {
                            if (!IsStopped(startStop, d->data))
                            {
                                move = true;
                            }
                            else
                            {
                                (p->data).stopping_time += GetTime(Info, d->data);
                            }
                        }
                    }
                    Info = d->data;
                    d = d->pNext;
                }
                if ((p->data).stopping_time > max)
                {
                    max = (p->data).stopping_time;
                    strcpy(maxid, (p->data).id);
                }
                p = p->pNext;
            }
        }
        (ptr->_code12) = true;
        return maxid;
    }
    else
    {
        L1Item<NinjaData> *p = ((ptr->ninjas)->data).pointerHead();
        char *maxid = new char[ID_MAX_LENGTH];
        strcpy(maxid, "-1");
        if (p)
        {
            double max = (p->data).stopping_time;
            strcpy(maxid, (p->data).id);
            p = p->pNext;
            while (p)
            {
                if ((p->data).stopping_time > max)
                {
                    max = (p->data).stopping_time;
                    strcpy(maxid, (p->data).id);
                }
                p = p->pNext;
            }
        }
        return maxid;
    }
}
string Code14(L1List<NinjaInfo_t> &db, GData *&ptr)
{
    //Find all lost ninjas
    if (!(ptr->_code14))
    {
        L1Item<NinjaData> *p = ((ptr->ninjas)->data).pointerHead();
        string ans = ((p == NULL) ? "-1 " : "");
        while (p)
        {
            L1Item<NinjaInfo_t> *d = db.pointerHead();
            NinjaInfo_t Info;
            NinjaInfo_t startStop;
            L1List<NinjaInfo_t> record;
            bool first = false;
            bool move = true;
            while (d)
            {
                if (strcmp((d->data).id, (p->data).id) != 0)
                {
                    d = d->pNext;
                    continue;
                }
                if (!first)
                {
                    first = true;
                    Info = d->data;
                    record.insertTail(Info);
                }
                else
                {
                    if (move)
                    {
                        if (IsStopped(Info, d->data))
                        {
                            move = false;
                            startStop = Info;
                        }
                        else
                        {
                            if (record.traverse(CoordinateEqual, d->data))
                            {
                                (p->data).IsLost = true;
                                ans += string((p->data).id) + " ";
                                break;
                            }
                            record.insertTail(d->data);
                        }
                    }
                    else
                    {
                        if (!IsStopped(startStop, d->data))
                        {
                            move = true;
                            if (record.traverse(CoordinateEqual, d->data))
                            {
                                (p->data).IsLost = true;
                                ans += string((p->data).id) + " ";
                                break;
                            }
                            record.insertTail(d->data);
                        }
                    }
                }
                Info = d->data;
                d = d->pNext;
            }
            record.destroy();
            p = p->pNext;
        }
        (ptr->_code14) = true;
        if(ans == "")
            ans = "-1";
        else ans.pop_back();
        return ans;
    }
    else
    {
        L1Item<NinjaData> *p = ((ptr->ninjas)->data).pointerHead();
        string ans = ((p == NULL) ? "-1 " : "");
        while (p)
        {
            if ((p->data).IsLost)
                ans += string((p->data).id) + " ";
            p = p->pNext;
        }
        if (ans == "")
            ans = "-1";
        else ans.pop_back();
        return ans;
    }
}
void InitGData(GData *&ptr, L1List<NinjaInfo_t> &db)
{
    L1Item<NinjaInfo_t> *p = db.pointerHead();
    if (p)
        ptr->FirstID = string((p->data).id);
    while (p)
    {
        if (p->pNext == NULL)
            ptr->LastID = string((p->data).id);
        char *id = new char[ID_MAX_LENGTH];
        strcpy(id, (p->data).id);
        (ptr->ninjas)->insert(id);
        p = p->pNext;
    }
}
bool processEvent(ninjaEvent_t &event, L1List<NinjaInfo_t> &nList, void *pGData)
{
    // TODO: Your code comes here
    GData *ptr = (GData *)pGData;
    if (!ptr->init)
    {
        InitGData(ptr, nList);
        ptr->init = true;
    }
    /// NOTE: The output of the event will be printed on one line
    /// end by the endline character.
    string code(event.code);
    if (code[0] == '0')
    {
        cout << code << ": ";
        cout << ptr->eve << endl;
        return true;
    }
    else if (code == "1")
    {
        cout << code << ": ";
        //Print the first ninja's ID
        cout << ((ptr->FirstID == "") ? "empty" : ptr->FirstID) << endl;
        return true;
    }
    else if (code == "2")
    {
        cout << code << ": ";
        //Print the last ninja's ID
        cout << ((ptr->LastID == "") ? "empty" : ptr->LastID) << endl;
        return true;
    }
    else if (code == "3")
    {
        cout << code << ": ";
        //Print the number of ninja attending the competition
        cout << Code3(ptr) << endl;
        return true;
    }
    else if (code == "4")
    {
        cout << code << ": ";
        //Print the largest ninja's id number
        cout << Code4(ptr) << endl;
        return true;
    }
    else if (code[0] == '5' && code.length() > 1)
    {
        cout << code << ": ";
        //Print ninja's first_start_moving_time
        string id = code.substr(1, code.length() - 1);
        time_t ans;
        char *_id = new char[ID_MAX_LENGTH];
        strcpy(_id, id.data());
        if (!CheckID(ptr, _id))
        {
            cout << "-1" << endl;
            return true;
        }
        if (Code5(nList, _id, ans))
        {
            char *out = new char[26];
            strPrintTime(out, ans);
            cout << out << endl;
        }
        else
            cout << "empty" << endl;
        return true;
    }
    else if (code[0] == '6' && code.length() > 1)
    {
        cout << code << ": ";
        //Print ninja's last_start_stopping_time
        string id = code.substr(1, code.length() - 1);
        char *_id = new char[ID_MAX_LENGTH];
        strcpy(_id, id.data());
        if (!CheckID(ptr, _id))
        {
            cout << "-1" << endl;
            return true;
        }
        time_t ans;
        if (Code6(nList, _id, ans))
        {
            char *out = new char[26];
            strPrintTime(out, ans);
            cout << out << endl;
        }
        else
            cout << "Non-stop" << endl;
        return true;
    }
    else if (code[0] == '7' && code.length() > 1)
    {
        cout << code << ": ";
        //Print ninja's number_of_stopping_time
        string id = code.substr(1, code.length() - 1);
        char *_id = new char[ID_MAX_LENGTH];
        strcpy(_id, id.data());
        if (!CheckID(ptr, _id))
            cout << "-1" << endl;
        else
            cout << Code7(nList, _id) << endl;
        return true;
    }
    else if (code[0] == '8' && code.length() > 1)
    {
        cout << code << ": ";
        //Print ninja's moving_distance
        string id = code.substr(1, code.length() - 1);
        char *_id = new char[ID_MAX_LENGTH];
        strcpy(_id, id.data());
        if (!CheckID(ptr, _id))
        {
            cout << "-1" << endl;
            return true;
        }
        cout << Code8(nList, _id) << endl;
        return true;
    }
    else if (code == "9")
    {
        cout << code << ": ";
        //Print the ninja's id who has moved the longest distance
        cout << Code9(nList, ptr) << endl;
        return true;
    }
    else if (code == "10")
    {
        cout << code << ": ";
        //Print ninja's id having longest moving time
        cout << Code10(nList, ptr) << endl;
        return true;
    }
    else if (code.substr(0, 2) == "11" && code.length() >= 3)
    {
        cout << code << ": ";
        //Print the ninja's id who was attacked by the ninja with this id
        string id = code.substr(2, code.length() - 2);
        char *ans = Code11(ptr, id.c_str());
        if (strcmp(ans, "-1") != 0)
        {
            NinjaInfo_t del(ans);
            nList.removeAll(del);
        }
        cout << ans << endl;
        return true;
    }
    else if (code == "12")
    {
        cout << code << ": ";
        //Print ninja's id having longest stopping time
        cout << Code12(nList, ptr) << endl;
        return true;
    }
    else if (code.substr(0, 2) == "13" && code.length() > 2)
    {
        return true;
    }
    else if (code == "14")
    {
        cout << code << ": ";
        //Print all lost Ninjas
        cout << Code14(nList, ptr) << endl;
        return true;
    }
    return false;
}
