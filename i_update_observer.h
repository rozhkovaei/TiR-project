#pragma once

template< class T >
struct IUpdateObserver
{
    virtual ~IUpdateObserver() {}

    virtual void Notify( T&& data ) = 0;
};