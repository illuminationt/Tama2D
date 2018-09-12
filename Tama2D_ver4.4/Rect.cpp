#include "Rect.h"
#include"Space/Vector2.h"

namespace {//����
	const int INTERNAL_UNIT = 1000;
}
Rect::Rect():
	m_x(0),m_y(0),
	m_sizeX(0),m_sizeY(0),
	m_offsetX(0),m_offsetY(0),
	m_sizeRateX(1.f),m_sizeRateY(1.f){
}



bool Rect::isIntersect(const Rect& r)const {
	//�����Fa�A����Fb�Ƃ���
	//�܂�x����
	int al = m_x;//LeftA
	int ar = m_x + m_sizeX;//RightA
	int bl = r.m_x;
	int br = r.m_x + r.m_sizeX;
	if ((al < br) && (ar > bl)) {
		int ab = m_y +m_sizeY;//BottomA
		int at = m_y;//TopA
		int bb = r.m_y + r.m_sizeY;
		int bt = r.m_y;
		if ((at < bb) && (ab >bt)) {
			return true;
		}
	}
	return false;
}

void Rect::setPosition(const Vector2& a) {
	m_x = static_cast<int>(a.x*INTERNAL_UNIT)+m_offsetX;
	m_y = static_cast<int>(a.y*INTERNAL_UNIT)+m_offsetY;
}
void Rect::setPosition(float x, float y) {
	m_x = static_cast<int>(x*INTERNAL_UNIT)+m_offsetX;
	m_y = static_cast<int>(y*INTERNAL_UNIT)+m_offsetY;
}
void Rect::setSize(const Vector2& a) {
	m_sizeX = static_cast<int>(a.x*m_sizeRateX*INTERNAL_UNIT);
	m_sizeY = static_cast<int>(a.y*m_sizeRateY*INTERNAL_UNIT);
}
void Rect::setSize(float x,float y) {
	m_sizeX = static_cast<int>(x*m_sizeRateX*INTERNAL_UNIT);
	m_sizeY = static_cast<int>(y*m_sizeRateY*INTERNAL_UNIT);
}
void Rect::setOffset(const Vector2& a) {
	m_offsetX = static_cast<int>(a.x*INTERNAL_UNIT);
	m_offsetY = static_cast<int>(a.y*INTERNAL_UNIT);
}
void Rect::setOffset(float x, float y) {
	m_offsetX = static_cast<int>(x*INTERNAL_UNIT);
	m_offsetY = static_cast<int>(y*INTERNAL_UNIT);
}
void Rect::setSizeRate(const Vector2& a) {
	m_sizeRateX = a.x;
	m_sizeRateY = a.y;
}
void Rect::setSizeRate(float x,float y) {
	m_sizeRateX = x;
	m_sizeRateY = y;
}

void Rect::restrictMove(Vector2* inout, const Rect& r,const Vector2& playerPrevMove)const {
	//�������Ă������R�s�[��p��
	Rect rect = *this;

	//�ړ��x�N�g��������P�ʂɕϊ�
	int tx = static_cast<int>(inout->x*INTERNAL_UNIT);
	int ty = static_cast<int>(inout->y*INTERNAL_UNIT);

	//�Ƃ肠�����ړ��B�Փˌ��o�͂��̂��ƁB
	rect.m_x += tx;
	rect.m_y += ty;

	//�ړ���ŏՓ˂��Ȃ��Ƃ��B�����Ă��ǂ�
	if (!rect.isIntersect(r)) {
		return;
	}
	
	//�������Ă��܂����B
	//x�ɂ͓�����Ay�ɂ͓�����ꍇ�����ꂼ�ꎎ��
	//y�̂ݓ�����ꍇ
	rect.m_x -= tx;
	if (!rect.isIntersect(r)) {//y�͓�����
		//==============����̍�=============
		if (playerPrevMove.y == 0.f) {
			rect.m_x += tx;
			rect.m_y -= ty;
			if (!rect.isIntersect(r)) {
				int ab = m_y + m_sizeY;//BottomA
				int bt = r.m_y;
				if (ab <= bt) {//��������ɂ���Ȃ�
					inout->y = (bt - ab) / INTERNAL_UNIT;
				}
				else {//���������Ȃ�
					int at = m_y;//TopA
					int bb = r.m_y + r.m_sizeY;
					inout->y = -(at - bb) / INTERNAL_UNIT;
				}
				return;
			}
		}
		//=============================================

		int al = m_x;//LeftA
		int br = r.m_x + r.m_sizeX;
		if (al >= br) {//�������E���ɂ���Ȃ�
			inout->x = -(al - br) / INTERNAL_UNIT;
		}
		else {//�����������Ȃ�
			int ar = m_x + m_sizeX;//RightA
			int bl = r.m_x;
			inout->x = (bl - ar) / INTERNAL_UNIT;
		}

		return;
	}
	rect.m_x += tx;//���ɖ߂��Ƃ�
	//x�̂ݓ�����ꍇ
	rect.m_y -= ty;
	if (!rect.isIntersect(r)) {
		int ab = m_y + m_sizeY;//BottomA
		int bt = r.m_y;
		if (ab <= bt) {//��������ɂ���Ȃ�
			inout->y = (bt - ab) / INTERNAL_UNIT;
		}
		else {//���������Ȃ�
			int at = m_y;//TopA
			int bb = r.m_y + r.m_sizeY;
			inout->y = -(at - bb) / INTERNAL_UNIT;
		}
		return;
	}

	//�ǂ̕����ɂ������Ȃ��ꍇ
	inout->x = inout->y = 0.0;
	return;

}


float Rect::offsetX()const {
	return m_offsetX / INTERNAL_UNIT;
}
float Rect::offsetY()const {
	return m_offsetY / INTERNAL_UNIT;
}
float Rect::sizeRateX()const {
	return m_sizeRateX;
}
float Rect::sizeRateY()const {
	return m_sizeRateY;
}

/*���˂�����������R�[�h���

�܂��A���A���̃Q�[���ł̓v���C���[�̂����蔻����A����̃X�^�e�B�b�N�I�u�W�F�N�g����
�p���ǂޕ����ɏ��Ԃɓ����蔻����s���Ă���B
�v���C���[���ݒu���Ă��č��ɐi�ލہA���ւ̓��͂Əd�͂̍�����
���������ւ̃x�N�g�������̓x�N�g���ƂȂ�B
���̏�Ԃŏ��̃I�u�W�F�N�g�̋��ڂɗ���ƁA
�܂������̏��Ƃ̏Փ˔��肪�s����B
�����̃R�[�h�ł́A�܂�x�����������ē�����Ȃ����y�����ɓ�����A�Ƃ���
���̓x�N�g���̓�x�����������Ay�����݂̂��ړ��x�N�g���Ƃ��Ă����B
����č����̏��Ƃ̏Փ˔���ɂ��x�����͏�����y�����݂̂��c��B
y�����݂̂��c������Ԃŋ��ڂ̉E���Ƃ̏Փ˔��肪�s����B
���R�Ay�����ɐi�߂ΏՓ˂���̂ł��̓��̓x�N�g���͏�����A
���Ǔ��̓x�N�g����0�ɂȂ�A�ړ��x�N�g����0�ɂȂ�B
���ꂪ�s���R�ȓ˂�������̌����ł���B
������
x�����������ďՓ˂��Ȃ��Ȃ�Ax���������ɖ߂���y�����������ďՓ˔�������Ă݂�B
��̏��˂�������̏�Ԃɂ���Ȃ��y�����������΂��܂��s���̂ł����OK
�P��x�����ɕǂ������ԂȂ�Ax���������ɖ߂������_�ł܂��ǂɂ߂荞�ތ`�ŏՓ˂���̂ŁA
���̉�����̓L�����Z������Ay�����݂̂ɓ����悤�ɂȂ�B

�����l�ł���

|=========================================|
|���悭�悭�l������Ȃɂ��������ĂȂ����� |
|=========================================|
�ǂ����悤�`�`�`�`�`�`�`�`
���������������

*/