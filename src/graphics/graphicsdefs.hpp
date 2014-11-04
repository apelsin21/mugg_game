#ifndef GRAPHICSDEFS_HPP
#define GRAPHICSDEFS_HPP

#include <GL/glew.h>


namespace mugg {
    namespace graphics {
        
        #define GLSL(src) "#version 130\n" #src
        
        enum TextureFilter {            
            Nearest,
            Linear,
        };
        static const char* TextureFilterString[] = {
            "Nearest",
            "Linear",
            NULL
        };
        static GLenum TextureFilterToGLEnum(TextureFilter filter) {
            switch(filter) {
                case Nearest:
                    return GL_NEAREST;
                case Linear:
                    return GL_LINEAR;
                default:
                    return 0;
            }
        }

        enum TextureWrap {
            Repeat,
            MirroredRepeat,
            ClampToEdge,
            ClampToBorder,
        };
        static const char* TextureWrapString[] = {
            "Repeat",
            "MirroredRepeat",
            "ClampToEdge",
            "ClampToBorder",
            NULL
        };
        static GLenum TextureWrapToGLEnum(TextureWrap wrap) {
            switch(wrap) {
                case Repeat:
                    return GL_REPEAT;
                case MirroredRepeat:
                    return GL_MIRRORED_REPEAT;
                case ClampToEdge:
                    return GL_CLAMP_TO_EDGE;
                case ClampToBorder:
                    return GL_CLAMP_TO_BORDER;
                default:
                    return 0;
            }
        }

        enum ProjectionType {
            Orthographic,
            Perspective
        };
        static const char* ProjectionTypeString[] = {
            "Orthographic",
            "Perspective",
            NULL
        };

        enum ShaderType {
            VertexShader,
            FragmentShader,
            GeometryShader,
        };
        static const char* ShaderTypeString[] = {
            "VertexShader",
            "FragmentShader",
            "GeometryShader",
            NULL
        };
        static GLenum ShaderTypeToGLEnum(ShaderType type) {
            switch(type) {
                case VertexShader:
                    return GL_VERTEX_SHADER;
                case FragmentShader:
                    return GL_FRAGMENT_SHADER;
                case GeometryShader:
                    return GL_GEOMETRY_SHADER;
                default:
                    return 0;
            }
        }
    }
}

#endif
