#include "file_system.hpp"

namespace vfs
{

file_system::file_system() :
    mIsOpen(false),
    mVfsFilePath()
{

}

file_system::file_system(const std::string& pPath) :
    file_system()
{
    mVfsFilePath = pPath;
}

file_system::~file_system()
{
    close();
}

void file_system::open(const std::string& pPath)
{
    if(mIsOpen) close();

    mVfsFilePath = pPath;
}

void file_system::close()
{
    if(!mIsOpen) return;
}

bool file_system::is_open() const
{
    return mIsOpen;
}

}
