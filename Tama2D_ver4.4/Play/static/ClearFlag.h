#ifndef CLEARFLAG_H
#define CLEARFLAG_H

#include"Play/StaticObject.h"

//�N���A�t���O�Ƃ�
/*
�����̂��ʓ|�����o���G�e�B�L���ɂ������̂�
�u����ɐG�ꂽ��S�[���v���Ă������̂���肽���Ǝv���܂�
�O�������낢��Ȃ��̂ɂ������̂ŁA
�u�{����CSV�̒l+1000�v��Excel��CSV�t�@�C���ɏ�������ŁA
�ǂݍ��ނƂ���-1000���ĕ`�悷��A�Ƃ������@�ōs���܂�
*/

class ClearFlag:public StaticObject{
public:
	ClearFlag(int csvNumber);
	~ClearFlag();
};


#endif