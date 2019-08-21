#pragma once

#include "Graphics/Model/Model.h"
namespace Framework {
namespace Graphics {

class OBJLoader {
public:
    OBJLoader(GraphicsDeviceManager& graphicsDevice);
    ~OBJLoader();
    std::unique_ptr<Model> load(const std::string& filepath);
private:
    std::vector<std::unique_ptr<Mesh>> loadMeshes(const std::string& name);
    std::vector<std::unique_ptr<Material>> loadMaterials(const std::string& name);
    std::shared_ptr<Texture> loadTexture(const std::string& name);
    std::string getPath(std::string modelName, std::string path);

    GraphicsDeviceManager& mRenderingManager;
};

} //Graphics 
} //Framework 
