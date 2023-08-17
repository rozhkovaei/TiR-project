#pragma once

#include <iostream>

#define SQLITE 1

#ifdef SQLITE
    static const std::string DB_NAME = "TiRDoc.sqlite";
#endif

struct ClientData
{
    int mId = 0;
    std::string mFirstName;
    std::string mPatronymic;
    std::string mLastName;
    std::string mPassport;
    std::string mPhone;
};

struct WeaponData
{
    int mId = 0;
    std::string mType;
    std::string mCaliber;
    std::string mMark;
    std::string mIssueYear;
};

struct BulletData
{
    int mId = 0;
    std::string mType;
    std::string mCaliber;
    std::string mSerialNumber;
    std::string mIssueYear;
};

enum class ControllerEvent
{
    BUTTON_CLIENTS_PRESSED = 0,
    BUTTON_ADD_PRESSED = 1,
    BUTTON_DELETE_PRESSED = 2
};