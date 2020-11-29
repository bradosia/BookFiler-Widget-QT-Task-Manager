# BookFiler Widget w/ QT: Task Manager Widget
This is a QT5 widget that creates a task list to monitor task progress. This widget uses a `sqlite3` backend.

# Usage Instructions

Connect to your database:
```cpp
sqlite3 *dbPtr = nullptr;
sqlite3_open("myDatabase.db", &dbPtr);
// Using shared pointers when possible
std::shared_ptr<sqlite3> database(nullptr);
database.reset(dbPtr, sqlite3_close);
```

Create the tree widget and set the database data
```cpp
std::shared_ptr<bookfiler::widget::TreeImpl> treeWidget =
      std::make_shared<bookfiler::widget::TreeImpl>();
treeWidget->setData(database, "taskList");
treeWidget->update();
```

## Sqlite3 Table format
The default table create statement is shown below. The Table name and column names may be different, but the user must explicitly map the names.
```sql
CREATE TABLE "taskList" (
	"id"	INTEGER NOT NULL,
	"parentId"	INTEGER NOT NULL,
	"partsDone"	INTEGER,
	"partsTotal"	INTEGER,
	"timeElapsed"	INTEGER,
	"timeRemaining"	INTEGER,
	"timeTotal"	INTEGER,
	"CanCancel"	INTEGER NOT NULL,
	"IsCancel"	INTEGER NOT NULL,
	"CanPause"	INTEGER NOT NULL,
	"IsPause"	INTEGER NOT NULL,
	"status"	INTEGER,
	"IsSelected"	INTEGER,
	"title"	TEXT,
	"description"	TEXT,
	PRIMARY KEY("id" AUTOINCREMENT)
)
```

# Build Instructions

## Windows - MinGW-w64
Install MSYS2<BR>
Then, install GCC, cmake, git and dependencies. Confirmed working with Windows 10 as of 11/19/2020.
```shell
pacman -Syu
pacman -S mingw-w64-x86_64-gcc git make mingw-w64-x86_64-cmake
pacman -Rns cmake
# restart MSYS2 so that we use the mingw cmake
pacman -S mingw-w64-x86_64-boost mingw-w64-x86_64-sqlite3
```
Build:
```shell
git clone https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget
cd BookFiler-Module-HTTP
mkdir build
cd build
cmake -G "MSYS Makefiles" ../
make
```

## Linux Ubuntu
Install GCC, cmake, git and dependencies. Confirmed working with Ubuntu 20.04 as of 11/8/2020.
```shell
sudo apt-get update
sudo apt install build-essential gcc-multilib g++-multilib cmake git
sudo apt install libboost-all-dev mingw-w64-x86_64-sqlite3
```
Build:
```shell
git clone https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget
cd BookFiler-Module-HTTP
mkdir build
cd build
cmake ../
make
```

# Developers

[Developer Notes](/dev/readme.md)

