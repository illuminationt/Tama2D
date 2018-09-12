#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include"Rect.h"
#include"Space/Vector2.h"
class Image;
//�e�N�X�`���A�e�N�X�`���̒��̏����ꏊ�A��ʓ��̕`���ꏊ�A�傫�����������
//�����`�悷�邾���̊֐����������ȁ`�`

class StaticObject
{
public:
	StaticObject();
	virtual ~StaticObject();

	enum Tag {
		TAG_BRICK,
		TAG_HATENA,
		TAG_COIN,
		TAG_GOALPOLE,
		TAG_CLEAR_FLAG,//�S�[���̊��ł͂Ȃ�
		TAG_OTHER_BLOCKS,
		TAG_BACKGROUND,

		TAG_NOKO,

		TAG_OTHER_ENEMY,
	};
	
	virtual void initialize(
		const char* filename,
		int colNumber,//�e�N�X�`���̗�
		int rowNumber,//�e�N�X�`���̍s
		int startFrame,//���̊G���n�܂�t���[���i�ꏊ�j
		int endFrame,
		int currentFrame,
		int frameDelay,
		float drawPosX,
		float drawPosY,
		float width,
		float height,
		float offsetX,
		float offsetY,
		float sizeRateX,
		float sizeRateY,
		Tag tag);

	//draw���Ƃ�setTexture���Ă��������������ɏd����
	virtual void setTexture()const;
	virtual void draw();
	//update�͖��t���[���Ă΂��i�v���C���[�����ȂȂ�����j
	virtual void update(const Vector2& playerMove,const Vector2& playerPos);
	//���̃I�u�W�F�N�g���E��
	virtual void kill();

	virtual void setCheckCollision();
	virtual bool needCheckCollision();
	virtual bool isActive()const;
	virtual bool isKilled()const;
	const Rect* rect()const;
	void setRectOffset(float, float);
	void setRectSizeRate(float, float);

	const Vector2* position()const;
	const Vector2* size()const;
	const Vector2* velocity()const;
	const Vector2* prevMove()const;

	
	const Tag tag()const;
	void setTag(Tag type);

	int colNumber()const;//�e�N�X�`�����̍s�̐�
	int rowNumber()const;//�e�N�X�`�����̗�̐�
	int startFrame()const;//�e�N�X�`�����ŃA�j���̊J�n�t���[��
	int endFrame()const;//�e�N�X�`�����ŃA�j���̏I���_
	int currentFrame()const;//�e�N�X�`�����ō��`���Ă�t���[��
	int frameDelay()const;//�A�j���̃R�}����̊Ԋu

	void setHittedDir(const Vector2&);
	int index()const;
	void setIndex(int j);
protected:
	Rect m_rect;
	Image* m_image;
	Vector2 m_position;
	Vector2 m_size;
	Vector2 m_velocity;
	Vector2 m_prevMove;

	//�����蔻�肵�Ȃ��Ă����ʒu�ɂ���Ƃ���false
	bool m_needCheckCollision;
	//�E���ꂽ��true
	bool m_isKilled;
	//��ʕ\���̕K�v���Ȃ��Ȃ�����false
	bool m_isActive;
	//���̃I�u�W�F�N�g�̎��̂͂Ȃɂ��H
	Tag m_tag;

	//�e�N�X�`���̂ǂ���`�������肷�邽�߂̕ϐ�
	//�e�N�X�`�����̍s�A��̐�
	//��̓I�ȓG�N���X�ł͓G�N���X�̃R���X�g���N�^�ŏ�����
	//�R���X�g���N�^�͊�ꁨ�h���̏��ŌĂ΂��
	int m_colNumber;
	int m_rowNumber;
	int m_startFrame;
	int m_endFrame;
	int m_currentFrame;
	int m_frameDelay;

	Vector2 m_hittedDir;
	int m_index;//�}�b�v��̉��Ԗڂɔz�u���ꂽ���H
	
};


#endif