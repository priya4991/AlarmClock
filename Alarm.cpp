#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <iostream>
using namespace std;

class alarm {
    public:
    tm alarmtime, presenttime, timedifference;
    time_t now;
    alarm()
    {
        now = time(0);
        presenttime = *localtime(&now);
        alarmtime = presenttime;
        alarmtime.tm_sec = 0;
    }

    void getTime() 
    {
        string time;
        cout << "Enter alarm in 24 hour format hh:mm - ";
        getline(cin, time);
        int pos = 0, h;
        while((pos = time.find(':')) != string::npos) 
        {
            string token = time.substr(0, pos);
            stringstream convert(token);
            convert >> alarmtime.tm_hour;
            time.erase(0, pos+1);
        }
        stringstream convert(time);
        convert >> alarmtime.tm_min;
    }

    void findTimeDifference() 
    {
        int sec = difftime(mktime(&alarmtime), now);
        if (sec < 0)
        {
            // Handle past alarm time by adding 24 hours
            sec += 24 * 60 * 60; // 24 hours in seconds
        }

        timedifference.tm_min = sec / 60;
        timedifference.tm_hour = timedifference.tm_min / 60;
        timedifference.tm_min = timedifference.tm_min % 60;
        timedifference.tm_sec = sec % 60;
    }

    void fireAlarm() 
    {
        while(true) 
        {
            system("clear");
            now = time(0);
            presenttime = *localtime(&now);
            findTimeDifference();
            cout << "Time remaining: " << timedifference.tm_hour << ":" << timedifference.tm_min << ":" << timedifference.tm_sec << endl;
            if (timedifference.tm_hour == 0 && timedifference.tm_min == 0 && timedifference.tm_sec == 0) 
            {
                cout << endl << "Time ended" << endl;
                break;
            }
        }
    
    }
};

int main()
{
    alarm a;
    a.getTime();
    a.fireAlarm();
    for (int i=0; ; i=i+50) {
        cout << "Beep!" << endl;
    }
    return 0;
}