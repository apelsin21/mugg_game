#ifndef IMAGE_HPP
#define IMAGE_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "gui/guiobject.hpp"
#include "graphics/texture2d.hpp"

namespace mugg {
    namespace gui {
        class GUIManager;
        
        class Sprite : public GUIObject {
            private:
                bool positionChanged, uvChanged, colorChanged;
                
                std::vector<float> positions;
                std::vector<float> uvs;
                std::vector<float> colors;
            public:
                Sprite(mugg::gui::GUIManager*);
                ~Sprite();
       
                std::vector<float> GetPositions();
                void SetPositions(const std::vector<float>&);
                
                std::vector<float> GetUVs();
                void SetUVs(const std::vector<float>&);
                
                std::vector<float> GetColors();
                void SetColors(const std::vector<float>&);

                virtual bool IsPositionChanged();
                virtual bool IsUVChanged();
                virtual bool IsColorChanged();
        };
    }
}

#endif
