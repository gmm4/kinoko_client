#include "pch.h"
#include "hook.h"
#include "config.h"
#include "ztl/ztl.h"
#include <cstdint>
#include "uiReplacement.h"

const bool bTranslateChinese = true; // Translate StringPool into Chinese

#define REPLACE_STRING(INDEX, NEW_STRING) \
    do { \
        static char sEncoded[GetLength(NEW_STRING) + 2]; \
        EncodeString(INDEX, NEW_STRING, sEncoded); \
    } while (0)


class StringPool {
public:
    class Key {
    public:
        ZArray<uint8_t> m_aKey;
    };
    static_assert(sizeof(Key) == 0x4);
};

static auto StringPool__Key__ctor = reinterpret_cast<void (__thiscall*)(StringPool::Key*, const uint8_t*, uint32_t, uint32_t)>(0x00746470);

static auto StringPool__ms_aKey = reinterpret_cast<const uint8_t*>(0x00B98830);
static auto StringPool__ms_aString = reinterpret_cast<const char**>(0x00C5A878);

constexpr size_t GetLength(const char* s) {
    size_t n = 0;
    while (s[n]) {
        ++n;
    }
    return n;
}

void EncodeString(int nIdx, const char* sSource, char* sDestination) {
    StringPool::Key keygen;
    StringPool__Key__ctor(&keygen, StringPool__ms_aKey, 0x10, 0);
    size_t n = strlen(sSource);
    for (size_t i = 0; i < n; ++i) {
        uint8_t key = keygen.m_aKey[i % 0x10];
        sDestination[i + 1] = sSource[i] ^ key;
        if (sSource[i] == key) {
            sDestination[i + 1] = key;
        }
    }
    sDestination[0] = 0;
    sDestination[n + 1] = 0;
    StringPool__ms_aString[nIdx] = sDestination;
}


void AttachStringPoolMod() {
    REPLACE_STRING(2585, CONFIG_REGISTRY_KEY);
    REPLACE_STRING(2948, CONFIG_VERSION_STRING);

    if (bTranslateChinese == true) {

        REPLACE_STRING(11, "设置");
        REPLACE_STRING(12, "新手");
        REPLACE_STRING(13, "战士");
        REPLACE_STRING(14, "弓箭手");
        REPLACE_STRING(15, "飞侠");
        REPLACE_STRING(16, "海盗");
        REPLACE_STRING(17, "管理员");
        REPLACE_STRING(18, "骑士团");
        REPLACE_STRING(19, "可以");
        REPLACE_STRING(20, "超级GM");
        REPLACE_STRING(22, "战士");
        REPLACE_STRING(23, "剑客");
        REPLACE_STRING(24, "勇士");
        REPLACE_STRING(25, "英雄");
        REPLACE_STRING(26, "准骑士");
        REPLACE_STRING(27, "骑士");
        REPLACE_STRING(28, "圣骑士");
        REPLACE_STRING(29, "枪战士");
        REPLACE_STRING(30, "龙骑士");
        REPLACE_STRING(31, "黑骑士");
        REPLACE_STRING(32, "法师");
        REPLACE_STRING(33, "巫师");
        REPLACE_STRING(34, "魔导师");
        REPLACE_STRING(35, "法师(火,毒)");
        REPLACE_STRING(36, "巫师(火,毒)");
        REPLACE_STRING(37, "魔导师(火,毒)");
        REPLACE_STRING(38, "法师(冰,雷)");
        REPLACE_STRING(39, "巫师(冰,雷)");
        REPLACE_STRING(40, "魔导师(冰,雷)");
        REPLACE_STRING(41, "牧师");
        REPLACE_STRING(42, "祭司");
        REPLACE_STRING(43, "主教");
        REPLACE_STRING(44, "弓箭手");
        REPLACE_STRING(45, "猎人");
        REPLACE_STRING(46, "射手");
        REPLACE_STRING(47, "神射手");
        REPLACE_STRING(48, "弩弓手");
        REPLACE_STRING(49, "游侠");
        REPLACE_STRING(50, "箭神");
        REPLACE_STRING(51, "飞侠");
        REPLACE_STRING(52, "刺客");
        REPLACE_STRING(53, "无影人");
        REPLACE_STRING(54, "隐士");
        REPLACE_STRING(55, "侠客");
        REPLACE_STRING(56, "独行客");
        REPLACE_STRING(57, "侠盗");
        REPLACE_STRING(58, "拳手");
        REPLACE_STRING(59, "斗士");
        REPLACE_STRING(60, "冲锋队长");
        REPLACE_STRING(61, "火枪手");
        REPLACE_STRING(62, "大副");
        REPLACE_STRING(63, "船长");
        REPLACE_STRING(64, "初心者");
        REPLACE_STRING(65, "当前服务器人数已满\r\n请稍后再试");
        REPLACE_STRING(66, "死亡状态中不能执行该操作");

        REPLACE_STRING(709, "固有道具");
        REPLACE_STRING(710, "任务道具");
        REPLACE_STRING(711, "组队任务道具");
        REPLACE_STRING(712, "不可交换");
        REPLACE_STRING(713, "仅可交换1次");
        REPLACE_STRING(716, "装备后无法交换");

        REPLACE_STRING(4517, "扩展道具栏");
        REPLACE_STRING(4518, "缩小道具栏");
        REPLACE_STRING(4520, "扩展道具栏上限");

        REPLACE_STRING(5305, "丢出多少金币？（若金币被其他玩家拾取，将会损失一部分）");
    }

    // StringPool Replacement for UI from post-bb to pre-bb
    if (isSetPrebbUI == true) {
        REPLACE_STRING(6497, "UI/Basic.img/BtCancel2"); // UI/Basic.img/BtCancel4
        REPLACE_STRING(6498, "UI/Basic.img/BtClose");   // UI/Basic.img/BtClose3
        REPLACE_STRING(6499, "UI/Basic.img/BtOK2");     // UI/Basic.img/BtOK4

        /*
        // 【注意】关于以下 Notice6 的UI替换，目前仍需要更多优化，关注c/s_box的交互
        REPLACE_STRING(6500, "UI/Basic.img/Notice4/box");     // UI/Basic.img/Notice6/box
        REPLACE_STRING(6501, "UI/Basic.img/Notice4/box2");     // UI/Basic.img/Notice6/box2
        REPLACE_STRING(6502, "UI/Basic.img/Notice4/c");     // UI/Basic.img/Notice6/c
        REPLACE_STRING(6503, "UI/Basic.img/Notice4/c_box");     // UI/Basic.img/Notice6/c_box
        //REPLACE_STRING(6504, "UI/Basic.img/Notice6/message/0");     // UI/Basic.img/Notice6/message/0
        //REPLACE_STRING(6505, "UI/Basic.img/Notice6/message/1");     // UI/Basic.img/Notice6/message/1
        //REPLACE_STRING(6506, "UI/Basic.img/Notice6/message/2");     // UI/Basic.img/Notice6/message/2
        //REPLACE_STRING(6507, "UI/Basic.img/Notice6/message/3");     // UI/Basic.img/Notice6/message/3
        //REPLACE_STRING(6508, "UI/Basic.img/Notice6/message/4");     // UI/Basic.img/Notice6/message/4
        REPLACE_STRING(6509, "UI/Basic.img/Notice4/s");     // UI/Basic.img/Notice6/s
        REPLACE_STRING(6510, "UI/Basic.img/Notice4/s_box");     // UI/Basic.img/Notice6/s_box
        REPLACE_STRING(6511, "UI/Basic.img/Notice4/t");     // UI/Basic.img/Notice6/t
        */
    }
}
