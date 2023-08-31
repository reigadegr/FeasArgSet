#include "include/LockValue.h"
#include "include/function.h"
#include <fstream>
#include <sstream>
#include <thread>
std::string auto_define() {
    std::vector<std::string> nodes = {"/sys/module/perfmgr_mtk/parameters/perfmgr_enable",
                                      "/sys/module/bocchi_perfmgr/parameters/perfmgr_enable",
                                      "/sys/module/mtk_fpsgo/parameters/perfmgr_enable"};

    for (const auto &node : nodes) {
        if (access(node.c_str(), F_OK) == 0) {
            LOG("检测到节点: ", node, " 存在\n");
            return node;
        }
    }
    return "ReadFile";
}

bool write_struct(std::string switch_ctrl, struct FeasPath *p, const char *pathProfile) {

    if (switch_ctrl == "/sys/module/mtk_fpsgo/parameters/perfmgr_enable") {
        // LOG("开始记录");
        p->Feas_switch = "/sys/module/mtk_fpsgo/parameters/perfmgr_enable";
        p->Fps = "/sys/module/mtk_fpsgo/parameters/fixed_target_fps";
        p->scaling_a = "/sys/module/mtk_fpsgo/parameters/scaling_a";
        p->scaling_b = "/sys/module/mtk_fpsgo/parameters/scaling_b";
        return true;
    }

    if (switch_ctrl == "/sys/module/perfmgr_mtk/parameters/perfmgr_enable") {
        p->Feas_switch = "/sys/module/perfmgr_mtk/parameters/perfmgr_enable";
        p->Fps = "/sys/module/perfmgr_mtk/parameters/fixed_target_fps";
        p->scaling_a = "/sys/module/perfmgr_mtk/parameters/scaling_a";
        p->scaling_b = "/sys/module/perfmgr_mtk/parameters/scaling_b";
        return true;
    }

    if (switch_ctrl == "/sys/module/bocchi_perfmgr/parameters/perfmgr_enable") {
        p->Feas_switch = "/sys/module/bocchi_perfmgr/parameters/perfmgr_enable";
        p->Fps = "/sys/module/bocchi_perfmgr/parameters/fixed_target_fps";
        p->scaling_a = "/sys/module/bocchi_perfmgr/parameters/scaling_a";
        p->scaling_b = "/sys/module/bocchi_perfmgr/parameters/scaling_b";
        return true;
    }

    if (switch_ctrl == "ReadFile") {
        LOG("内置节点不存在，读取文件\n");
        // 实例化FeasPath的对象feaspath
        FeasPath feaspath;
        readPathProfile(pathProfile, &feaspath);
        check_path(&feaspath);
        return true;
    }

    return false;
}

void init_FeasNode() {
    FeasPath Pandora_mtk;
    Pandora_mtk.Feas_switch = "/sys/module/mtk_fpsgo/parameters/perfmgr_enable";
    Pandora_mtk.Fps = "/sys/module/mtk_fpsgo/parameters/fixed_target_fps";
    Pandora_mtk.scaling_a = "/sys/module/mtk_fpsgo/parameters/scaling_a";
    Pandora_mtk.scaling_b = "/sys/module/mtk_fpsgo/parameters/scaling_b";
    Feas_off(&Pandora_mtk);

    FeasPath Mi_Mtk_FEAS;
    Mi_Mtk_FEAS.Feas_switch = "/sys/module/perfmgr_mtk/parameters/perfmgr_enable";
    Mi_Mtk_FEAS.Fps = "/sys/module/perfmgr_mtk/parameters/fixed_target_fps";
    Mi_Mtk_FEAS.scaling_a = "/sys/module/perfmgr_mtk/parameters/scaling_a";
    Mi_Mtk_FEAS.scaling_b = "/sys/module/perfmgr_mtk/parameters/scaling_b";
    Feas_off(&Mi_Mtk_FEAS);

    FeasPath bocchi;
    bocchi.Feas_switch = "/sys/module/bocchi_perfmgr/parameters/perfmgr_enable";
    bocchi.Fps = "/sys/module/bocchi_perfmgr/parameters/fixed_target_fps";
    bocchi.scaling_a = "/sys/module/bocchi_perfmgr/parameters/scaling_a";
    bocchi.scaling_b = "/sys/module/bocchi_perfmgr/parameters/scaling_b";
    Feas_off(&Mi_Mtk_FEAS);
}
