#include <gtest/gtest.h>
#include <windows.h>  // For GetFinalPathNameByHandle
#include <cstdio>
#include <io.h>  // for _get_osfhandle

int add(int a, int b) {
    return a + b;
}

TEST(FileTests, a01APIPrintTempPath) {
    // 获取 Windows 临时目录
    char tempPath[MAX_PATH];
    DWORD result = GetTempPathA(MAX_PATH, tempPath);
    printf("%s", tempPath);
}

TEST(FileTests, a01PrintCurrentPath) {
    char path[MAX_PATH + 1];
    char *cwd = getcwd(path, MAX_PATH);
    printf("Current working directory: %s\n", cwd);
}

void print_file_path(FILE *fp) {
    int fd = _fileno(fp);
    HANDLE hFile = (HANDLE) _get_osfhandle(fd);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("无效的句柄。\n");
        return;
    }

    char path[MAX_PATH];
    DWORD result = GetFinalPathNameByHandleA(hFile, path, MAX_PATH, FILE_NAME_NORMALIZED);
    if (result == 0) {
        printf("获取路径失败，错误码：%lu\n", GetLastError());
    } else {
        // 有可能路径前缀是 \\?\, 去掉它更友好
        if (strncmp(path, "\\\\?\\", 4) == 0) {
            printf("文件路径是：%s\n", path + 4);
        } else {
            printf("文件路径是：%s\n", path);
        }
    }
}

TEST(FileTests, a01PrintFilePath) {
    FILE *tmp;
    errno_t err = tmpfile_s(&tmp);
    if (err != 0 || tmp == NULL) {
        return;
    }
    print_file_path(tmp);
    // EXPECT_EQ(add(-2, -3), -5);
}

TEST(FileTestsTempFile, a02TempFileCreate) {
    FILE *tmp;
    errno_t err = tmpfile_s(&tmp);
    if (err != 0 || tmp == NULL) {
        return;
    }
    fprintf(tmp, "test temp data.\n");
    rewind(tmp);
    char buf[100];
    if (fgets(buf, sizeof(buf), tmp) != NULL) {
        printf("read buf: %s", buf);
    }
    fclose(tmp);
}

TEST(FileTestsTempFile, a02TempFileWrite) {
    char tmpName[] = "testFile_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd == -1) {
        perror("mkstemp failed");
        return;
    }
    printf("Temporary file path: %s", tmpName);
    const char *content = "test data!\n";
    write(fd, content, strlen(content));
    close(fd);
    unlink(tmpName);
}


TEST(FileTestsTempFile, a02TempDirectory) {
    // mktemp 不会实际创建目录，它只生成一个唯一的临时文件名（或目录名）
    char tmpDirName[] = "dir_XXXXXX";  // 模板尾部须含6个X
    if (_mktemp_s(tmpDirName, strlen(tmpDirName) + 1) != 0) {  // 生成唯一目录名
        std::cerr << "Failed to generate temp directory name" << std::endl;
        return;
    }

    // 创建临时目录
    if (_mkdir(tmpDirName) != 0) {
        std::cerr << "Failed to create temp directory" << std::endl;
        return;
    }
    std::cout << "Temp directory created: " << tmpDirName << std::endl;

    // 删除临时目录
    if (_rmdir(tmpDirName) != 0) {
        std::cerr << "Failed to remove temp directory" << std::endl;
        return;
    }
    std::cout << "Temp directory removed" << std::endl;
}
