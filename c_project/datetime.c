// https://blog.csdn.net/ybhjx/article/details/69374354?version=2.5.40003.149&platform=win

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

time_t get_timestamp(int year, int month, int day, int hour, int min, int sec) {
    struct tm timeinfo;
    time_t timestamp;

    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = min;
    timeinfo.tm_sec = sec;
    timeinfo.tm_isdst = -1;

    timestamp = mktime(&timeinfo);

    return timestamp;
}

void test_timet();

void test_timestamp_lite();

void test_timestamp_lite0();

void test_timestamp(int timestamp);

void test_print_current_time();

int generate_timestamp(int year, int month, int day) {
    struct tm t;
    memset(&t, 0, sizeof(t));
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    time_t timestamp = mktime(&t);
    return (int) timestamp;
}

void print_date(time_t timestamp) {
    struct tm *timeinfo;
    timeinfo = localtime(&timestamp);
    printf("%d-%02d-%02d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
}

int main() {
    int timestamp = generate_timestamp(2022, 12, 31);
    printf("The timestamp is: %d\n", timestamp);
    test_timestamp(timestamp);
    test_print_current_time();

    // test_timet();
    // test_timestamp();
    test_timestamp_lite0();
    // test_timestamp_lite();
    return 0;
}

void test_print_current_time() {
    time_t current_time;
    time(&current_time);
    print_date(current_time);
}

void test_timestamp(int timestamp) {
    time_t t1 = timestamp;
    srand((unsigned int)t1);

    int random_number = rand() % 100;
    printf("Generated random number: %d\n", random_number);
}

void test_timestamp_lite0() {
    struct tm strtm = {0};
    time_t time_bday;

    strtm.tm_year = 2021 - 1900;
    strtm.tm_mon = 1;
    time_bday = mktime(&strtm);
    printf("%lld\n", time_bday);
    printf("%s\n", ctime(&time_bday)); //Thu Dec 31 00:00:00 2020

}


void test_timestamp_lite() {
    time_t timep = time(NULL);
    printf("%s", ctime(&timep));  // Thu Jan 01 08:01:24 1970
    printf("%lld\n", timep); // 1629249301 和 time(NULL)一样 -- 当前时间

    struct tm *p = gmtime(&timep);
    p->tm_year = 2020 - 1900; // 2020.12.3 15:03:05
    // p->tm_mon = 12;
    // p->tm_mday = 3;
    // p->tm_hour = 15;
    // p->tm_min = 3;
    // p->tm_sec = 5;
    printf("%lld\n", mktime(p)); // 1629249301
}
// struct tm
// {
//     int tm_sec;  /*秒，正常范围0-59， 但允许至61*/
//     int tm_min;  /*分钟，0-59*/
//     int tm_hour; /*小时， 0-23*/
//     int tm_mday; /*日，即一个月中的第几天，1-31*/
//     int tm_mon;  /*月， 从一月算起，0-11*/  1+p->tm_mon;
//     int tm_year;  /*年， 从1900至今已经多少年*/  1900＋ p->tm_year;
//     int tm_wday; /*星期，一周中的第几天， 从星期日算起，0-6*/
//     int tm_yday; /*从今年1月1日到目前的天数，范围0-365*/
//     int tm_isdst; /*日光节约时间的旗标*/
// };


void test_timet() {// time_t 这种类型就是用来存储从1970年到现在经过了多少秒
    // struct timeval
    // {
    //     long tv_sec; /*秒*/
    //     long tv_usec; /*微秒*/
    // };

    time_t timep;

    time(&timep); /*获取time_t类型当前时间*/
    /*转换为常见的字符串：Fri Jan 11 17:04:08 2008*/
    printf("%s", ctime(&timep));
    printf("%lld\n", timep);
    struct tm *p;
    p = gmtime(&timep); /*转换为struct tm结构的UTC时间 +0:00 time_t -> tm */
    printf("%d/%d/%d %d:%d:%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

    p = localtime(&timep); /*转换为本地的tm结构的时间按 +8:00 time_t -> tm */
    printf("time()->localtime() %d\n", p);
    printf("%d/%d/%d %d:%d:%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    timep = mktime(p); /*重新转换为time_t类型的UTC时间，这里有一个时区的转换*/
    //by lizp 错误，没有时区转换， 将struct tm 结构的时间转换为从1970年至p的秒数
    printf("time()->localtime()->mktime(): %d\n", timep);

}
