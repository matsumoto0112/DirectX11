#include "Model.h"
#include <fstream>
#include <string>
#include "Framework/Define/Path.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

namespace Framework {
namespace Graphics {

Model::Model(std::vector<std::unique_ptr<Mesh>> meshes,
    std::vector<std::unique_ptr<Material>> materials)
    :mMeshes(std::move(meshes)), mMaterials(std::move(materials)) { }

Model::~Model() {
    mMeshes.clear();
    mMaterials.clear();
}

void Model::draw(const Utility::Transform& transform) {
    ConstantBufferManager* cbManager = Utility::getConstantBufferManager();
    //���W�ϊ��s��̐ݒ�
    cbManager->setMatrix(Graphics::ConstantBufferParameterType::World, transform.createSRTMatrix());
    //���b�V�������ׂĕ`��
    for (auto&& mesh : mMeshes) {
        mesh->mVShader->set();
        mesh->mPShader->set();
        //�}�e���A�����̃Z�b�g
        cbManager->setColor(ConstantBufferParameterType::Ambient, mMaterials[mesh->matIndex]->ambient);
        cbManager->setColor(ConstantBufferParameterType::Diffuse, mMaterials[mesh->matIndex]->diffuse);
        cbManager->setColor(ConstantBufferParameterType::Specular, mMaterials[mesh->matIndex]->specular);
        cbManager->setFloat(ConstantBufferParameterType::Shininess, mMaterials[mesh->matIndex]->shininess);
        cbManager->setFloat(ConstantBufferParameterType::Alpha, mMaterials[mesh->matIndex]->alpha);

        //���ꂼ��̃e�N�X�`�������݂���΃Z�b�g����
        if (mMaterials[mesh->matIndex]->mAmbientMap != nullptr) {
            mMaterials[mesh->matIndex]->mAmbientMap->setData(ShaderInputType::Pixel, 1);
        }
        if (mMaterials[mesh->matIndex]->mDiffuseMap != nullptr) {
            mMaterials[mesh->matIndex]->mDiffuseMap->setData(ShaderInputType::Pixel, 2);
        }
        if (mMaterials[mesh->matIndex]->mSpecularMap != nullptr) {
            mMaterials[mesh->matIndex]->mSpecularMap->setData(ShaderInputType::Pixel, 3);
        }
        if (mMaterials[mesh->matIndex]->mBumpMap != nullptr) {
            mMaterials[mesh->matIndex]->mBumpMap->setData(ShaderInputType::Pixel, 4);
        }

        Utility::getConstantBufferManager()->send();
        mesh->mVIBuffer->render();
    }
}

std::vector<std::shared_ptr<VertexShader>> Model::getVertexShader() const {
    std::vector<std::shared_ptr<VertexShader>> res(mMeshes.size());
    const int size = mMeshes.size();
    for (int i = 0; i < size; i++) {
        res[i] = mMeshes[i]->mVShader;
    }
    return res;
}

std::vector<std::shared_ptr<PixelShader>> Model::getPixelShader() const {
    std::vector<std::shared_ptr<PixelShader>> res(mMeshes.size());
    const int size = mMeshes.size();
    for (int i = 0; i < size; i++) {
        res[i] = mMeshes[i]->mPShader;
    }
    return res;
}

void Model::setVertexShader(std::shared_ptr<VertexShader> vshader, const std::vector<int>& indices) {
    //�ύX���郁�b�V���̃C���f�b�N�X������΂���𗘗p����
    if (indices.size() > 0) {
        for (auto&& i : indices) {
            mMeshes[i]->mVShader = vshader;
        }
        return;
    }
    //�Ȃ���΂��ׂẴV�F�[�_�[��ς���
    for (auto&& mesh : mMeshes) {
        mesh->mVShader = vshader;
    }
}

void Model::setVertexShader(const std::vector<std::shared_ptr<VertexShader>>& vshaders) {
    MY_ASSERTION(vshaders.size() == mMeshes.size(),
        "�V�F�[�_�[�z�񂪕s���Ȓl�ł�");
    const int size = mMeshes.size();
    for (int i = 0; i < size; i++) {
        mMeshes[i]->mVShader = vshaders[i];
    }
}

void Model::setPixelShader(std::shared_ptr<PixelShader> pshader, const std::vector<int>& indices) {
    //�ύX���郁�b�V���̃C���f�b�N�X������΂���𗘗p����
    if (indices.size() > 0) {
        for (auto&& i : indices) {
            mMeshes[i]->mPShader = pshader;
        }
        return;
    }
    //�Ȃ���΂��ׂẴV�F�[�_�[��ς���
    for (auto&& mesh : mMeshes) {
        mesh->mPShader = pshader;
    }
}

void Model::setPixelShader(const std::vector<std::shared_ptr<PixelShader>>& pshaders) {
    MY_ASSERTION(pshaders.size() == mMeshes.size(),
        "�V�F�[�_�[�z�񂪕s���Ȓl�ł�");
    const int size = mMeshes.size();
    for (int i = 0; i < size; i++) {
        mMeshes[i]->mPShader = pshaders[i];
    }
}

} //Graphics 
} //Framework 
