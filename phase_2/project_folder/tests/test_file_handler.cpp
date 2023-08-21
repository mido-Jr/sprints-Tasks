// tests/test_file_handler.cpp

#include <gtest/gtest.h>
#include "FileHandler.h"

TEST(FileHandlerTest, GetFileList) {
FileHandler fileHandler;
std::vector<std::string> fileList = fileHandler.getFileList("/path/to/directory");

// Add assertions based on your expected behavior
ASSERT_FALSE(fileList.empty());
ASSERT_EQ(fileList.size(), 3); // Adjust the expected size as needed
}

TEST(FileHandlerTest, GetFileContent) {
FileHandler fileHandler;
std::string content = fileHandler.getFileContent("/path/to/file.txt");

// Add assertions based on your expected behavior
ASSERT_FALSE(content.empty());
ASSERT_EQ(content.substr(0, 5), "Hello"); // Adjust the expected content as needed
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
