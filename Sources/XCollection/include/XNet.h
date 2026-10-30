
#ifndef XNet_h
#define XNet_h

#if defined(__cplusplus)
extern "C" {
#endif

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/sysctl.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <sys/stat.h>

#if __has_include(<CX/CXBase.h>)
#include <CX/CXBase.h>
#else
#include "CXBase.h"
#endif

typedef enum {
    XSocketAddressTypeV4 = 1,
    XSocketAddressTypeUnix = 2,
    XSocketAddressTypeV6 = 3,
} XSocketAddressType_e;

typedef union {
    struct sockaddr_in address4;
    struct sockaddr_un addressUnix;
    struct sockaddr_in6 address6;
} XSocketAddress_u;

typedef struct {
    XSocketAddressType_e type;
    XSocketAddress_u content;
} XSocketAddress_s;


typedef struct __XIPAddress {
    uint8_t content[16];
} XIPAddress_t;


extern void XIPAddressInit4(XIPAddress_t * _Nonnull address, const struct sockaddr_in * _Nonnull sockaddress);
extern void XIPAddressInit6(XIPAddress_t * _Nonnull address, const struct sockaddr_in6 * _Nonnull sockaddress);


extern bool_t XIPAddressIsZero(const XIPAddress_t * _Nonnull address);
extern bool_t XIPAddressIsEqual(const XIPAddress_t * _Nonnull lhs, const XIPAddress_t * _Nonnull rhs);
extern bool_t XIPAddressIsIPv6(const XIPAddress_t * _Nonnull address);



//SO_RCVBUF选项必须在connect之前设置；对于服务器，SO_RCVBUF选项必须在listen前设置。因为TCP的窗口规模选项是在建立连接时用SYN与对方互换得到的。
//二、对于server端的socket一定要在listen之间设置缓冲区大小，因为，accept时新产生的socket会继承监听socket的缓冲区大小。对于client端的socket一定要在connet之前设置缓冲区大小，因为connet时需要进行三次握手过程，会通知对方自己的窗口大小。在connet之后再设置缓冲区，已经没有什么意义。


int XSocketSetReadBufferSize(int fd, int size);

int XSocketSetWriteBufferSize(int fd, int size);

int XSocketSetPortReusedable(int socketfd);

int XSocketSetAddressReusedable(int socketfd);

int XSocketSetNoSIGPIPE(int socketfd);

void XSocketSetNonBlock(int socketfd, bool_t state);
bool_t XSocketGetNonBlock(int socketfd);

int XSocket(int domain, int type, int protocol);
void XSocketClose(int fd);

int XAccept(int socket, struct sockaddr *__restrict _Nonnull address, socklen_t *__restrict _Nonnull address_len);

/// 返回值 < 0 error,
ssize_t XSocketRead(int fd, void * _Nonnull buffer, size_t size);

/// 返回值 < 0 error,
ssize_t XSocketWrite(int fd, void * _Nonnull buffer, size_t size);

/// 返回值 < 0 error,
ssize_t XSocketSendFile(int socket, int fileFd, off_t offset, size_t size);


//     struct stat st; socket 信息
/*
 int fd = open("/path/to/file", O_RDONLY); // 打开文件获取文件描述符
     if (fd == -1) {
         perror("open");
         return 1;
     }
  
     struct stat st;
     if (fstat(fd, &st) == -1) {
         perror("fstat");
         return 1;
     }
  
     switch (st.st_mode & S_IFMT) {
         case S_IFREG:  printf("普通文件\n");  break;
         case S_IFDIR:  printf("目录文件\n");  break;
         case S_IFBLK:  printf("块设备文件\n");  break;
         case S_IFCHR:  printf("字符设备文件\n");  break;
         case S_IFIFO:  printf("管道或FIFO\n");  break;
         case S_IFSOCK: printf("套接字\n");  break;
         case S_IFLNK:  printf("符号链接\n");  break;
         default:       printf("未知类型\n");  break;
     }
 */



#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XNet_h */
