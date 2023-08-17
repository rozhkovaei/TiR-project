#pragma once

#include <iostream>

struct IErrorObserver
{
    virtual ~IErrorObserver() {}

    virtual void Notify( const std::string& message ) = 0;
};