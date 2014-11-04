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

                virtual mugg::gui::GUIManager* GetParent();

                virtual void SetScale(const glm::vec2&);
                virtual glm::vec2 GetScale();

                virtual void SetRotation(const float);
                virtual float GetRotation();

                virtual void SetPosition(const glm::vec2&);
                virtual glm::vec2 GetPosition();

                virtual void SetTexture(mugg::graphics::Texture2D*);
                virtual mugg::graphics::Texture2D* GetTexture();
                
                virtual void SetModelMatrix(const glm::mat4&);
                virtual glm::mat4 GetModelMatrix();

                virtual unsigned int GetIndex();
                virtual void SetIndex(unsigned int);

                virtual bool HasChanged();
        };
    }
}

#endif
