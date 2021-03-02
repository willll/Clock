#pragma once

template <typename T>
struct IData {

    virtual void setState(const T & state) = 0;

    virtual T getState() const = 0;

};