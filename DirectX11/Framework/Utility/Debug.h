#pragma once

#include <string>
#include "Utility/StringBuilder.h"
#include "Utility/Singleton.h"

/**
* @def VisualStudio�̏o�͂Ƀ��O�o��
* @param mes �\�����郁�b�Z�[�W
*/
#define MY_DEBUG_LOG(mes) Framework::Utility::Debug::getInstance().debugLog(__FUNCTION__,__LINE__, mes)

/**
* @def �A�T�[�V����
* @param cond ������
* @param mes cond��false�̎��ɕ\�����郁�b�Z�[�W
*/
#define MY_ASSERTION(cond,mes) Framework::Utility::Debug::getInstance().assertion(__FUNCTION__,__LINE__,cond, mes);

/**
* @def �G���[�E�B���h�E�̕\��
* @param cond ������
* @param mes cond��false�̎��ɕ\�����郁�b�Z�[�W
* @details �f�o�b�O���ɂ̓��b�Z�[�W�ƂƂ��ɔ��������֐����A�s�ԍ����\�������
*/
#define MY_ERROR_WINDOW(cond,mes) Framework::Utility::Debug::getInstance().errorWindow(__FUNCTION__,__LINE__,cond,mes);

/**
* @def �����𖞂����Ă�����VisualStudio�̏o�͂Ƀ��O�o��
* @param cond ������
* @param mes �\�����郁�b�Z�[�W
*/
#define MY_DEBUG_LOG_IF(cond,mes) if((cond)) MY_DEBUG_LOG(mes)

namespace Framework {
namespace Utility {
class Debug : public Singleton<Debug> {
public:
    /**
    * @brief �A�T�[�V����
    * @param funcName �֐���
    * @param line ���������s
    * @param condition ����
    * @param message �G���[���b�Z�[�W
    */
    void assertion(const std::string& funcName, int line,
        bool condition, const std::string& message);
    /**
    * @brief ���O�o��
    * @param funcName �֐���
    * @param line ���������s
    * @param message �o�͓��e
    */
    void debugLog(const std::string& funcName, int line, const std::string& message);
    /**
    * @brief �G���[�E�B���h�E�̕\��
    * @param funcName �֐���
    * @param line ���������s
    * @param condition ������
    * @param message �G���[���b�Z�[�W
    */
    void errorWindow(const std::string& funcName, int line,
        bool condition, const std::string& message);
    /**
    * @brief �G���[���b�Z�[�W�̍쐬
    * @param funcName �֐���
    * @param line ���������s
    * @param message ���ۂ̃G���[���b�Z�[�W
    * @return [funcName line:message]�̌`���̃��b�Z�[�W��Ԃ�
    */
    std::string errorMessage(const std::string& funcName, int line,
        const std::string& message);
protected:
    /**
    * @brief �R���X�g���N�^
    */
    Debug();
    /**
    * @brief �f�X�g���N�^
    */
    ~Debug();
};

} //Utility
} //Framework