// clipy.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
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

	// メモリオブジェクト確保
	hMem = GlobalAlloc( GHND, nLen );

	// メモリオブジェクトをロックしてアドレスを取得
	lpMem = ( LPSTR ) GlobalLock( hMem );

	// メモリオブジェクトに文字列を書き込む
	//memset( lpMem, 0x00, length + 1 );
	//lstrcpyW( lpMem, lplpszArgs[ 1 ] );
	::WideCharToMultiByte( CP_THREAD_ACP, 0, lplpszArgs[ 1 ], nLen, lpMem, nLen, NULL, NULL );

	// メモリオブジェクトをアンロック
	GlobalUnlock( hMem );

	// クリップボードをオープン
	OpenClipboard( NULL );
	// クリップボードをクリア
	EmptyClipboard();

	// クリップボードにメモリオブジェクトの文字列をコピー
	SetClipboardData( CF_TEXT, hMem );

	// クリップボードをクローズ
	CloseClipboard();

	return 0;
}

