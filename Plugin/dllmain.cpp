#include "stdinc.h"
#include "byte_pattern.h"
#include "moddl.h"

BOOL WINAPI DllMain(HMODULE module, DWORD reason, void *reserved)
{
	
    if (reason == DLL_PROCESS_ATTACH)
    {
		// moddownload
		wchar_t myDocumentPath[MAX_PATH];
		SHGetSpecialFolderPath(NULL, myDocumentPath, CSIDL_PERSONAL, 0);

		const path gameDirPath = path{ myDocumentPath } / L"Paradox Interactive" / L"Crusader Kings II";
		if (!InitAutoUpdate(gameDirPath)) exit(-1);

        byte_pattern::start_log(L"ck2jps");

		// オプションをiniファイルから取得
		RunOptions options = RunOptions();
		Misc::getOptionsByINI(&options);

		// versionを文字列から取得
		CK2Version version = Misc::getVersion();

		// version設定
		options.version = version;

		errno_t success = NOERROR;

		// マップフォント表示処理
		success |= MapView::init(&options);

		// マップフォントjustify
		success |= MapJustify::init(&options);

		// マップフォント調整処理１
		success |= MapAdj::init(&options);

		// マップフォント表示調整２
		success |= MapAdj2::init(&options);

		// マップフォント表示調整３ おそらく強制大文字の解除
		success |= MapAdj3::init(&options);

		// フォントローディング処理
		success |= Font::init(&options);

		// 終了時のダイアログの花文字
		success |= DecorativeLetterEndDialog::init(&options);

		// ダイアログの花文字
		success |= DecorativeLetterDialog::init(&options);

		// 継承ダイアログの花文字
		success |= DecorativeLetterInheritDialog::init(&options);

		// Buttonとツールチップ
		success |= ButtonAndTooltip::init(&options);

		// メインテキスト
		success |= MainText::init(&options);

		// メインテキスト改行処理（ダイアログ）
		success |= MainTextLineBreak::init(&options);

		// ニックネーム修正
		success |= NickNameFix::init(&options);

		// Dynastyに-idがつかないようにする
		success |= NoDynastyId::init(&options);

		// IME
		success |= IME::init(&options);

		//Input
		success |= Input::init(&options);

		// 不明（忘れた…）
		success |= Unk3::init(&options);
		
		// ...の省略
		success |= TextOerflow::init(&options);

		// 不明
		success |= Unk5::init(&options);

		// issue33 「XXXに忠誠を誓っている」にしたい
		// https://github.com/matanki-saito/CK2dll/issues/33
		success |= Issue33::init(&options);

		// issue32 家 名前になっているので、日本語のときのみ名前 家にしたい
		// https://github.com/matanki-saito/CK2dll/issues/32
		success |= Issue32::init(&options);

		// 日付表記の変更
		success |= DateFormat::init(&options);

		// ファイル保存
		success |= FileSave::init(&options);

		if (success == NOERROR && options.test == false) {
			byte_pattern::temp_instance().debug_output2("DLL [OK]");
		}
		else {
			const DWORD sysDefLcid = ::GetSystemDefaultLCID();

			WCHAR* message;
			WCHAR* caption;

			switch (sysDefLcid) {
			case MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN):
				caption = L"エラー";
				message = L""
					L"このバージョンはまだ日本語化に対応していないため起動できません。\n"
					L"将来、日本語化に対応した際には自動的に起動できるようになります。\n"
					L"\n"
					L"以前のバージョンに戻す方法は下記サイトをご覧ください。\n"
					L"https://paradoxian-japan-mod.com/version";
				break;

			case MAKELANGID(LANG_CHINESE_SIMPLIFIED, SUBLANG_CHINESE_SIMPLIFIED):
				caption = L"错误";
				message = L""
					L"Multibyte DLL 尚未支持此游戏版本。\n"
					L"当我发布新的时，它会自动更新。\n"
					L"\n"
					L"DLL宣布页面:\n"
					L"https://github.com/matanki-saito/EU4dll";
				break;


			case MAKELANGID(LANG_CHINESE_TRADITIONAL, SUBLANG_CHINESE_TRADITIONAL):
				caption = L"錯誤";
				message = L""
					L"Multibyte DLL 尚未支持此遊戲版本。\n"
					L"當我發布新的時，它會自動更新。\n"
					L"\n"
					L"DLL宣布頁面:\n"
					L"https://github.com/matanki-saito/EU4dll";
				break;

			case MAKELANGID(LANG_KOREAN, SUBLANG_KOREAN):
				caption = L"오류";
				message = L""
					L"멀티 바이트 DLL은 아직이 게임 버전을 지원하지 않습니다.\n"
					L"새 게시물을 게시하면 자동으로 업데이트됩니다.\n"
					L"\n"
					L"DLL 공지 페이지:\n"
					L"https://github.com/matanki-saito/EU4dll";
				break;

			case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US):
			default:
				caption = L"ERROR";
				message = L""
					L"Multibyte DLL hasn't supported this game version yet.\n"
					L"It will be updated automatically, when I publish new one.\n"
					L"\n"
					L"DLL announce page:\n"
					L"https://github.com/matanki-saito/EU4dll";
			}

			MessageBoxW(NULL, message, caption, MB_OK);

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
