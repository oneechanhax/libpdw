
#pragma once

#include <string>
#include <unordered_map>
#include <glez/color.hpp>

// TMP SHIT TILL I CAN GET RID OF IT EWWWWWWWW

class KeyValues {
public:
    KeyValues (const std::string&) {}
    std::unordered_map<std::string, bool> stored_bools;
    std::unordered_map<std::string, int> stored_ints;
    std::unordered_map<std::string, float> stored_floats;
    std::unordered_map<std::string, std::string> stored_strings;
    std::unordered_map<std::string, glez::rgba> stored_colors;
    bool GetBool(const std::string& s) { return this->stored_bools.at(s); }
    void SetBool(const std::string& s, int v) { this->stored_bools[s] = v; }
    int GetInt(const std::string& s) { return this->stored_ints.at(s); }
    void SetInt(const std::string& s, int v) { this->stored_ints[s] = v; }
    float GetFloat(const std::string& s) { return this->stored_floats.at(s); }
    void SetFloat(const std::string& s, float v) { this->stored_floats[s] = v; }
    std::string GetString(const std::string& s) { return this->stored_strings.at(s); }
    void SetString(const std::string& s, const std::string& v) { this->stored_strings[s] = v; }
    glez::rgba GetColor(const std::string& s) { return this->stored_colors.at(s); }
    void SetColor(const std::string& s, glez::rgba v) { this->stored_colors[s] = v; }
    bool FindKey(const std::string& s) {
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
    bool IsEmpty(const std::string& s) {
        return !this->FindKey(s);
    }
};
