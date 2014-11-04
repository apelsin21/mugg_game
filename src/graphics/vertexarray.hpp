#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <iostream>

#include <GL/glew.h>

#include "graphics/globject.hpp"

namespace mugg {
    namespace graphics {
        class VertexArray : public GLObject {
            private:
            public:
                VertexArray();
                ~VertexArray();
        };
    }
}

#endif
