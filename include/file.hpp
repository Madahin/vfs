/**
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @madahin
 */

#ifndef VFS_FILE_HPP
#define VFS_FILE_HPP

#include <cstdint>

#include "file_system.hpp"

namespace vfs
{

class file_system;

class file
{
private:
    file(file_system& pFs);

private:
    enum NODE_TYPE : std::uint8_t
    {
        FILE_HEADER,
        FILE_DATA,
        FILE_CHECKSUM
    };

    file_system& mFileSystem;

private:

};

}

#endif // VFS_FILE
