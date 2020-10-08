/*
** AM���C�u���� �w���p�[
*/

#include	<Windows.h>
#include	<stdio.h>

#include	"amgame.h"
#include	"AmHelper.h"



// printf()�I�� DrawString()���g���֐�
void DrawPrintf( int x, int y, int nColor, const char *fmt, ... ) {
	// printf�̂悤�ȁA�����̐����m�肵�Ă��Ȃ��ꍇ�A ... �Ƃ����L�q������
	// ����� va_list �Ŏ擾�ł���
	// �����̎d�g�݂𗝉�����̂ł���� vsprintf() �ɂ��Ē��ׂ�Ɨǂ�

	// fmt �ȉ��̈�������Asz[] �ɕ���������o��
	char sz[0xffff];		// �z�񐔂�[0xffff]�Ȃ̂́A���ꂭ�炢����Α���邾�낤�I�T�C�Y�B������ꂽ���肪�o��B
	va_list list;
	va_start( list, fmt );
	vsprintf( sz, fmt, list );
	va_end( list );

	// ���o���������� sz[] ���g���ĉ�ʂɕ������`�悷��
	DrawString( x, y, sz, nColor );

}



// ���̕`��
// (x1,y1) - (x2,y2)
void DrawLine( int x1, int y1, int x2, int y2, int color ) {
	int x, y;
	// ���`�⊮�����`�悷��
	// x, y �̒��������x�[�X�Ƀ��[�v
	if ( abs(x1-x2) > abs(y1-y2) ) {
		// x�x�[�X
		if ( x1 > x2 ) {
			x = x1; x1 = x2; x2 = x;
			y = y1; y1 = y2; y2 = y;
		}
		for ( x = 0; x <= x2 - x1; x++ ) {
			y = y1 + ( y2 - y1 ) * x / ( x2 - x1 );
			DrawPixel( x1 + x, y, color );
		}
	} else {
		// y�x�[�X
		if ( y1 > y2 ) {
			x = x1; x1 = x2; x2 = x;
			y = y1; y1 = y2; y2 = y;
		}
		for ( y = 0; y <= y2 - y1; y++ ) {
			x = x1 + ( x2 - x1 ) * y / ( y2 - y1 );
			DrawPixel( x, y1 + y, color );
		}
	}
}


// �~�̕`��
// ���S(x,y) ���ar
void DrawCircle( int x, int y, int r, int color ) {
	// �v���[���n���ɂ��~�`��
	int cx, cy, d;
	cx = 0;
    cy = r;
    d = 2 - 2 * r;

	// �J�n�_�̕`��
	DrawPixel(  cx + x,  cy + y, color );	//  (0, R);
    DrawPixel(  cx + x, -cy + y, color );	//  (0, -R);
    DrawPixel(  cy + x,  cx + y, color );	//  (R, 0);
    DrawPixel( -cy + x,  cx + y, color );	//  (-R, 0);

	// 90�x���[�v
	while (1) {
		if (d > -cy) {
			cy--;
			d += 1 - 2 * cy;
		}

		if (d <= cx) {
			cx++;
			d += 1 + 2 * cx;
		}

		if (!cy) break;    // �`��I��

		// �`��
		DrawPixel(  cx + x,  cy + y, color );	// 0�`90�x�̊�
		DrawPixel( -cx + x,  cy + y, color );	// 90�`180�x�̊�
		DrawPixel( -cx + x, -cy + y, color );	// 180�`270�x�̊�
		DrawPixel(  cx + x, -cy + y, color );	// 270�`360�x�̊�
	}
}

// ��ʂ̃L���v�`���𐳂����s��
// GetDispGraph()�͍��W�ʒu���������L��
int		GetDispGraphToTexture(int hPicture) {
	POINT pt = { 0,0 };
	ClientToScreen(gg_hWindow, &pt);
	gg_piDispLocate.x = pt.x;
	gg_piDispLocate.y = pt.y;
	return GetDispGraph(hPicture);
}

