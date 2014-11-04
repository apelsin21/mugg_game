#include "scene/scenenode.hpp"

mugg::scene::SceneNode::SceneNode(mugg::scene::SceneManager* parent) {
    this->parent = parent;
}
mugg::scene::SceneNode::~SceneNode() {
}

void mugg::scene::SceneNode::AddMesh(mugg::graphics::Mesh*& mesh) {
    this->meshes.push_back(mesh);
}
bool mugg::scene::SceneNode::GetMeshByIndex(int index, mugg::graphics::Mesh*& out_mesh) {
    if(index < 0 || index > this->meshes.size() || this->meshes.empty()) {
        return false;
    }

    out_mesh = this->meshes[index];
    return true;
}
int mugg::scene::SceneNode::GetNumberOfMeshes() {
    return this->meshes.size();
}

void mugg::scene::SceneNode::SetPosition(const glm::vec4& in_position) {
    this->position = in_position;
    
    this->translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->position.x, this->position.y, this->position.z));
}
glm::vec4 mugg::scene::SceneNode::GetPosition() {
    return this->position;
}

void mugg::scene::SceneNode::SetRotation(const glm::vec3& in_rotation) {
    this->rotation = in_rotation;
    
    this->rotationMatrix = glm::rotate(glm::mat4(1.0f), this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
                           glm::rotate(glm::mat4(1.0f), this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
                           glm::rotate(glm::mat4(1.0f), this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
}
glm::vec3 mugg::scene::SceneNode::GetRotation() {
    return this->rotation;
}

void mugg::scene::SceneNode::SetScale(const glm::vec3& in_scale) {
    this->scale = scale;
    
    this->scaleMatrix = glm::scale(glm::mat4(1.0f), this->scale);
}
glm::vec3 mugg::scene::SceneNode::GetScale() {
    return this->scale;
}

glm::mat4 mugg::scene::SceneNode::GetModelMatrix() {
    return this->translationMatrix * this->rotationMatrix * this->rotationMatrix;
}
