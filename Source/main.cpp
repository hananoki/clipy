// clipy.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

int mainCRTStartup( void ) {
	int    nArgs;
	LPTSTR* lplpszArgs;
	auto ww = GetCommandLineW();
	lplpszArgs = CommandLineToArgvW( ww, &nArgs );

	if( nArgs <= 1 ) return 0;

	//int ret = WideCharToMultiByte( CP_ACP, 0, lplpszArgs[ 1 ], -1, local, dataSize + 1, NULL, NULL );
	int nLen = ::WideCharToMultiByte( CP_THREAD_ACP, 0, lplpszArgs[ 1 ], -1, NULL, 0, NULL, NULL );
	//int l2 = wcslen( lplpszArgs[ 1 ] );
	//LPCSTR moji = GetCommandLine();
	//int length = lstrlenW( lplpszArgs[1] );

	HGLOBAL hMem;
	LPSTR  lpMem;

	// �������I�u�W�F�N�g�m��
	hMem = GlobalAlloc( GHND, nLen );

	// �������I�u�W�F�N�g�����b�N���ăA�h���X���擾
	lpMem = ( LPSTR ) GlobalLock( hMem );

	// �������I�u�W�F�N�g�ɕ��������������
	//memset( lpMem, 0x00, length + 1 );
	//lstrcpyW( lpMem, lplpszArgs[ 1 ] );
	::WideCharToMultiByte( CP_THREAD_ACP, 0, lplpszArgs[ 1 ], nLen, lpMem, nLen, NULL, NULL );

	// �������I�u�W�F�N�g���A�����b�N
	GlobalUnlock( hMem );

	// �N���b�v�{�[�h���I�[�v��
	OpenClipboard( NULL );
	// �N���b�v�{�[�h���N���A
	EmptyClipboard();

	// �N���b�v�{�[�h�Ƀ������I�u�W�F�N�g�̕�������R�s�[
	SetClipboardData( CF_TEXT, hMem );

	// �N���b�v�{�[�h���N���[�Y
	CloseClipboard();

	return 0;
}

