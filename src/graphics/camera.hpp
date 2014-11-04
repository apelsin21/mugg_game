#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "graphics/graphicsdefs.hpp"

namespace mugg {
    namespace graphics {
        class Camera {
            private:
                glm::mat4 modelMatrix, viewMatrix, projectionMatrix;
                glm::vec3 position, scale, rotation;
            
                //Defined in radians
                double fov;
            public:
                Camera();
                ~Camera();

                virtual void SetModelMatrix(const glm::mat4&);
                virtual glm::mat4 GetModelMatrix();

                virtual void SetViewMatrix(const glm::mat4&);
                virtual glm::mat4 GetViewMatrix();
                
                virtual void SetProjectionMatrix(const glm::mat4&);
                virtual glm::mat4 GetProjectionMatrix();
        
                virtual void SetProjectionType(ProjectionType);
                virtual ProjectionType GetProjectionType();

                //Only has effect for a perspective projection
                virtual void SetFOV(double);
                virtual double GetFOV();
        };
    }
}

#endif
