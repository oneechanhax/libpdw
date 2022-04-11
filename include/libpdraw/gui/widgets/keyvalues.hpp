
/*
 * Libpdraw: A Versitile GUI for use with a primitive drawing system!
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

#include <glez/color.hpp>
#include <string>
#include <unordered_map>

// TMP SHIT TILL I CAN GET RID OF IT EWWWWWWWW

class KeyValues {
public:
    KeyValues(const std::string&) { }
    std::unordered_map<std::string, bool> stored_bools;
    std::unordered_map<std::string, int> stored_ints;
    std::unordered_map<std::string, float> stored_floats;
    std::unordered_map<std::string, std::string> stored_strings;
    std::unordered_map<std::string, glez::rgba> stored_colors;
    [[deprecated]] bool GetBool(const std::string& s) { return this->stored_bools.at(s); }
    [[deprecated]] void SetBool(const std::string& s, int v) { this->stored_bools[s] = v; }
    [[deprecated]] int GetInt(const std::string& s) { return this->stored_ints.at(s); }
    [[deprecated]] void SetInt(const std::string& s, int v) { this->stored_ints[s] = v; }
    [[deprecated]] float GetFloat(const std::string& s) { return this->stored_floats.at(s); }
    [[deprecated]] void SetFloat(const std::string& s, float v) { this->stored_floats[s] = v; }
    [[deprecated]] std::string GetString(const std::string& s) { return this->stored_strings.at(s); }
    [[deprecated]] void SetString(const std::string& s, const std::string& v) { this->stored_strings[s] = v; }
    [[deprecated]] glez::rgba GetColor(const std::string& s) { return this->stored_colors.at(s); }
    [[deprecated]] void SetColor(const std::string& s, glez::rgba v) { this->stored_colors[s] = v; }
    [[deprecated]] bool FindKey(const std::string& s) {
        {
            auto find = stored_bools.find(s);
            if (find != stored_bools.end())
                return true;
        }
        {
            auto find = stored_ints.find(s);
            if (find != stored_ints.end())
                return true;
        }
        {
            auto find = stored_floats.find(s);
            if (find != stored_floats.end())
                return true;
        }
        {
            auto find = stored_strings.find(s);
            if (find != stored_strings.end())
                return true;
        }
        {
            auto find = stored_colors.find(s);
            if (find != stored_colors.end())
                return true;
        }
        return false;
    }
    [[deprecated]] bool IsEmpty(const std::string& s) {
        return ![this](const std::string& s) {
            {
                auto find = stored_bools.find(s);
                if (find != stored_bools.end())
                    return true;
            }
            {
                auto find = stored_ints.find(s);
                if (find != stored_ints.end())
                    return true;
            }
            {
                auto find = stored_floats.find(s);
                if (find != stored_floats.end())
                    return true;
            }
            {
                auto find = stored_strings.find(s);
                if (find != stored_strings.end())
                    return true;
            }
            {
                auto find = stored_colors.find(s);
                if (find != stored_colors.end())
                    return true;
            }
            return false;
        }(s);
    }
};
