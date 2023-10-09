#ifndef NODEPERMISSION_H
#define NODEPERMISSION_H

#pragma once

static void Permission_unlock(const std::string &path) {

    if (access(path.c_str(), F_OK) == -1) {
        return;
    }

    chmod(path.c_str(), 0666);
}

#endif
