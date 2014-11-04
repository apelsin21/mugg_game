#ifndef GLOBJECT_HPP
#define GLOBJECT_HPP

#include <GL/glew.h>

namespace mugg {
    namespace core {
        class ContentManager;
    }
    
    namespace graphics {
        class GLObject {
            protected:
                GLuint ID = -1;
                unsigned int index = 0;
                mugg::core::ContentManager* parent;
                bool hasGeneratedID;
            public:
                GLObject(mugg::core::ContentManager* parent) {
                    this->parent = parent;
                    this->hasGeneratedID = false;
                }
                
                virtual mugg::core::ContentManager* GetParent() {
                    return this->parent;
                }

                virtual void SetID(GLuint newID) {
                    this->ID = newID;   
                }
                virtual GLuint GetID() {
                    return this->ID;
                }

                virtual bool HasGeneratedID() {
                    return this->hasGeneratedID;
                }

                virtual void SetIndex(unsigned int index) {
                    this->index = index;
                }
                virtual unsigned int GetIndex() {
                    return this->index;
                }
        };
    }
}

#endif
