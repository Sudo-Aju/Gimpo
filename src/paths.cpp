#include "paths.hpp"

#include <string>
#include <filesystem>

#ifdef __APPLE__

#include <mach-o/dyld.h>

std::filesystem::path getAssetPath()
{
    uint32_t size = 0;

    _NSGetExecutablePath(nullptr, &size);

    std::string buffer(size, '\0');

    _NSGetExecutablePath(buffer.data(), &size);

    return std::filesystem::path(buffer)
        .parent_path()
        .parent_path()
        .parent_path()
        / "Contents/Resources/Assets";
}

#elif defined(_WIN32)

#include <windows.h>

std::filesystem::path getAssetPath()
{
    wchar_t buffer[MAX_PATH];

    GetModuleFileNameW(
        nullptr,
        buffer,
        MAX_PATH
    );

    return std::filesystem::path(buffer)
        .parent_path()
        / "Assets";
}

#elif defined(__linux__)

#include <unistd.h>

std::filesystem::path getAssetPath()
{
    char buffer[4096];

    ssize_t length = readlink(
        "/proc/self/exe",
        buffer,
        sizeof(buffer) - 1
    );

    buffer[length] = '\0';

    return std::filesystem::path(buffer)
        .parent_path()
        / "Assets";
}

#endif