#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include <string>

#include "file.hpp"

namespace vfs
{

// Forward declaration
class file;

class file_system
{
    friend class file;

public:
    file_system();
    file_system(const std::string& pPath);
    ~file_system();

    void open(const std::string& pPath);
    void close();

    bool is_open() const;

private:
    bool mIsOpen;
    std::string mVfsFilePath;
};

}

#endif // FILE_SYSTEM_HPP

