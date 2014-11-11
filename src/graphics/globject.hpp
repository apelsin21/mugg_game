#ifndef GLOBJECT_HPP
#define GLOBJECT_HPP

#include <GL/glew.h>

namespace mugg {
    
    namespace graphics {
        class GLObject {
            protected:
                GLuint ID;
                unsigned int index;
                bool hasGeneratedID;
            public:
                GLObject() {
                    this->hasGeneratedID = false;
                    this->ID = -1;
                    this->index = 0;
                }
                
                void SetID(GLuint newID) {
                    this->ID = newID;   
                }
                GLuint GetID() {
                    return this->ID;
                }

                bool HasGeneratedID() {
                    return this->hasGeneratedID;
                }

                void SetIndex(unsigned int index) {
                    this->index = index;
                }
                unsigned int GetIndex() {
                    return this->index;
                }
        };
    }
}

#endif
