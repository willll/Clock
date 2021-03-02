#pragma once

#include <vector>
#include <algorithm>  

#include "Interfaces/IData.hpp"

// forward declarations
// template <typename T>
// struct IObserver {
//     virtual void update(const IData<T> *);
// };

template <typename T> struct IObserver;


template <typename T>
class ISubject : public IData<T>{

    std::vector<IObserver<T> *> observers;

public :

    explicit ISubject() { }

    void attach(IObserver<T> * _observer) {
        observers.emplace_back(_observer);
    }

    void notify() {
        for_each(observers.begin(), observers.end(),[this](IObserver<T> * o)
        {
            o->update(this);
        });
    }
};
