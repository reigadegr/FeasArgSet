#pragma once
template <typename T>
void UnLock_val(T value,const std::string &path){
    const char *TmpPath = path.c_str();
   if (!std::filesystem::exists(path)) {
        //LOG("Warning: ", path, " 不存在");
        return;
    }

    std::system(("umount " + path + " 2>/dev/null").c_str());

    // check value
    std::ifstream test(path);
    if (test.is_open()) {
        T temp;
        test >> temp;
        test.close();

        if (temp == value) {
            return;
        }
    }
    // check done

    // chown(TmpPath, 0, 0);
    chmod(TmpPath, 0666);
    // target_file:path 对象

    std::ofstream target_file(path, std::ios::out | std::ios::trunc);
    if (!target_file.is_open()) {
        std::cerr << "无法打开文件进行写操作: " << path << std::endl;
        return;
    }

    target_file << value;
    target_file.close();
}
