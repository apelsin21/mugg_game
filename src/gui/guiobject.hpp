#ifndef GUIOBJECT_HPP
#define GUIOBJECT_HPP

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gui/guimanager.hpp"

namespace mugg {
    namespace graphics {
        class Texture2D;
    }

    namespace gui {
        class GUIObject {
            protected:
                unsigned int index;
                mugg::gui::GUIManager* parent;
                mugg::graphics::Texture2D* texture;
                
                glm::vec2 position, scale;
                float rotation;
                
                glm::mat4 modelMatrix, translationMatrix, rotationMatrix, scaleMatrix;
            
                bool changed;
            public:
                GUIObject(mugg::gui::GUIManager*);

                mugg::gui::GUIManager* GetParent();
                
                void SetScale(const glm::vec2&);
                glm::vec2 GetScale();
                
                void SetRotation(const float);
                float GetRotation();
                
                void SetPosition(const glm::vec2&);
                glm::vec2 GetPosition();
                
                void SetTexture(mugg::graphics::Texture2D*);
                mugg::graphics::Texture2D* GetTexture();
                
                void SetModelMatrix(const glm::mat4&);
                glm::mat4 GetModelMatrix();
                
                unsigned int GetIndex();
                void SetIndex(unsigned int);
                
                bool HasChanged();
        };
    }
}

#endif
