#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;
#define TASK_2

#ifdef TASK_1
const double pi = 3.1415926535;

class circle {
private:
    double radius;
    double ference;
    double area;

public:
    circle(double rad) {
        radius = rad;
        set_ference();
        set_area();
    }

    void set_radius(double rad) {
        radius = rad;
        set_ference();
        set_area();
    }

    void set_ference() {
        ference = 2 * pi * radius;
    }

    void set_area() {
        area = pi * pow(radius, 2);
    }

    double get_radius() {
        return radius;
    }

    double get_ference() {
        return ference;
    }

    double get_area() {
        return area;
    }
};

int main() {
    const double earthRadius = 6378.1;
    circle earth(earthRadius);
    double newFerence = earth.get_ference() + 0.001;
    double newRadius = newFerence / (2 * pi);
    double gap = newRadius - earthRadius;
    cout << "The answer to the 'Earth and Rope' problem: " << gap << " km" << endl;
    circle pool(3);
    circle poolWithPath(4);
    double pathArea = poolWithPath.get_area() - pool.get_area();
    double pathCost = pathArea * 1000;
    double fenceCost = poolWithPath.get_ference() * 2000;
    double totalCost = pathCost + fenceCost;
    cout << "The answer to the 'Pool' problem: the cost of the path is " << pathCost << ", the cost of the fence is " << fenceCost << "\nThe total cost is " << totalCost << " rubles" << endl;
    return 0;
}
#endif

#ifdef TASK_2
class DateTime {
private:
    struct tm date;

public:
    DateTime(int day, int month, int year) {
        date.tm_mday = day;
        date.tm_mon = month - 1;
        date.tm_year = year - 1900;
    }
    DateTime(const string &dateStr) {
        istringstream sdate(dateStr);
        sdate.imbue(locale("C"));
        sdate >> get_time(&date, "%d %B %Y, %A");
        if (sdate.fail()) {
            cerr << "The date was entered incorrectly" << endl;
        }
    }
    DateTime() {
        time_t today = time(NULL);
        date = *localtime(&today);
    }
    DateTime(const DateTime &other) {
        date = other.date;
    }
    string get_today() const {
        return formatDate(date);
    }
    string get_yesterday() const {
        return formatDate(shiftDate(date, -1));
    }
    string get_tomorrow() const {
        return formatDate(shiftDate(date, 1));
    }
    string get_future(unsigned int N) const {
        return formatDate(shiftDate(date, N));
    }
    string get_past(unsigned int N) const {
        return formatDate(shiftDate(date, -static_cast<int>(N)));
    }
    int get_difference(const DateTime& other) const {
        time_t t1 = mktime(const_cast<tm*>(&date));
        time_t t2 = mktime(const_cast<tm*>(&(other.date)));
        int diff = difftime(t2, t1) / (24 * 60 * 60);
        return diff;
    }
private:
    string formatDate(const tm& dt) const {
        ostringstream fdate;
        fdate << put_time(&dt, "%d %B %Y, %A");
        return fdate.str();
    }
    tm shiftDate(const tm& dt, int days) const {
        time_t time = mktime(const_cast<tm*>(&dt)) + days * 24 * 60 * 60;
        return *localtime(&time);
    }
};

int main() {
    DateTime forToday;
    cout << "Today: " << forToday.get_today() << endl;
    cout << "Yesterday: " << forToday.get_yesterday() << endl;
    cout << "Tomorrow: " << forToday.get_tomorrow() << endl;
    cout << "52 days ago: " << forToday.get_past(52) << endl;
    cout << "After 228 days: " << forToday.get_future(228) << endl;
    DateTime newDate(13, 2, 2024);
    cout << "The difference between today and February 13, 2024: " << forToday.get_difference(newDate) << endl;
}
#endif