#include "include/Check.h"
#include "include/LockValue.h"
#include "include/NodePermission.h"
#include "include/UnLockValue.hpp"
#include "include/function.h"
#if 0
struct FeasPath {
public:
    std::string Feas_switch;
    std::string Fps;
    std::string scaling_a;
    std::string scaling_b;
    std::string normal_frame_keep_count;
    std::string min_freq_limit_level;
    std::string max_freq_limit_level;
} __attribute__((aligned(128)));

#endif
// 进入游戏，锁定节点值
void Feas_on(const struct listGame *o, const struct FeasPath *p) {
    lock_val(1, p->Feas_switch);
    lock_val(o->fixed_target_fps, p->Fps);
    lock_val(o->scaling_a, p->scaling_a);
    lock_val(o->scaling_b, p->scaling_b);
    lock_val(o->normal_frame_keep_count, p->normal_frame_keep_count);
    lock_val(o->min_freq_limit_level, p->min_freq_limit_level);
    lock_val(o->max_freq_limit_level, p->max_freq_limit_level);
}

void Feas_off(const struct FeasPath *p) {
    // 退出游戏，恢复节点值，解锁feas节点权限
    UnLock_val(0, p->Feas_switch);
    UnLock_val(-1, p->Fps);
    UnLock_val(0, p->scaling_a);
    UnLock_val(0, p->scaling_b);
    UnLock_val(0, p->normal_frame_keep_count);
    UnLock_val(0, p->min_freq_limit_level);
    UnLock_val(0, p->max_freq_limit_level);
}
void Allow_system_operation() {
    // 进入游戏，解锁scaling_max_freq节点权限
    for (int i = 0; i < 8; i++) {
        Permission_unlock("/sys/devices/system/cpu/cpufreq/policy" +
                          std::to_string(i) + "/scaling_max_freq");
    }
}

void set_gov(std::string &gov) {
    for (int i = 0; i < 8; i++) {
        lock_val(gov, "/sys/devices/system/cpu/cpufreq/policy" +
                          std::to_string(i) + "/scaling_governor");
        check_val(gov, "/sys/devices/system/cpu/cpufreq/policy" +
                           std::to_string(i) + "/scaling_governor");
    }
}

void set_middle_big_gov(std::string &gov) {
    // 设置游戏中中大核调速器
    for (int i = 1; i < 8; i++) {
        lock_val(gov, "/sys/devices/system/cpu/cpufreq/policy" +
                          std::to_string(i) + "/scaling_governor");
        check_val(gov, "/sys/devices/system/cpu/cpufreq/policy" +
                           std::to_string(i) + "/scaling_governor");
    }
}

// Recover the scaling_max_freq and scaling_min_freq from cpu_info_max_freq and
// cpu_info_min_freq
void recover_freq() {
    for (int i = 0; i < 8; i++) {
        Get1To2("/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) +
                    "/cpuinfo_max_freq",
                "/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) +
                    "/scaling_max_freq");
        Get1To2("/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) +
                    "/cpuinfo_min_freq",
                "/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) +
                    "/scaling_min_freq");
        Permission_unlock("/sys/devices/system/cpu/cpufreq/policy" +
                          std::to_string(i) + "/scaling_max_freq");
    }
}
auto AutoNode(FeasPath &feaspath) -> bool {
    if (!check_path(&feaspath)) {
        mk_node(FindPerfmgrName("/sys/module", "perfmgr_enable", "/parameters"),
                &feaspath);
        if (!check_path(&feaspath)) {
            LOG("配置文件有误，且无法自动生成节点，请修改配置文件后使用");
            LOG("进程已结束");
            return false;
        }
        LOG("自动生成节点成功");
        return true;
    }
    LOG("节点设置全部正确");

    return true;
}
