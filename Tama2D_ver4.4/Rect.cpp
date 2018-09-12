#include "Rect.h"
#include"Space/Vector2.h"

namespace {//無名
	const int INTERNAL_UNIT = 1000;
}
Rect::Rect():
	m_x(0),m_y(0),
	m_sizeX(0),m_sizeY(0),
	m_offsetX(0),m_offsetY(0),
	m_sizeRateX(1.f),m_sizeRateY(1.f){
}



bool Rect::isIntersect(const Rect& r)const {
	//自分：a、相手：bとする
	//まずxから
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
	//いじってもいいコピーを用意
	Rect rect = *this;

	//移動ベクトルを内部単位に変換
	int tx = static_cast<int>(inout->x*INTERNAL_UNIT);
	int ty = static_cast<int>(inout->y*INTERNAL_UNIT);

	//とりあえず移動。衝突検出はそのあと。
	rect.m_x += tx;
	rect.m_y += ty;

	//移動先で衝突しないとき。動いても良い
	if (!rect.isIntersect(r)) {
		return;
	}
	
	//当たってしまった。
	//xには動ける、yには動ける場合をそれぞれ試す
	//yのみ動ける場合
	rect.m_x -= tx;
	if (!rect.isIntersect(r)) {//yは動ける
		//==============苦肉の策=============
		if (playerPrevMove.y == 0.f) {
			rect.m_x += tx;
			rect.m_y -= ty;
			if (!rect.isIntersect(r)) {
				int ab = m_y + m_sizeY;//BottomA
				int bt = r.m_y;
				if (ab <= bt) {//自分が上にいるなら
					inout->y = (bt - ab) / INTERNAL_UNIT;
				}
				else {//自分が下なら
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
		if (al >= br) {//自分が右側にいるなら
			inout->x = -(al - br) / INTERNAL_UNIT;
		}
		else {//自分が左側なら
			int ar = m_x + m_sizeX;//RightA
			int bl = r.m_x;
			inout->x = (bl - ar) / INTERNAL_UNIT;
		}

		return;
	}
	rect.m_x += tx;//元に戻しとく
	//xのみ動ける場合
	rect.m_y -= ty;
	if (!rect.isIntersect(r)) {
		int ab = m_y + m_sizeY;//BottomA
		int bt = r.m_y;
		if (ab <= bt) {//自分が上にいるなら
			inout->y = (bt - ab) / INTERNAL_UNIT;
		}
		else {//自分が下なら
			int at = m_y;//TopA
			int bb = r.m_y + r.m_sizeY;
			inout->y = -(at - bb) / INTERNAL_UNIT;
		}
		return;
	}

	//どの方向にも動けない場合
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

/*床突っかかり解消コード解説

まず、今、このゲームではプレイヤーのあたり判定を、左上のスタティックオブジェクトから
英文読む方向に順番に当たり判定を行っている。
プレイヤーが設置していて左に進む際、左への入力と重力の合成で
左下方向へのベクトルが入力ベクトルとなる。
その状態で床のオブジェクトの境目に来ると、
まず左側の床との衝突判定が行われる。
今このコードでは、まずx方向を消して当たらなければyだけに動ける、として
入力ベクトルの内x方向を消し、y方向のみを移動ベクトルとしていた。
よって左側の床との衝突判定によりx方向は消されy方向のみが残る。
y方向のみが残った状態で境目の右側との衝突判定が行われる。
当然、y方向に進めば衝突するのでこの入力ベクトルは消され、
結局入力ベクトルは0になり、移動ベクトルが0になる。
これが不自然な突っかかりの原因である。
解消策
x方向を消して衝突しないなら、x方向を元に戻してy方向を消して衝突判定をしてみる。
例の床突っかかりの状態にあるならばy方向を消せばうまく行くのでこれでOK
単にx方向に壁がある状態なら、x方向を元に戻した時点でまた壁にめり込む形で衝突するので、
この解消策はキャンセルされ、y方向のみに動くようになる。

お疲れ様でした

|=========================================|
|↑よくよく考えたらなにも解消してなかった |
|=========================================|
どうしよう～～～～～～～～
↑無理矢理解決した

*/