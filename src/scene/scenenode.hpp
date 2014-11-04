#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_CXX11
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/mesh.hpp"

namespace mugg {
    namespace scene {
        class SceneManager;

        class SceneNode {
            private:
                glm::vec4 position;
                glm::vec3 rotation;
                glm::vec3 scale;

                mugg::scene::SceneManager* parent;
                std::vector<mugg::graphics::Mesh*> meshes;
                glm::mat4 translationMatrix, rotationMatrix, scaleMatrix;
            public:
                SceneNode(mugg::scene::SceneManager*);
                ~SceneNode();

                virtual void AddMesh(mugg::graphics::Mesh*&);
                virtual bool GetMeshByIndex(int, mugg::graphics::Mesh*&);
                virtual int GetNumberOfMeshes();
                
                virtual glm::mat4 GetModelMatrix();

                virtual void SetPosition(const glm::vec4&);
                virtual glm::vec4 GetPosition();

                virtual void SetRotation(const glm::vec3&);
                virtual glm::vec3 GetRotation();

                virtual void SetScale(const glm::vec3&);
                virtual glm::vec3 GetScale();
        };
    }
}

#endif
