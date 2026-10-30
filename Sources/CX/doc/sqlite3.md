/*
 SQLite支持3种线程模式：
 　　
 SQLITE_THREADSAFE=0.
 单线程：这种模式下，没有进行互斥，多线程使用不安全。禁用所有的mutex锁，并发使用时会出错。当SQLite编译时加了SQLITE_THREADSAFE=0参数，或者在初始化SQLite前调用sqlite3_config(SQLITE_CONFIG_SINGLETHREAD)时启用。
 　　
 SQLITE_THREADSAFE=2.
 多线程：这种模式下，只要一个数据库连接不被多个线程同时使用就是安全的。源码中是启用bCoreMutex，禁用bFullMutex。实际上就是禁用数据库连接和prepared statement(准备好的语句)上的锁，因此不能在多个线程中并发使用同一个数据库连接或prepared statement。当SQLite编译时加了SQLITE_THREADSAFE=2参数时默认启用。若SQLITE_THREADSAFE不为0，可以在初始化SQLite前，调用sqlite3_config(SQLITE_CONFIG_MULTITHREAD)启用;或者在创建数据库连接时，设置SQLITE_OPEN_NOMUTEX flag。
 　　
 SQLITE_THREADSAFE=1.
 串行：sqlite是线程安全的。启用所有的锁，包括bCoreMutex和bFullMutex 。因为数据库连接和prepared statement都已加锁，所以多线程使用这些对象时没法并发，也就变成串行了。当SQLite编译时加了SQLITE_THREADSAFE =1参数时默认启用。若SQLITE_THREADSAFE不为0，可以在初始化SQLite前，调用sqlite3_config(SQLITE_CONFIG_SERIALIZED)启用;或者在创建数据库连接时，设置SQLITE_OPEN_FULLMUTEX flag  。
在Windows和Linux上， 已编译的好的二进制发行版中都是1
iOS 上是2
*/

\#define SQLITE_THREADSAFE 2

## version

version:  "3.32.0"
source:  "2020-02-18 19:49:48 9469f36ac89e4b75d0ab25fefbeff25201992c53141da915dcaa017083cab6db"