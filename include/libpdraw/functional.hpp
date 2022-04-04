
#pragma once

// an extended std lib

#include <algorithm>
#include <vector>

namespace cat {

// To handle calling of events
template <typename... args>
class Event {
public:
    using FuncPtr = void (*)(args...);

private:
    std::vector<FuncPtr> func_pool;
    bool in_event = false;
    auto find(FuncPtr in) {
        return std::find(this->func_pool.begin(), this->func_pool.end(), in);
    }

public:
    inline bool GetInEvent() { return in_event; }
    inline void Emit(args... a) {
        in_event = true;
        for (const auto& func : this->func_pool)
            func(a...);
        in_event = false;
    }
    void Listen(FuncPtr in) {
        auto find = this->find(in);
        if (find != this->func_pool.end())
            throw "Listener already exists";
        this->func_pool.push_back(in);
    }
    void Remove(FuncPtr in) {
        auto find = this->find(in);
        if (find != this->func_pool.end())
            this->func_pool.erase(find);
        else
            throw "Listener doesnt exist";
    }
};

// Managed listener, adds on construct and removes on destruct
/*template<class Event>
class Listener {
    Listener(Event::FuncPtr _callback) : callback(_callback) {
        Event.Listen(_callback);
    }
    ~Listener() { Event.Remove(callback); }
    const Event::FuncPtr callback;
};*/

}
