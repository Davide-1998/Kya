#ifndef _WINSAVEFILE_H
#define _WINSAVEFILE_H

// TODO // Rename file and structure, should work cross-platform

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>
#include <vector>

class WinSaveFile {
public:
  WinSaveFile(const std::filesystem::path &destination,
              const std::size_t &reserve = 0)
      : location(destination) {
    // If first time writing initialize the save file
    if (std::filesystem::exists(location.parent_path()) && !Exists()) {
      std::fstream stream(location, std::ios_base::out | std::ios_base::binary);
      stream.write("\0", reserve);
    }
  }

  /**
   * @brief Append data on the buffer, ready to be written when
   * Commit() is called
   *
   * @return true
   * @return false
   */
  template <typename T>
  std::enable_if_t<std::is_same_v<T, std::vector<char>> ||
                       std::is_same_v<T, std::string>,
                   bool>
  Write(const T &data) {
    buffer.insert(buffer.end(), data.begin(), data.end());
    return true;
  }

  bool Write(const std::string_view &data) {
    buffer.insert(buffer.end(), data.begin(), data.end());
    return true;
  }

  bool Write(const char *data) {
    return data == nullptr ? false : Write(std::string_view(data));
  }

  /**
   * @brief Check whether destination file already exists
   *
   * @return true
   * @return false
   */
  bool Exists() { return std::filesystem::exists(location); }

  /**
   * @brief Get savefile size if exists
   *
   * @return std::size_t Save File size if exists or 0 otherwise
   */
  std::size_t Size() {
    return Exists() ? std::filesystem::file_size(location) : 0;
  }

  /**
   * @brief Read content of saved file
   *
   * @param content
   * @return true File exists and has been correctly read
   * @return false Either file does not exist or Read operation failure
   */
  bool Read(std::string &content) {
    if (!Exists()) {
      return false;
    }

    const std::size_t read_amount = std::filesystem::file_size(location);
    content.resize(read_amount, '\0');
    std::fstream stream(location, std::ios_base::in | std::ios_base::binary);
    return stream.read(content.data(), read_amount).good();
  }

  /**
   * @brief Converts an std::string content to std::vector<char>
   * @details Example: WinSaveFile::StringToVecChar(std::string("Hello World"));
   *
   * @param data
   * @return std::vector<char>
   */
  static std::vector<char> StringToVecChar(const std::string &data) {
    std::vector<char> output;
    output.insert(output.begin(), data.begin(), data.end());
    return output;
  }

  /**
   * @brief Write the enqueued data from internal buffer to destination
   * @details Firstly read the saved data then try writing, if write fails
   * restore the content
   * @return true
   * @return false
   */
  bool Commit() {
    if (buffer.empty()) {
      return false;
    }

    std::string content;
    if (Exists() && !Read(content)) {
      return false; // Reading failed, thus writing may corrupt file if fails
    }

    std::fstream stream(location, std::ios_base::out | std::ios_base::trunc |
                                      std::ios_base::binary);
    if (stream.write(buffer.data(), buffer.size()).good()) {
      return true;
    } else {
      // May fail too
      stream.write(content.data(), content.size());
      return false;
    }
  }

private:
  // Filepath to save file
  std::filesystem::path location;

  // Used for Write operations: enqueues content until Commit() is called
  std::vector<char> buffer;
};

#endif // _WINSAVEFILE_H