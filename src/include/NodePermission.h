#pragma once

static void Permission_unlock(const std::string &path) {

    if (!std::filesystem::exists(path)) {
        LOG("Warning: ", path, " 不存在");
        return;
    }

    std::system(("umount " + path).c_str());

    chmod(path.c_str(), 0666);
}
