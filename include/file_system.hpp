/**
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @madahin
 */

#ifndef VFS_FILE_SYSTEM_HPP
#define VFS_FILE_SYSTEM_HPP

// C++ headers
#include <array>
#include <fstream>
#include <ios>
#include <limits>
#include <memory>
#include <string>

// C headers
#include <cstdint>
#include <cstring>

// project headers
#include "file.hpp"

namespace vfs
{

// Forward declaration
class file;
class folder;

class file_system
{
    friend class file;
    friend class folder;

public:
    file_system();
    file_system(const std::string& pPath);
    ~file_system();

    void open(const std::string& pPath);
    void close();

    bool is_open() const;
    const std::string& path() const;
    std::ios_base::iostate stream_state() const;

private:
    bool check_integrity();
    bool check_header();
    void init_file_system();
    bool is_new_file();

private:
    const std::string FILE_SYSTEM_HEADER = {'\x56', '\x46', '\x53', '\x34', '\x32', '\x34', '\x34', '\x32'}; // VFS42442
    const std::array<char, 3> PROJECT_VERSION = {VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH};
    bool mIsOpen;
    std::fstream mFileHandle;
    std::string mVfsFilePath;
    std::unique_ptr<file> mRootFolder;
};

}

#endif // VFS_FILE_SYSTEM_HPP

