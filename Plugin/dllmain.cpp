#include "stdinc.h"
#include "byte_pattern.h"

BOOL WINAPI DllMain(HMODULE module, DWORD reason, void *reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        byte_pattern::start_log(L"ck2jps");

		// versionを文字列から取得
		CK2Version version = Misc::getVersion();

		errno_t success = NOERROR;

		// マップフォント表示
		MapView::init(version);

		// マップフォントjustify
		MapJustify::init(version);

		// フォント
		Font::init(version);

		// 終了時のダイアログの花文字
		DecorativeLetterEndDialog::init(version);

		// ダイアログの花文字
		DecorativeLetterDialog::init(version);

		// 継承ダイアログの花文字
		DecorativeLetterInheritDialog::init(version);

		// Buttonとツールチップ
		ButtonAndTooltip::init(version);

		// メインテキスト
		MainText::init(version);

		if (success == NOERROR) {
			//MessageBoxW(NULL, L"[OK]", L"Multibyte DLL", MB_OK);
			byte_pattern::temp_instance().debug_output2("DLL [OK]");
		}
		else {
			MessageBoxW(NULL, L"[NG]", L"Multibyte DLL", MB_OK);
			byte_pattern::temp_instance().debug_output2("DLL [NG]");
			exit(-1);
		}

    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        byte_pattern::shutdown_log();
    }

    return TRUE;
}
