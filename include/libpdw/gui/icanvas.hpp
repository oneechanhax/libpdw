
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

#include <chrono>
#include <glez/color.hpp>
#include <glez/font.hpp>
#include <glez/texture.hpp>

#include "gui/tooltip.hpp"
#include "gui/widgets/basewindow.hpp"

class CanvasLayer {
public:
    using TranslationMatrix = std::pair<std::pair<int, int>, std::pair<int, int>>; // src, dest
public:
    enum class RectType { Filled,
        Outline };
    virtual void Line(TranslationMatrix, glez::rgba color) = 0;
    virtual void Rect(TranslationMatrix, glez::rgba color, RectType = RectType::Filled) = 0;
    virtual void Rect(TranslationMatrix, glez::rgba color, glez::texture&) = 0;
    virtual void Circle(std::pair<int, int> center, float radius, glez::rgba color, int steps = 16) = 0;
    virtual std::pair<int, int> String(std::pair<int, int> src, const std::string& str, glez::rgba color, std::optional<glez::rgba> outline = glez::color::black) = 0;
    virtual std::pair<int, int> StringSize(const std::string& str) = 0;
    virtual glez::rgba GetColor() const = 0;
};

class ICanvas : public CanvasLayer {
public:
    // The plan is to "traverse" the canvas tree. Super easy way to manage themes maybe. We'll see!
    virtual const ICanvas& GetBackground() const = 0;
    virtual const ICanvas& GetForeground() const = 0;
};

inline std::pair<int, int> operator+(std::pair<int, int> v1, std::pair<int, int> v2) {
    return { v1.first + v2.first, v1.second + v2.second };
}

class CanvasOffset : public ICanvas {
    ICanvas* parent;
    std::pair<int, int> offset;
    TranslationMatrix Offset(TranslationMatrix tm) {
        return { this->offset + tm.first, tm.second };
    }

public:
    CanvasOffset(ICanvas* parent, std::pair<int, int> offset)
        : parent(parent)
        , offset(offset) { }
    virtual void Line(TranslationMatrix tm, glez::rgba color) override {
        this->parent->Line(this->Offset(tm), color);
    }
    virtual void Rect(TranslationMatrix tm, glez::rgba color, RectType rt = RectType::Filled) override {
        this->parent->Rect(this->Offset(tm), color, rt);
    }
    virtual void Rect(TranslationMatrix tm, glez::rgba color, glez::texture& tx) override {
        this->parent->Rect(this->Offset(tm), color, tx);
    }
    virtual void Circle(std::pair<int, int> center, float radius, glez::rgba color, int steps = 16) override {
        this->parent->Circle(this->offset + center, radius, color, steps);
    }
    virtual std::pair<int, int> String(std::pair<int, int> src, const std::string& str, glez::rgba color, std::optional<glez::rgba> outline = glez::color::black) override {
        return this->parent->String(this->offset + src, str, color, outline);
    }
    virtual std::pair<int, int> StringSize(const std::string& str) override {
        return this->parent->StringSize(str);
    }
    virtual glez::rgba GetColor() const override { return this->parent->GetColor(); }
    virtual const ICanvas& GetBackground() const override { return this->parent->GetBackground(); }
    virtual const ICanvas& GetForeground() const override { return this->parent->GetForeground(); }

public:
    decltype(offset) GetOffset() const { return offset; }
};
