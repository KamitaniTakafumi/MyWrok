#ifndef __AMHELPER_H__
#define __AMHELPER_H__
/*
** AM���C�u���� �w���p�[
*/


#include	<Windows.h>
#include	<stdio.h>
#include	"amgame.h"


// �ꕔwarning���o���Ȃ��悤�ɂ���ݒ�
#pragma warning(disable : 4996)



// printf()�I�� DrawString()���g���֐�
void	DrawPrintf( int x, int y, int nColor, const char *fmt, ... );

// ���̕`��
// (x1,y1) - (x2,y2)
void	DrawLine( int x1, int y1, int x2, int y2, int color );


// �~�̕`��
// ���S(x,y) ���ar
void	DrawCircle( int x, int y, int r, int color );


// ��ʂ̃L���v�`���𐳂����s��
// GetDispGraph()�͍��W�ʒu���������L��
int		GetDispGraphToTexture(int hPicture);



#endif // !__AMHELPER_H__
