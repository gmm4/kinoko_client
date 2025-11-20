#include "pch.h"
#include "hook.h"
#include "wvs/wvsapp.h"
#include "common/cuistatusbar.h"
#include "common/dbbasic.h"
#include "ztl/zalloc.h"

// CUIStatusBar::ChatLogAdd
static auto oriCUIStatusBarChatLogAdd = reinterpret_cast<void(__thiscall*)(CUIStatusBar*, const char*, int, int, int, ZRef<GW_ItemSlotBase>)>(0x0087AEC0);

void __stdcall ApplyF12Quest() {
   

    std::string logContent = "测试内容";
    ZRef<GW_ItemSlotBase> emptyItem;
    oriCUIStatusBarChatLogAdd(CUIStatusBar::GetInstance(), logContent.c_str(), 12, -1, 0, emptyItem);
     
}

static uintptr_t f12_hook_jmp = 0x00937026;
static uintptr_t f12_hook_ret = 0x0093702B;
DWORD UseFuncKeyMapped = 0x00932E20;

void __declspec(naked) f12_hook() {
    __asm {
        pushfd
        pushad

        mov     eax, [ esp + 0x74 ]
        cmp     eax, 0x7B
        jnz     skip_end
        call    ApplyF12Quest

        skip_end:
        popad
        popfd
        call    UseFuncKeyMapped
        jmp     [ f12_hook_ret ]
    }
}



void AttachF12test() {
   
    PatchJmp(f12_hook_jmp, reinterpret_cast<uintptr_t>(&f12_hook));  
}