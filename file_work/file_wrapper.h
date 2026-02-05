#ifndef NAVAL_WARFARE_FILE_WORK_FILE_WRAPPER_H_
#define NAVAL_WARFARE_FILE_WORK_FILE_WRAPPER_H_

#include <fstream>
#include <stdexcept>

using namespace std;

class FileWrapper {
 public:
  FileWrapper(const string& filename, ios_base::openmode mode = ios::in | ios::out);
  ~FileWrapper();
  void close();
  string get_file_line();
  ofstream& stream();
 private:
  fstream file;
};

#endif //NAVAL_WARFARE_FILE_WORK_FILE_WRAPPER_H_
