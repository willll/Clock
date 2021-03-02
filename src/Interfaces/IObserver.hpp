#pragma once

#include "Interfaces/IData.hpp"

template <typename T>
struct IObserver {

    explicit IObserver()
    { }

    virtual void update(const IData<T> * _data) = 0;
};
