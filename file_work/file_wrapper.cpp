#include "file_wrapper.h"

FileWrapper::FileWrapper(const string& filename, std::ios_base::openmode mode) {
  file.open(filename, mode);
  if (!file.is_open()) {
    throw runtime_error("Failed to open file: " + filename);
  }
}

FileWrapper::~FileWrapper() {
  if (file.is_open()) {
    file.close();
  }
}

void FileWrapper::close() {
  if (file.is_open()) {
    file.close();
  }
}

string FileWrapper::get_file_line() {
  string line;
  file >> line;

}

ofstream& FileWrapper::stream() {
  return file;
}