
/*
 * Libpdw: Primitives Done Well!
 * Copyright (C) 2022 Rebekah Rowe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

} // namespace cat
