#pragma once

struct VertexLayout
{
    unsigned int count;
    unsigned int type;
    bool normalized = false;

    VertexLayout(unsigned int count, unsigned int type, bool normalized)
        : count(count), type(type), normalized(normalized) {}

    VertexLayout(unsigned int count, unsigned int type)
        : count(count), type(type), normalized(false) {}
};