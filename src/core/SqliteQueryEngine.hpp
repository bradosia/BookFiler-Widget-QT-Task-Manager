#if DEPENDENCY_SQLITE
#ifndef BOOKFILER_SQLITEQUERYENGINE_H
#define BOOKFILER_SQLITEQUERYENGINE_H

// C++
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

/* sqlite3 3.33.0
 * License: PublicDomain
 */
#include <sqlite3.h>

namespace bookfiler {
namespace core {

typedef std::map<std::string, std::vector<std::string>> TableContent;
constexpr char COMPLETE_TABLE[] = "SELECT * FROM taskList;";
class SQliteQueryEngine {
public:
  static TableContent updateContent(std::shared_ptr<sqlite3> database,
                                    void *instance_ptr) {

    SQliteQueryEngine *engine_ptr = (SQliteQueryEngine *)instance_ptr;
    engine_ptr->content = TableContent{};
    if (database) {
      SqliteQuery(database, COMPLETE_TABLE, instance_ptr);
    }
    return engine_ptr->content;
  }
  TableContent content;

private:
  void contentCallback(int argc, char **argv, char **azColName) {
    if (argc < 0) {
      return;
    }
    for (int i = 0; i < argc; ++i) {
      std::string column_name{azColName[i]};
      std::string field_value{"NULL"};
      if (argv[i]) {
        field_value = std::string(argv[i]);
      }
      content[column_name].push_back(field_value);
    }
  }

  static int SqliteQuery(std::shared_ptr<sqlite3> database, const char *query,
                         void *instance_ptr) {
    char errorMessage[1024];
    char *buf = errorMessage;
    int ret = sqlite3_exec(database.get(), query, staticContentCallback,
                           instance_ptr, &buf);
    if (ret != 0) {
      std::cerr << errorMessage;
    }
    return ret;
  }
  static int staticContentCallback(void *instance_ptr, int argc, char **argv,
                                   char **azColName) {
    SQliteQueryEngine *engine = (SQliteQueryEngine *)instance_ptr;
    engine->contentCallback(argc, argv, azColName);
    return 0;
  }
};
} // namespace core
} // namespace bookfiler

#endif // BOOKFILER_SQLITEQUERYENGINE_H
#endif
