/**
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @madahin
 */

#include "file_system.hpp"

namespace vfs
{

/*********************************************
 * PUBLIC METHODE                            *
 *********************************************/

file_system::file_system() :
    mIsOpen(false),
    mFileHandle(),
    mVfsFilePath()
{

}

file_system::file_system(const std::string& pPath) :
    file_system()
{
    open(pPath);
}

file_system::~file_system()
{
    close();
}

void file_system::open(const std::string& pPath)
{
    if(mIsOpen)
    {
        close();
    }

    mFileHandle.open(pPath, std::ios::in | std::ios::out | std::ios::binary);

    if(mFileHandle.is_open())
    {
        if(is_new_file())
        {
            init_file_system();
        }

        if(check_integrity())
        {
            mIsOpen = true;
            mVfsFilePath = pPath;
        }
    }
}

void file_system::close()
{
    if(!mIsOpen)
    {
        return;
    }

    mFileHandle.close();
    mVfsFilePath.clear();
}

bool file_system::is_open() const
{
    return mIsOpen;
}

const std::string& file_system::path() const
{
    return mVfsFilePath;
}

std::ios_base::iostate file_system::stream_state() const
{
    return mFileHandle.rdstate();
}


/*********************************************
 * PRIVATE METHODE                           *
 *********************************************/

bool file_system::check_integrity()
{
    return check_header();
}

bool file_system::check_header()
{
    int headerComparaison{0};
    std::unique_ptr<char> headerBuffer(new char[FILE_SYSTEM_HEADER.size()]);

    // Make sure we are at the begining
    mFileHandle.seekg(0, std::ios::end);
    // Read header into buffer
    mFileHandle.read(headerBuffer.get(), static_cast<std::streamsize>(FILE_SYSTEM_HEADER.size()));
    // Return to the begining
    mFileHandle.seekg(0, std::ios::end);

    headerComparaison = std::strncmp(headerBuffer.get(), FILE_SYSTEM_HEADER.c_str(), FILE_SYSTEM_HEADER.size());

    return headerComparaison == 0;
}

void file_system::init_file_system()
{
    // Make sure we are at the begining
    mFileHandle.seekg(0, std::ios::end);
    // Write header so we can recognise it regardless of its extension.
    mFileHandle.write(FILE_SYSTEM_HEADER.c_str(), static_cast<std::streamsize>(FILE_SYSTEM_HEADER.size()));
    //Write the project version, in case of compatibility problems
    mFileHandle.write(PROJECT_VERSION.data(), static_cast<std::streamsize>(PROJECT_VERSION.size()));
}

bool file_system::is_new_file()
{
    // See https://stackoverflow.com/a/2409527
    std::streampos fileSize = mFileHandle.tellg();
    fileSize = mFileHandle.tellg();
    mFileHandle.seekg(0, std::ios::end);
    fileSize = mFileHandle.tellg() - fileSize;
    return fileSize == 0;
}

}
