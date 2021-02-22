#include "pch.h"
#include "plugin_64.h"

namespace Font {

	extern "C" {
		void fontBufferHeapZeroClear();
		uintptr_t fontBufferHeapZeroClearReturnAddress;
		uintptr_t fontBufferHeapZeroClearHeepAllocJmpAddress;
		uintptr_t fontBufferHeapZeroClearHeapJmpAddress;
	}

	DllError fontBufferHeapZeroClearInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			// mov rcx,cs:hHeap
			BytePattern::temp_instance().find_pattern("48 8B 0D ? ? ? ? 4C 8B C3 33 D2");
			if (BytePattern::temp_instance().has_size(1, u8"Font buffer heap zero clear")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// mov rcx, {cs:hHeap}
				fontBufferHeapZeroClearHeapJmpAddress = Injector::GetBranchDestination(address + 0x0).as_int();
				// call {{cs:HeapAlloc}}
				fontBufferHeapZeroClearHeepAllocJmpAddress = Injector::GetBranchDestination(address + 0xC).as_int();
				// jz short loc_xxxxx
				fontBufferHeapZeroClearReturnAddress = address + 0x15;

				Injector::MakeJMP(address, fontBufferHeapZeroClear, true);
			}
			else {
				e.unmatch.fontBufferHeapZeroClearInjector = true;
			}
			break;
		default:
			e.version.fontBufferHeapZeroClearInjector = true;
		}

		return e;
	}

	DllError fontBufferClearInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			BytePattern::temp_instance().find_pattern("BA 88 3B 00 00");
			if (BytePattern::temp_instance().has_size(2, u8"Font buffer clear")) {
				// mov edx, 3B88h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else {
				e.unmatch.fontBufferClearInjector = true;
			}

			BytePattern::temp_instance().find_pattern("BA A0 3B 00 00");
			if (BytePattern::temp_instance().has_size(2, u8"Font buffer clear")) {
				// mov edx, 3BA0h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else {
				e.unmatch.fontBufferClearInjector = true;
			}
			break;
		default:
			e.version.fontBufferClearInjector = true;
		}

		return e;
	}

	DllError fontBufferExpansionInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			BytePattern::temp_instance().find_pattern("B9 88 3B 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"Font buffer expansion")) {
				// mov ecx, 3B88h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else {
				e.unmatch.fontBufferExpansionInjector = true;
			}

			BytePattern::temp_instance().find_pattern("B9 A0 3B 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"Font buffer expansion")) {
				// mov ecx, 3BA0h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else {
				e.unmatch.fontBufferExpansionInjector = true;
			}
			break;
		default:
			e.version.fontBufferExpansionInjector = true;
		}

		return e;
	}

	DllError fontSizeLimitInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_3_0:
			BytePattern::temp_instance().find_pattern("B9 00 00 00 02");
			// CKIII発売日に3.3.3自体がアップデートしたのでそれの対策
			if (BytePattern::temp_instance().count() == 1 || BytePattern::temp_instance().count() == 2 || BytePattern::temp_instance().count() == 3) {
				BytePattern::LoggingInfo("Font size limit:[OK]");

				// mov     ecx, 2000000h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x4), 0x04, true);
			}
			else {
				BytePattern::LoggingInfo("Font size limit:[NG]");
				e.unmatch.fontSizeLimitInjector = true;
			}

			BytePattern::temp_instance().find_pattern("48 8B F8 3D 00 00 00 02");
			if (BytePattern::temp_instance().has_size(1, u8"Font size limit")) {
				// mov     rdi, rax
				// cmp     eax, 2000000h / 2000000h byte = 33Mbyte -> 67Mbyte
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x7), 0x04, true);
			}
			else {
				e.unmatch.fontSizeLimitInjector = true;
			}

			BytePattern::temp_instance().find_pattern("4C 8B F0 3D 00 00 00 02");
			if (BytePattern::temp_instance().has_size(1, u8"Font size limit")) {
				// mov     r14, rax
				// cmp     eax, 2000000h / 2000000h byte = 33Mbyte -> 67Mbyte
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x7), 0x04, true);
			}
			else {
				e.unmatch.fontSizeLimitInjector = true;
			}
			break;
		default:
			e.version.fontSizeLimitInjector = true;
		}

		return e;
	}

	/*-----------------------------------------------*/

	DllError Init(RunOptions options) {
		DllError result = {};

		BytePattern::LoggingInfo(u8"font etc fix");

		/* ヒープゼロフラグの修正 */
		result |= fontBufferHeapZeroClearInjector(options);

		/* フォントバッファクリア */
		result |= fontBufferClearInjector(options);

		/* フォントバッファ拡張 */
		result |= fontBufferExpansionInjector(options);

		/* フォントサイズの拡張 */
		result |= fontSizeLimitInjector(options);

		return result;
	}
}