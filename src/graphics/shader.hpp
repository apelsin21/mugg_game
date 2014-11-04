#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <memory>

#include "core/fileutils.hpp"

#include "graphics/graphicsdefs.hpp"
#include "graphics/globject.hpp"

namespace mugg {
    namespace core {
        class ContentManager;
    }

    namespace graphics {
        class Shader : public GLObject {
            private:
                mugg::graphics::ShaderType type;
                std::string filepath;
                std::string data;
                bool loaded, compiledSuccessfully;
                
                void CheckForErrors();
                const char* GetLog();
                bool Validate();

                mugg::core::ContentManager* creator;
            public:
                Shader(mugg::graphics::ShaderType, bool);
                Shader(mugg::core::ContentManager*);
                ~Shader();

                void CreateID();
                void DeleteID();

                bool Load(const std::string&);

                mugg::graphics::ShaderType GetType();
                void SetType(mugg::graphics::ShaderType);

                std::string GetData();
                void SetData(const std::string& data);

                std::string GetFilepath();
                void SetFilepath(std::string filepath);

                bool GetLoaded();
                bool GetCompiledSuccessfully();

                bool Compile();
        };
    }
}

#endif
