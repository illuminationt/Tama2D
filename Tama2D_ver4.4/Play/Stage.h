#ifndef STAGE_H
#define STAGE_H

#include"Space/Vector2.h"
#include<vector>
class StaticObject;
class DynamicObject;
class Rect;

class Stage
{
public:
	Stage(const char* CSVfilename,
		const char* CSVEnemyFilename);
	virtual ~Stage();

	const Rect* rect(int index)const;
	//j�Ԗڂ̃X�^�e�B�b�N�I�u�W�F�N�g�͏Փˏ����K�v�Ȉʒu�ɂ��邩�H
	bool needCheckColWithPlayer(int j)const;

	void setStaticTexture();
	void setDynamicTexture();
	void drawStatic();
	void drawDynamic();

	//�v���C���[��X�ړ��̓X�e�[�W�̑��Έړ��Ŏ����B
	//�v���C���[�̓������󂯎�葊�Έړ�
	void update(const Vector2& playerMove, const Vector2& playerPos,const Vector2* enemyMove);

	StaticObject* sObject(int j)const;
	DynamicObject* dObject(int j)const;

	int indexStatic(int j)const;
	int indexDynamic(int j)const;
	int gridNumber()const;
	int sObjectNumber()const;
	int dObjectNumber()const;
private:
	StaticObject** m_sObjects;
	DynamicObject** m_dObjects;

	//CSV�̒��̐������L�^�����z��
	std::vector<int> m_indexStatic;
	int* m_indexDynamic;

	int m_colNumber;
	int m_rowNumber;
	int m_gridNumber;
	int m_sObjectNumber;//���ۂ�static object�̐�
	int m_dObjectNumber;//���ۂ�dynamic object�̐�

	static const int m_maxColNumberStatic;//�e�N�X�`�����̍ő�̗�̐�(�X�^�e�B�b�N�I�u�W�F�N�g�́j
	static const int m_maxRowNumberStatic;//�e�N�X�`�����̍ő�̍s�̐�(�X�^�e�B�b�N�I�u�W�F�N�g�́j
	static const int m_maxColNumberDynamic;;//�e�N�X�`�����̍ő�̗�̐�(�_�C�i�~�b�N�I�u�W�F�N�g�́j
	static const int m_maxRowNumberDynamic;;//�e�N�X�`�����̍ő�̍s�̐�(�_�C�i�~�b�N�I�u�W�F�N�g�́j
};



#endif