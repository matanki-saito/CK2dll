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

		// マップフォント表示処理
		success |= MapView::init(version);

		// マップフォントjustify
		success |= MapJustify::init(version);

		// マップフォント調整処理１
		success |= MapAdj::init(version);

		// マップフォント表示調整２
		success |= MapAdj2::init(version);

		// マップフォント表示調整３
		success |= MapAdj3::init(version);

		// フォントローディング処理
		success |= Font::init(version);

		// 終了時のダイアログの花文字
		//success |= DecorativeLetterEndDialog::init(version);

		// ダイアログの花文字
		//success |= DecorativeLetterDialog::init(version);

		// 継承ダイアログの花文字
		//success |= DecorativeLetterInheritDialog::init(version);

		// Buttonとツールチップ
		success |= ButtonAndTooltip::init(version);

		// メインテキスト
		success |= MainText::init(version);

		// メインテキスト改行処理（ダイアログ）
		success |= MainTextLineBreak::init(version);

		// ニックネーム修正
		//success |= NickNameFix::init(version);

		// Dynastyに-idがつかないようにする
		success |= NoDynastyId::init(version);

		// IME
		success |= IME::init(version);

		//Input
		success |= Input::init(version);

		//Unknown 3
		success |= Unk3::init(version);

		//Unknown 4
		success |= Unk4::init(version);

		// issue33
		//success |= Issue33::init(version);

		// issue32
		//success |= Issue32::init(version);

		// 日付表記の変更
		success |= DateFormat::init(version);

		if (success == NOERROR) {
			byte_pattern::debug_output2("Multibyte DLL [OK]");
		}
		else {
			MessageBoxW(NULL, L"[Multibyte DLL ERROR]\nThis game version is not supported by Multibyte DLL.\nPlease delete d3d9.dll and restart game.\nOr check new version dll.\n\nhttps://github.com/matanki-saito/CK2Dll", L"Multibyte DLL", MB_OK);
			byte_pattern::debug_output2("Multibyte DLL [NG]");
			exit(-1);
		}

    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        byte_pattern::shutdown_log();
    }

    return TRUE;
}
