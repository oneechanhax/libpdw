
#include <cassert>
#include <functional>
#include <vector>
#include <string_view>
#include <glez/font.hpp>
#include "glez/color.hpp"
#include "input.hpp"

#pragma once

namespace ui {

template<typename T>
class Var;

using Enum = std::vector<std::string_view>;
using TreeMap = std::vector<std::string_view>;
using CommandArgs = std::vector<std::string_view>;

class BaseVar {
public:
    enum class Type {
        kBool,
        kInt,
        kFloat,
        kKey,
        kEnum,
        kString,
        kColor,
        kFont
    };
public:
    BaseVar(Type, TreeMap, std::string_view _gui_name);

    const Type type;
    const TreeMap gui_map;
    const std::string command_name;
    const std::string_view gui_name;

    virtual void Call(std::ostream&, CommandArgs) = 0;
    virtual std::string GetString() = 0;  // Used by cfg mgr and gui
    virtual void SetString(std::string_view) = 0;
    virtual void SetDefault() = 0;
private:
    static inline std::vector<BaseVar*> list;
public:
    static inline const auto& GetList() { return list; }
};

template<typename T>
class Var;

template<>
class Var<bool>: public BaseVar {
public:
    Var(TreeMap, std::string_view, bool _defaults);

    std::string GetString() final;
    void SetString(std::string_view) final;
    void Call(std::ostream&, CommandArgs) final;
    void SetDefault() final;

    operator bool() const { return this->value; }
    bool operator==(bool v) const { return this->value == v; }
    Var<bool>& operator=(bool v);
private:
    bool value;
public:
    const bool defaults;
    std::function<void(bool)> Callback;
};

template<>
class Var<int> : public BaseVar {
public:
    Var<int>(TreeMap, std::string_view, int _defaults, int min, int max);
    Var<int>(TreeMap, std::string_view, int _defaults, int max = 100);

    std::string GetString() override;
    void SetString(std::string_view) override;
    void Call(std::ostream&, CommandArgs) override;
    void SetDefault() final;

    operator int() const { return this->value; }
    bool operator==(int v) const { return this->value == v; }
    Var<int>& operator=(int v);
protected:
    int value;
public:
    const int defaults, min, max;
    std::function<void(int)> Callback;
};
template<>
class Var<float> : public BaseVar {
public:
    Var(TreeMap, std::string_view, float _defaults);
    Var(TreeMap, std::string_view, float _defaults, float max);
    Var(TreeMap, std::string_view, float _defaults, float min, float max);
    std::string GetString() final;
    void SetString(std::string_view) final;
    void Call(std::ostream&, CommandArgs) final;
    void SetDefault() final;

    operator float() const { return this->value; }
    bool operator==(float v) const { return this->value == v; }
    Var<float>& operator=(float v);
private:
    float value;
public:
    const float defaults, min, max;
    std::function<void(float)> Callback;
};

template<>
class Var<Enum> : public Var<int> {
public:
    Var(TreeMap, std::string_view name, int _defaults, Enum _enum);
    std::string GetString() final;
    void SetString(std::string_view) final;
    void Call(std::ostream&, CommandArgs) final;

    operator int() const { return this->value; }
    bool operator==(int v) const { return this->value == v; }
    using Var<int>::operator=;
public:
    const std::vector<std::string_view> internal_enum;
};

template<>
class Var<std::string> :  public BaseVar {
public:
  Var(TreeMap, std::string_view, std::string_view _defaults);
  Var(TreeMap, std::string_view, std::string_view _defaults, float max);
  Var(TreeMap, std::string_view, std::string_view _defaults, float min, float max);
  std::string GetString() final;
  void SetString(std::string_view) final;
  void Call(std::ostream&, CommandArgs) final;
  void SetDefault() final;

  operator std::string_view() const { return this->value; }
  operator const std::string&() const { return this->value; }
  operator std::string() const { return this->value; }
  bool operator==(std::string_view v) const { return std::string_view(this->value) == v; }
  bool operator==(const std::string& v) const { return this->value == v; }
  Var<std::string>& operator=(std::string_view v) { return *this = std::string(v); }
  Var<std::string>& operator=(std::string v);
private:
    std::string value;
public:
    const std::string_view defaults;
    const int min, max;
    std::function<void(std::string_view)> Callback;
};

template<>
class Var<CatKey> :  public BaseVar {
public:
  Var(TreeMap, std::string_view, CatKey _defaults);
  std::string GetString() final;
  void SetString(std::string_view) final;
  void Call(std::ostream&, CommandArgs) final;
  void SetDefault() final;

  operator bool() const;
  operator CatKey() const { return this->value; }
  bool operator==(CatKey v) const { return this->value == v; }
  Var<CatKey>& operator=(CatKey v);
private:
    CatKey value;
public:
    const CatKey defaults;
    std::function<void(CatKey)> Callback;
};

}
