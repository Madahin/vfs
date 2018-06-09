#ifndef VFS_FILE
#define VFS_FILE

namespace vfs
{

class file_system;

class file
{
private:
    file(file_system& pFs);

private:
    file_system& mFileSystem;
};

}

#endif // VFS_FILE
