// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include "plugin_64.h"
#include "mod_download.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ulReasonForCall,
                       LPVOID lpReserved){

		if (ulReasonForCall == DLL_PROCESS_ATTACH) {
			BytePattern::StartLog(L"ck2_jps_2");

			DllError e = {};

			// mod download
			#ifndef _DEBUG
			e |= ModDownload::Init();
			#endif

			// 設定
			RunOptions options;
			options.version = Version::GetVersion();

			// デバッグ用
			#ifdef _DEBUG
			//e |= Debug::Init(options);
			#endif

			// フォント読み込み
			e |= Font::Init(options);

			// メインテキスト
			e |= MainText::Init(options);

			// ツールチップとボタン
			e |= TooltipAndButton::Init(options);

			// マップ表示
			e |= MapView::Init(options);

			// マップ文字の調整
			e |= MapAdjustment::Init(options);

			// マップ文字の調整
			e |= MapJustify::Init(options);

			Validator::Validate(e, options);
		}
		else if (ulReasonForCall == DLL_PROCESS_DETACH) {
			BytePattern::ShutdownLog();
		}

		return TRUE;
}

