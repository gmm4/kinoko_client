#include "pch.h"
#include "hook.h"
#include "uiReplacement.h"



// Common CUIWnd
static void uiCUIWndReplacement() {

    // Base
    SmartPatchStr(0x00B4B658, L"UI/Basic.img/BtClose");     // UI/Basic.img/BtClose3

    /*
    // UtilDlgEx
    SmartPatchStr(0x00BA49AE, L"UI/Basic.img/BtCancel2");       // UI/Basic.img/BtCancel4
    SmartPatchStr(0x00BA49DE, L"UI/Basic.img/BtOK2");   // UI/Basic.img/BtOK4
    */

    /*
    // UtilDlgEx
    SmartPatchStr(0x00BAB220, L"UI/UIWindow.img/UtilDlgEx");
    SmartPatchStr(0x00BAB258, L"UI/UIWindow.img/UtilDlgEx_Pet/backgrnd");
    SmartPatchStr(0x00BAB2A8, L"UI/UIWindow2.img/UtilDlgEx_Avatar/backgrnd");
    SmartPatchStr(0x00BAB300, L"UI/UIWindow.img/UtilDlgEx/is");
    SmartPatchStr(0x00BAB33C, L"UI/UIWindow.img/UtilDlgEx/ic");
    SmartPatchStr(0x00BAB378, L"UI/UIWindow.img/UtilDlgEx/it");
    SmartPatchStr(0x00BAB3B4, L"UI/UIWindow.img/UtilDlgEx/s");
    SmartPatchStr(0x00BAB3F0, L"UI/UIWindow.img/UtilDlgEx/c");
    SmartPatchStr(0x00BAB42C, L"UI/UIWindow.img/UtilDlgEx/t");
    SmartPatchStr(0x00BAB468, L"UI/UIWindow.img/UtilDlgEx/line");
    SmartPatchStr(0x00BAB8B8, L"UI/UIWindow2.img/UtilDlgEx/dot1");
    SmartPatchStr(0x00BAB8F8, L"UI/UIWindow2.img/UtilDlgEx/dot0");
    SmartPatchStr(0x00BABB04, L"UI/UIWindow2.img/UtilDlgEx/bar");
    */

}

// Item Bag
static void uiItemReplacement() {

    Patch1(0x007CE552 + 1, 0x00); // bMultiBg set to false

    Patch1(0x007CCEED + 2, 0x9B); // Item BtClose OffsetX
    Patch1(0x007CCEE7 + 2, 0xAC); // Item BtClose OffsetY while expanded
    Patch1(0x007CBBD9 + 2, 0x9B); // Item BtClose OffsetX after Toggle
    Patch1(0x007CBBD3 + 2, 0xAC); // Item BtClose OffsetY while expanded after Toggle 

    SmartPatchStr(0x00B9D2E8, L"UI/UIWindow.img/Item/BtGather");
    SmartPatchStr(0x00B9D328, L"UI/UIWindow.img/Item/BtSort");
    PatchExtended(0x007CCD34, 7, "\x6A\x0C\x8B\x86\xD8\x0A\x00\x00\x83\xE8\x09\x50\x68\xD3\x07\x00\x00", 17);   // Set OffsetY/X of BtGather
    PatchExtended(0x007CCCF6, 7, "\x6A\x0C\x8B\x86\xD8\x0A\x00\x00\x83\xE8\x09\x50\x68\xD4\x07\x00\x00", 17);   // Set OffsetY/X of BtSort

    SmartPatchStr(0x00B9D364, L"UI/UIWindow.img/Item/backgrnd");
    SmartPatchStr(0x00B9D3A8, L"UI/UIWindow.img/Item/FullBackgrnd");
    Patch1(0x007CCF03 + 1, 0xAF);   // Item Backgrnd width
    Patch1(0x007CCEF9 + 1, 0xAC);   // Item Backgrnd width while expanded
    Patch1(0x007CCEFE + 1, 0x21);   // Item Backgrnd height
    Patch1(0x007CBBEF + 1, 0xAF);   // Item Backgrnd width after Toggle  
    Patch1(0x007CBBE5 + 1, 0xAC);   // Item Backgrnd width while expanded after Toggle  
    Patch1(0x007CBBEA + 1, 0x21);   // Item Backgrnd height after Toggle    

    SmartPatchStr(0x00B9D500, L"UI/UIWindow.img/Item/BtFull");
    SmartPatchStr(0x00B9D584, L"UI/UIWindow.img/Item/BtSmall");
    Patch1(0x007CEE2F + 1, 0x0C); // Item BtFull OffsetY
    PatchExtended(0x007CEE31, 8, "\x75\x0B\x68\x83\x00\x00\x00\x68\x0D\xEF\x7C\x00\xC3\x68\x2F\x02\x00\x00",18);    // Set Item BtFull/BtSmall OffsetX

    SmartPatchStr(0x00B9D3F0, L"UI/UIWindow.img/Item/activeIcon");
    PatchExtended(0x007CBF78, 6, "\x6B\xC9\x22\x83\xC1\x32\x89\xD3", 8);    // Align Item Rect Offset Y
    PatchExtended(0x007CBF85, 7, "\x8D\x04\x85\x08\x00\x00\x00\x8D\x1C\x9B\x03\xC3", 12);   // Align Item Rect Offset X

    SmartPatchStr(0x00B9D438, L"UI/UIWindow.img/Item/New/inventory");
    SmartPatchStr(0x00B9D480, L"UI/UIWindow.img/Item/New/Tab0");
    SmartPatchStr(0x00B9D4C0, L"UI/UIWindow.img/Item/New/Tab1");
    
    SmartPatchStr(0x00B9D540, L"UI/UIWindow.img/Item/BtCashshop");
    PatchExtended(0x007CEE9F, 6, "\x6A\x00\x68\x12\x01\x00\x00\x68\x1D\x02\x00\x00", 12); // Set OffsetY/X of UIWindow.img/Item/BtCashshop
    
    SmartPatchStr(0x00B9D5C0, L"UI/UIWindow.img/Item/BtCoin");
    PatchExtended(0x007CEDBD, 9, "\x68\x0B\x01\x00\x00\x6A\x08\x68\xD2\x07\x00\x00", 12); // Set OffsetY/X of UIWindow.img/Item/BtCoin
    Patch1(0x007CD09D + 1, 0x88);   // Set OffsetX of Meso number
    Patch1(0x007CD16D + 1, 0x0B);   // Set OffsetY of Meso number
        
    SmartPatchStr(0x00B9D600, L"UI/UIWindow.img/Item/Tab/enabled");   
    SmartPatchStr(0x00B9D648, L"UI/UIWindow.img/Item/Tab/disabled");
    Patch1(0x007CE899 + 1, 0x3);    // Item Tab OffsetX
    Patch1(0x007CE897 + 1, 0x17);   // Item Tab OffsetY
    Patch1(0x007CE892 + 1, 0xAA);   // Item Tab Width
    Patch1(0x007CE822 + 3, 0x00);   // Item Tab Gap Space
    PatchJmp(0x007CBAF4, 0x007CBB0B);   // Ignore Item Tab exchange between Set-up and Etc
    PatchJmp(0x007CBACA, 0x007CBAEB);   // Ignore Item Tab exchange between Set-up and Etc
    PatchStr(0x007CD985, "\x6B\xC9\x22\x90\x90\x83\xE9\x1F");
    PatchExtended(0x007CDD09, 8, "\x8B\x4C\x24\x60\x8B\x54\x24\x4C\x83\xE9\x04", 11);

    SmartPatchStr(0x00B9D690, L"UI/UIWindow.img/Item/disabled");

    Patch1(0x007CECA3 + 1, 3);  // Set CCtrlStrollBar Type to VScr4
}

// StatusBar
static void uiStatusBarReplacement() {

    SmartPatchStr(0x00BA5990, L"UI/StatusBar.img/base/backgrnd");   // UI/StatusBar2.img/mainBar/backgrnd

    SmartPatchStr(0x00BA5940, L"UI/StatusBar.img/base/backgrnd2"); // UI/StatusBar2.img/mainBar/lvBacktrnd
    PatchStr(0x0087D85E, "\xEB\x23");   // Ignore UI/StatusBar2.img/mainBar/lvCover
    SmartPatchStr(0x00BA59D8, L"UI/Basic.img/LevelNo"); // UI/StatusBar2.img/mainBar/lvNumber
    Patch1(0x00873662 + 1, 0x32);   // Set offsetX of Level Number
    Patch1(0x0087365D + 1, 0x29);   // Set offsetY of Level Number
    Patch1(0x00873645 + 1, 0x01);   // Set gap space of Level Number

    Patch1(0x00873714 + 1, 0x21);   // Set offsetY of Job Name
    Patch1(0x0087371E + 1, 0x58);   // Set offsetX of Job Name
    Patch1(0x00873C6D + 1, 0x58);   // Set offsetX of Character Name

    



}

// Call all UI Replacement functions
void AttachUIReplacement() {
    if (isSetPrebbUI) {
        uiCUIWndReplacement();
        uiItemReplacement();
        //uiStatusBarReplacement(); // δ���
    }
}