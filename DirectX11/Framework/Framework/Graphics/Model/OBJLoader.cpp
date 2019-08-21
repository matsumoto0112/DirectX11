#include "OBJLoader.h"
#include <fstream>
#include <unordered_map>
#include "Graphics/GraphicsDeviceManager.h"
#include "Graphics/Texture/TextureLoader.h"
#include "Define/Path.h"
namespace Framework {
namespace Graphics {

OBJLoader::OBJLoader(GraphicsDeviceManager& graphicsDevice)
    :mGraphicsDevice(graphicsDevice) {}

OBJLoader::~OBJLoader() {}

std::unique_ptr<Model> OBJLoader::load(const std::string& filepath) {
    std::string path = Define::Path::getInstance().objModel() + filepath;
    std::vector<std::unique_ptr<Mesh>> mesh = loadMeshes(path);
    std::string matPath = path;
    int pos = matPath.rfind('.');
    matPath = matPath.substr(0, pos);
    std::vector<std::unique_ptr<Material>> mat = loadMaterials(matPath);
    return std::make_unique<Model>(mGraphicsDevice, std::move(mesh), std::move(mat));
}

std::vector<std::unique_ptr<Mesh>> OBJLoader::loadMeshes(const std::string & name) {
    std::vector<Math::Vector4> positions;
    std::vector<Math::Vector3> normals;
    std::vector<Math::Vector2> uvs;
    std::ifstream ifs(name, std::ios::in);
    std::string buf;
    int currentIndex = -1;

    if (!ifs.is_open()) {
        throw "";
    }

    //vertices[i]:i番目のマテリアルの頂点
    std::vector<std::vector<TextureVertex3D>> vertices;
    std::vector<std::vector<WORD>> indices;
    std::unordered_map<std::string, int> matNames;
    while (true) {
        //行頭の文字を読み込み、その文字によって分岐
        ifs >> buf;

        //もう読み終わっていたら終了
        if (!ifs)break;
        //#はコメント
        if (buf == "#") {

        }
        //頂点座標
        else if (buf == "v") {
            Math::Vector4 pos;
            ifs >> pos.x >> pos.y >> pos.z;
            pos.w = 1.0f;
            positions.emplace_back(pos);
        }
        //UV座標
        else if (buf == "vt") {
            Math::Vector2 uv;
            ifs >> uv.x >> uv.y;
            uvs.emplace_back(uv);
        }
        //法線
        else if (buf == "vn") {
            Math::Vector3 nor;
            ifs >> nor.x >> nor.y >> nor.z;
            normals.emplace_back(nor);
        }
        //面情報
        else if (buf == "f") {
            int iPosition;
            int iUV;
            int iNormal;

            //三角形の情報のみ読み込む
            for (int face = 0; face < 3; face++) {
                TextureVertex3D vertex;
                //頂点座標インデックスを読み取る
                ifs >> iPosition;
                //1-indexから0-indexに変換
                iPosition--;
                vertex.pos = positions[iPosition];

                //次に"/"で区切られているかチェック
                if (ifs.peek() == '/') {
                    //その"/"を無視する
                    ifs.ignore();

                    //次に/が来なければテクスチャのインデックスが入ってくる
                    if (ifs.peek() != '/') {
                        ifs >> iUV;
                        iUV--;
                        vertex.uv = uvs[iUV];
                    }
                    //次に/が来ていれば法線のインデックスが入ってくる
                    if (ifs.peek() == '/') {
                        ifs.ignore();
                        ifs >> iNormal;
                        iNormal--;
                        vertex.normal = normals[iNormal];
                    }
                }
                vertices[currentIndex].emplace_back(vertex);
                indices[currentIndex].emplace_back((int)vertices[currentIndex].size() - 1);
            }
        }
        else if (buf == "usemtl") {
            ifs >> buf;
            if (matNames.find(buf) != matNames.end()) {
                currentIndex = matNames[buf];
            }
            else {
                currentIndex++;
                matNames.emplace(buf, currentIndex);
                vertices.emplace_back(std::vector<TextureVertex3D>());
                indices.emplace_back(std::vector<WORD>());
            }
        }
        //それ以外の時
        else {

        }
    }

    ifs.close();

    const int size = matNames.size();

    std::vector<std::unique_ptr<Mesh>> mMeshes(size);
    for (int i = 0; i < size; i++) {
        mMeshes[i] = std::make_unique<Mesh>();
        mMeshes[i]->mVIBuffer =
            std::make_unique<VertexAndIndexBuffer>(mGraphicsDevice, vertices[i], indices[i],
                Graphics::PrimitiveTopology::TriangleList);
        mMeshes[i]->mVShader =
            std::make_unique<VertexShader>(mGraphicsDevice, "Texture3DVS");
        mMeshes[i]->mPShader =
            std::make_unique<PixelShader>(mGraphicsDevice, "Cone1PS");
        mMeshes[i]->matIndex = i;
    }
    return mMeshes;
}

std::vector<std::unique_ptr<Material>> OBJLoader::loadMaterials(const std::string& name) {
    std::vector<std::unique_ptr<Material>> mMaterials;
    std::ifstream ifs = std::ifstream(name + ".mtl", std::ios::in);
    std::string buf;
    int pos = name.rfind('/');
    if (pos == -1) {
        pos = name.rfind('\\');
    }
    std::string texPath = name.substr(0, pos);
    int matCount = -1;
    while (true) {
        ifs >> buf;
        if (!ifs)break;

        //新しいマテリアル情報
        if (buf == "newmtl") {
            matCount++;
            mMaterials.emplace_back(std::make_unique<Material>());
        }
        //Ambient
        else if (buf == "Ka") {
            Color4 c;
            ifs >> c.r >> c.g >> c.b;
            c.a = 1.0f;
            mMaterials[matCount]->ambient = c;
        }
        //Diffuse
        else if (buf == "Kd") {
            Color4 c;
            ifs >> c.r >> c.g >> c.b;
            c.a = 1.0f;
            mMaterials[matCount]->diffuse = c;
        }
        //Specular
        else if (buf == "Ks") {
            Color4 c;
            ifs >> c.r >> c.g >> c.b;
            c.a = 1.0f;
            mMaterials[matCount]->specular = c;
        }
        //Alpha
        else if (buf == "d") {
            ifs >> mMaterials[matCount]->alpha;
        }
        //Shininess;
        else if (buf == "Ns") {
            ifs >> mMaterials[matCount]->shininess;
        }
        else if (buf == "map_Ka") {
            ifs >> buf;
            mMaterials[matCount]->mAmbientMap = loadTexture(getPath(texPath, buf));
        }
        else if (buf == "map_Kd") {
            ifs >> buf;
            mMaterials[matCount]->mDiffuseMap = loadTexture(getPath(texPath, buf));
        }
        else if (buf == "map_Ks") {
            ifs >> buf;
            mMaterials[matCount]->mSpecularMap = loadTexture(getPath(texPath, buf));
        }
        else if (buf == "map_Bump") {
            ifs >> buf;
            mMaterials[matCount]->mBumpMap = loadTexture(getPath(texPath, buf));
        }
    }
    return mMaterials;
}
std::shared_ptr<Texture> OBJLoader::loadTexture(const std::string& name) {
    TextureLoader loader(mGraphicsDevice);
    return loader.load(name);
}

std::string OBJLoader::getPath(std::string modelName, std::string path) {
    int pos = path.rfind('/');
    if (pos == -1) {
        pos = path.rfind('\\');
    }
    pos++;
    return modelName + "/textures/" + path.substr(pos);
}
} //Graphics 
} //Framework 
