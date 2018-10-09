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
		success |= MapView::init(version);

		// マップフォントjustify
		success |= MapJustify::init(version);

		// フォント
		success |= Font::init(version);

		// 終了時のダイアログの花文字
		success |= DecorativeLetterEndDialog::init(version);

		// ダイアログの花文字
		success |= DecorativeLetterDialog::init(version);

		// 継承ダイアログの花文字
		success |= DecorativeLetterInheritDialog::init(version);

		// Buttonとツールチップ
		success |= ButtonAndTooltip::init(version);

		// メインテキスト
		success |= MainText::init(version);

		// ニックネーム修正
		success |= NickNameFix::init(version);

		// Dynastyに-idがつかないようにする
		success |= NoDynastyId::init(version);

		// IME
		success |= IME::init(version);

		//その他
		success |= Misc::init(version);

		if (success == NOERROR) {
			byte_pattern::debug_output2("DLL [OK]");
		}
		else {
			MessageBoxW(NULL, L"[NG]", L"Multibyte DLL", MB_OK);
			byte_pattern::debug_output2("DLL [NG]");
			exit(-1);
		}

    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        byte_pattern::shutdown_log();
    }

    return TRUE;
}
