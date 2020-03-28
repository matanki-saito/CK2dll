#pragma once
#pragma once
#include "pch.h"

enum Ck2Version {
	UNKNOWN = 0,
	v3_3_0 = 330
};

typedef UINT64 DllErrorCode;

struct DllError {
	union {
		DllErrorCode code0;
		struct {
			bool timeout : 1;
			bool waitFailed : 1;
			bool proccessFaild : 1;
		};
	} mod;

	union {
		DllErrorCode code1;
		struct {
			bool fontBufferExpansionInjector : 1;
			bool fontSizeLimitInjector : 1;
			bool fontBufferHeapZeroClearInjector : 1;
			bool debugProc1Injector : 1;
			bool fontBufferClearInjector : 1;
			bool mainTextProc1Injector : 1;
			bool mainTextProc2Injector : 1;
			bool mainTextProc3Injector : 1;
			bool mainTextProc4Injector : 1;
			bool tooltipAndButtonProc1Injector : 1;
			bool tooltipAndButtonProc2Injector : 1;
			bool tooltipAndButtonProc3Injector : 1;
			bool tooltipAndButtonProc4Injector : 1;
			bool tooltipAndButtonProc5Injector : 1;
			bool tooltipAndButtonProc6Injector : 1;
			bool mapViewProc1Injector : 1;
			bool mapViewProc2Injector : 1;
			bool mapViewProc3Injector : 1;
			bool mapViewProc4Injector : 1;
			bool mapAdjustmentProc1Injector : 1;
			bool mapAdjustmentProc2Injector : 1;
			bool mapAdjustmentProc3Injector : 1;
			bool mapAdjustmentProc4Injector : 1;
			bool mapJustifyProc1Injector : 1;
			bool mapJustifyProc2Injector : 1;
			bool mapJustifyProc3Injector : 1;
			bool mapJustifyProc4Injector : 1;
			bool eventDialog1Injector : 1;
			bool eventDialog2Injector : 1;
			bool mapPopupProc1Injector : 1;
			bool mapPopupProc2Injector : 1;
			bool mapPopupProc3Injector : 1;
			bool listFieldAdjustmentProc1Injector : 1;
			bool listFieldAdjustmentProc2Injector : 1;
			bool listFieldAdjustmentProc3Injector : 1;
			bool fileSaveProc1Injector : 1;
			bool fileSaveProc2Injector : 1;
			bool fileSaveProc3Injector : 1;
			bool fileSaveProc4Injector : 1;
			bool fileSaveProc5Injector : 1;
			bool dateProc1Injector : 1;
			bool mapNudgeViewProc1Injector : 1;
			bool mainTextAdjustmentProc1Injector : 1;
			bool mainTextAdjustmentProc2Injector : 1;
			bool mainTextAdjustmentProc3Injector : 1;
			bool mainTextAdjustmentProc4Injector : 1;
			bool mainTextAdjustmentProc5Injector : 1;
			bool mainTextAdjustmentProc6Injector : 1;
			bool decorativeLetterProc1Injector : 1;
			bool decorativeLetterProc2Injector : 1;
			bool decorativeLetterProc3Injector : 1;
			bool decorativeLetterProc4Injector : 1;
			bool decorativeLetterProc5Injector : 1;
			bool decorativeLetterProc6Injector : 1;
			bool decorativeLetterProc7Injector : 1;
			bool decorativeLetterProc8Injector : 1;
			bool decorativeLetterProc9Injector : 1;
			bool decorativeLetterProc10Injector : 1;
			bool decorativeLetterProc11Injector : 1;

			bool mainTextOverflowProc1Injector : 1;

			bool general : 1;
		};
	} version;

	union {
		DllErrorCode code2;
		struct {
			bool fontBufferExpansionInjector : 1;
			bool fontSizeLimitInjector : 1;
			bool fontBufferHeapZeroClearInjector : 1;
			bool debugProc1Injector : 1;
			bool fontBufferClearInjector : 1;
			bool mainTextProc1Injector : 1;
			bool mainTextProc2Injector : 1;
			bool mainTextProc3Injector : 1;
			bool mainTextProc3Injector2 : 1;
			bool mainTextProc4Injector : 1;
			bool tooltipAndButtonProc1Injector : 1;
			bool tooltipAndButtonProc2Injector : 1;
			bool tooltipAndButtonProc3Injector : 1;
			bool tooltipAndButtonProc4Injector : 1;
			bool tooltipAndButtonProc5Injector : 1;
			bool tooltipAndButtonProc6Injector : 1;
			bool mapViewProc1Injector : 1;
			bool mapViewProc2Injector : 1;
			bool mapViewProc3Injector : 1;
			bool mapViewProc4Injector : 1;
			bool mapAdjustmentProc1Injector : 1;
			bool mapAdjustmentProc2Injector : 1;
			bool mapAdjustmentProc3Injector : 1;
			bool mapAdjustmentProc4Injector : 1;
			bool mapJustifyProc1Injector : 1;
			bool mapJustifyProc2Injector : 1;
			bool mapJustifyProc3Injector : 1;
			bool mapJustifyProc4Injector : 1;
			bool eventDialog1Injector : 1;
			bool eventDialog2Injector : 1;
			bool mapPopupProc1Injector : 1;
			bool mapPopupProc2Injector : 1;
			bool mapPopupProc3Injector : 1;
			bool listFieldAdjustmentProc1Injector : 1;
			bool listFieldAdjustmentProc2Injector : 1;
			bool listFieldAdjustmentProc3Injector : 1;
			bool fileSaveProc1Injector : 1;
			bool fileSaveProc2Injector : 1;
			bool fileSaveProc3Injector : 1;
			bool fileSaveProc4Injector : 1;
			bool fileSaveProc5Injector : 1;
			bool dateProc1Injector : 1;
			bool mapNudgeViewProc1Injector : 1;
			bool mainTextAdjustmentProc1Injector : 1;
			bool mainTextAdjustmentProc2Injector : 1;
			bool mainTextAdjustmentProc3Injector : 1;
			bool mainTextAdjustmentProc4Injector : 1;
			bool mainTextAdjustmentProc5Injector : 1;
			bool mainTextAdjustmentProc6Injector : 1;
			bool decorativeLetterProc1Injector : 1;
			bool decorativeLetterProc2Injector : 1;
			bool decorativeLetterProc3Injector : 1;
			bool decorativeLetterProc4Injector : 1;
			bool decorativeLetterProc5Injector : 1;
			bool decorativeLetterProc6Injector : 1;
			bool decorativeLetterProc7Injector : 1;
			bool decorativeLetterProc8Injector : 1;
			bool decorativeLetterProc9Injector : 1;
			bool decorativeLetterProc10Injector : 1;
			bool decorativeLetterProc11Injector : 1;

			bool mainTextOverflowProc1Injector : 1;

			bool general : 1;
		};
	} unmatch;

	void operator |= (DllError e)
	{
		this->mod.code0 |= e.mod.code0;
		this->version.code1 |= e.version.code1;
		this->unmatch.code2 |= e.unmatch.code2;
	}
};

typedef struct {
	union {
		char text[0x10];
		char* p;
	} t;
	UINT64 len;
	UINT64 len2;

	std::string getString() {
		if (len >= 0x10) {
			return std::string(t.p);
		}
		else {
			return std::string(t.text);
		}
	}

	void setString(std::string* src) {

		len = src->length();

		if (len >= 0x10) {
			len2 = 0x1F;

			auto p = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len + 3);
			if (p != NULL) {
				memcpy(p, src->c_str(), len);
				t.p = p;
			}
		}
		else {
			memcpy(t.text, src->c_str(), len);
		}
	}
} ParadoxTextObject;

typedef struct {
	Ck2Version version;
	bool test;
} RunOptions;

namespace Version {
	void GetVersionFromExe(RunOptions* option);
}

namespace Ini {
	void GetOptionsFromIni(RunOptions* option);
}

namespace Debug {
	DllError Init(RunOptions option);
}

namespace Validator {
	void Validate(DllError dllError, RunOptions options);
}

namespace Font {
	DllError Init(RunOptions option);
}

namespace MainText {
	DllError Init(RunOptions option);
}

namespace TooltipAndButton {
	DllError Init(RunOptions option);
}

namespace MapView {
	DllError Init(RunOptions option);
}

namespace MapAdjustment {
	DllError Init(RunOptions option);
}

namespace MapJustify {
	DllError Init(RunOptions option);
}

namespace MainTextOverflow {
	DllError Init(RunOptions option);
}

namespace MainTextAdjustment {
	DllError Init(RunOptions option);
}

namespace DecorativeLetter {
	DllError Init(RunOptions option);
}

namespace Date {
	DllError Init(RunOptions option);
}

namespace WordOrder {
	DllError Init(RunOptions option);
}

namespace Localize {
	DllError Init(RunOptions option);
}

namespace FileName {
	DllError Init(RunOptions option);
}