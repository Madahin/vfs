/**
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @madahin
 */

#ifndef VFS_FOLDER_HPP
#define VFS_FOLDER_HPP

#include <array>
#include <vector>

#include <cstdint>

#include "file_system.hpp"

namespace vfs
{

class file_system;

class folder
{
private:
    folder(file_system& pFs);

private:
    file_system& mFileSystem;

private:
    struct folder_node
    {
        std::uint8_t mNameSize;
        std::string mName;
        std::uint32_t mNodeNumber;
        std::vector<std::uint64_t> mNodeAdress;
        std::array<std::uint8_t, 40> mChecksum;
    };
};

}

#endif // VFS_FOLDER_HPP

