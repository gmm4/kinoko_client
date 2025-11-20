#include "pch.h"
#include "hook.h"
#include "wvs/wvsapp.h"

#include <detours.h>
#include <chrono>
#include <mutex>
#include <windows.h>
#include <mmsystem.h> // 包含 timeGetTime 的声明
#pragma comment(lib, "winmm.lib")


// 关于慢动作的基础和特效配置
const float SLOW_MOTION_FACTOR = 3.0f;              // 慢动作因子，播放速度为 1/因子
//const wchar_t* SLOW_MOTION_EFFECT_UOL = L"skill/100.img/skill/1001004/CharLevel/25/effect";
const wchar_t* SLOW_MOTION_EFFECT_UOL = L"Effect/MapEff.img/BossDead";      // 慢动作特效UOL


// 实现慢动作的全局变量申明
bool g_bSlowMotion = false; // 全局开关
static DWORD g_dwLastRealTime = 0;
static DWORD g_dwLastFakeTime = 0;
static std::mutex g_mutex;
LPVOID pOriginalTimeGetTime = NULL;
static DWORD(WINAPI* OriginalTimeGetTime)(void) = NULL;


// 触发慢动作时调用的函数，开启慢动作开关
void __stdcall ApplySlowMotion() {

    g_bSlowMotion = !g_bSlowMotion;

}

// hook后的 timeGetTime 函数
DWORD WINAPI Hooked_TimeGetTime() {
    std::lock_guard<std::mutex> lock(g_mutex);

    // 1. 调用原始函数
    DWORD dwRealTime = OriginalTimeGetTime();

    if (!g_bSlowMotion) {
        // 正常模式：重置计时器并返回真实时间
        g_dwLastRealTime = dwRealTime;
        g_dwLastFakeTime = dwRealTime;
        return dwRealTime;
    }

    // --- 慢动作逻辑 ---

    DWORD dwRealDelta = dwRealTime - g_dwLastRealTime;

    // 计算慢动作时间差 (除以因子)
    DWORD dwFakeDelta = (DWORD)((float)dwRealDelta / SLOW_MOTION_FACTOR);

    DWORD dwFakeTime = g_dwLastFakeTime + dwFakeDelta;

    // 更新状态并返回
    g_dwLastRealTime = dwRealTime;
    g_dwLastFakeTime = dwFakeTime;

    return dwFakeTime;
}


// 动态搜索 timeGetTime 在内存中的加载位置并hook
void initial_timeGetTime_hook() {


    pOriginalTimeGetTime = GetProcAddress(GetModuleHandleA("winmm.dll"), "timeGetTime");

    // 使用 Detours 库进行 Hook
    // 目标地址是 pOriginalTimeGetTime，Trampoline 指针是 OriginalTimeGetTime，Detour 函数是 Hooked_TimeGetTime
    if (DetourTransactionBegin() != NO_ERROR ||
            DetourUpdateThread(GetCurrentThread()) != NO_ERROR) {
        // 处理错误
        return;
    }

    // De`tourAttach 需要 void** ppTarget 和 void* pDetour
    // 注意：我们将 pOriginalTimeGetTime 的地址（LPVOID*）传递给 Detours 作为目标
    // Detours 会将 timeGetTime 的原始地址替换为 Hooked_TimeGetTime
    // 并将 Trampoline 地址写入 OriginalTimeGetTime

    // 确保 DetoursAttach 的第一个参数是 &pOriginalTimeGetTime（即 LPVOID*）
    // 第二个参数是 Hooked_TimeGetTime 函数指针
    DetourAttach(&(LPVOID&)pOriginalTimeGetTime, &Hooked_TimeGetTime);

    // 将 Trampoline 指针 OriginalTimeGetTime 赋给 pOriginalTimeGetTime 变量
    // 这行代码应该在 DetourAttach 内部完成，但在 Detours API 中，
    // 我们通常传递一个指向函数指针的指针 (void**)，让 Detours 完成赋值。

    // 由于您提供了一个自定义宏，让我们使用标准 Detours 的方式：

    // 确保 OriginalTimeGetTime 是一个指向函数的静态指针
    static DWORD(WINAPI * pTargetTimeGetTime)(void) = NULL;
    pTargetTimeGetTime = (DWORD(WINAPI*)(void))pOriginalTimeGetTime;

    DetourAttach(&(PVOID&)pTargetTimeGetTime, Hooked_TimeGetTime);

    // 完成 Hook
    DetourTransactionCommit();

    // 在 Hook 完成后，将 Detours 创建的 Trampoline 地址赋给我们的全局变量
    OriginalTimeGetTime = pTargetTimeGetTime;

}


// 主函数
void AttachSlowMotion() {

    void initial_timeGetTime_hook();

}