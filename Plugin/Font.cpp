#include "stdinc.h"
#include "byte_pattern.h"

namespace Font
{
	/*-----------------------------------------------*/
	
	errno_t heapAllocInitFlag_hook(RunOptions *options) {
		std::string desc = "heap alloc init flag";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
			byte_pattern::temp_instance().find_pattern("8B EC 56 8B 75 08 83 FE E0 77 30");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov ebp, esp
			    // 0x8はHEAP_ZERO_MEMORY
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x28), 0x08, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t buffSizeLauncher_hook(RunOptions *options) {
		std::string desc = "launcher font heap size change";

		switch (options->version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("68 90 26 00 00");
			if (byte_pattern::temp_instance().has_size(3, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(0).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(2).address(3), 0x04, true);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
			byte_pattern::temp_instance().find_pattern("68 A8 26 00 00");
			if (byte_pattern::temp_instance().has_size(3, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(0).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(2).address(3), 0x04, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t buffSizeMain_hook(RunOptions *options) {
		std::string desc = "main font heap size change";

		switch (options->version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("68 84 26 00 00");
			if (byte_pattern::temp_instance().has_size(3,desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(0).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(2).address(3), 0x04, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
			byte_pattern::temp_instance().find_pattern("68 9C 26 00 00");
			if (byte_pattern::temp_instance().has_size(3, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(0).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(2).address(3), 0x04, true);
			}
			else return CK2ERROR1;
			return NOERROR;

		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/
	errno_t maxFontSizeChange_hook(RunOptions *options) {
		std::string desc = "max font size change";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
		case v3_0_X:
		case v3_1_0:
			/* File容量の制限解除 */
			byte_pattern::temp_instance().find_pattern("81 FE 00 00 00 02");
			if (byte_pattern::temp_instance().has_size(2,desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(0).address(0x5), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(0x5), 0x04, true);
			}
			else return CK2ERROR1;

			byte_pattern::temp_instance().find_pattern("68 00 00 00 02 C7 87 8C");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x4), 0x04, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("map font view");

		// フォントのバッファ拡張（本体）
		result |= buffSizeMain_hook(options);
		// フォントのバッファ拡張（ランチャー）
		result |= buffSizeLauncher_hook(options);
		// ヒープクリアフラグ
		result |= heapAllocInitFlag_hook(options);
		// 最大ファイルサイズを変更
		result |= maxFontSizeChange_hook(options);

		return result;
	}
}