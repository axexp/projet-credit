#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>


class global
{
public:
    global();
};

struct LoginInfo {
    QString username;
    int id;
};

extern LoginInfo g_loginInfo;


#endif // GLOBAL_H
