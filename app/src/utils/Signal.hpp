#pragma once
#include <vector>

template<typename C, typename T>
class Signal
{

public:

    void fire(T data);
    void addCallback(C* context, void (C::*fptr)(T data));

private:

    struct callback {
        callback(C* context, void (C::*fptr)(T data))
            : mContext(context)
            , mFptr(fptr)
        {}
        C* mContext;
        void (C::*mFptr)(T data);
    };

    std::vector<callback> callbacks {};
};

template <typename C, typename T>
void Signal<C, T>::fire(T data)
{
    for (auto callback : callbacks) {
        (*(callback.mContext).*(callback.mFptr))(data);
    }
}

template <typename C, typename T>
void Signal<C, T>::addCallback(C* context, void (C::*fptr)(T data))
{
    callbacks.push_back(callback(context, fptr));
}
