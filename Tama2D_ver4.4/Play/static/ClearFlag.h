#ifndef CLEARFLAG_H
#define CLEARFLAG_H

#include"Play/StaticObject.h"

//クリアフラグとは
/*
旗作るのも面倒だしバラエティ豊かにしたいので
「これに触れたらゴール」っていう物体を作りたいと思います
外見もいろいろなものにしたいので、
「本来のCSVの値+1000」をExcelのCSVファイルに書き込んで、
読み込むときに-1000して描画する、という方法で行きます
*/

class ClearFlag:public StaticObject{
public:
	ClearFlag(int csvNumber);
	~ClearFlag();
};


#endif