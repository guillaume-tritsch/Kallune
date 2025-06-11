#pragma once

class Renderable {
public:
    virtual void draw() = 0;
    virtual ~Renderable() = default;
};