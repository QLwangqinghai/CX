
#include "XNet.h"
#include <fcntl.h>

int XSocketSetReadBufferSize(int fd, int size) {
    return setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
}

int XSocketSetWriteBufferSize(int fd, int size) {
    return setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size));
}

int XSocketSetPortReusedable(int socketfd) {
    int on = 1;
    return setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(int));
}
int XSocketSetAddressReusedable(int socketfd) {
    int on = 1;
    return setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
}
int XSocketSetNoSIGPIPE(int socketfd) {
    int on = 1;
    
#if !CX_TARGET_OS_LINUX

    // Set the socket to ignore SIGPIPE to avoid dying on interrupted connections...
    //    Note: Linux does not support the SO_NOSIGPIPE option. Instead, we use the
    //          MSG_NOSIGNAL flags passed to send.  See the writeData() functions below.
    return setsockopt(socketfd, SOL_SOCKET, SO_NOSIGPIPE, &on, sizeof(int));
#endif
    return 0;
}

void XSocketSetNonBlock(int socketfd, bool_t state) {
    int flags = fcntl(socketfd, F_GETFL, 0);
    int newFlag = flags;
    if (state) {
        newFlag = flags | O_NONBLOCK;
    } else {
        newFlag = flags & (~O_NONBLOCK);
    }
    int fresult = fcntl(socketfd, F_SETFL, newFlag);
    XAssert(fresult != -1, "");
}

bool_t XSocketGetNonBlock(int socketfd) {
    int flags = fcntl(socketfd, F_GETFL, 0);
    return (flags & O_NONBLOCK) == O_NONBLOCK;
}

int XSocket(int domain, int type, int protocol) {
    
    int fd = socket(domain, type, protocol);
    if (fd >= 0) {
        XSocketSetNoSIGPIPE(fd);
        XLog("socket create: %d", fd);
    }
    return fd;
}
void XSocketClose(int fd) {
    int result = close(fd);
    XAssert(0 == result, "");
    XLog("socket close: %d", fd);
}


int XAccept(int socket, struct sockaddr *__restrict address, socklen_t *__restrict address_len) {
    while (true) {
        int fd = accept(socket, address, address_len);
        if (fd == -1) {
            if (errno == EINTR) {
                // 应该重试
                continue;
            } else if (errno == EWOULDBLOCK) {
                // 没有可用的链接
                
            }
            return fd;
        }
        XSocketSetNoSIGPIPE(fd);
        XLog("socket accept: %d", fd);
        return fd;
    }
    return -1;
}

/// 返回值 < 0 error,
ssize_t XSocketRead(int fd, void * _Nonnull buffer, size_t size) {
    ssize_t result = read(fd, buffer, size);
    if (result < 0) {
        if (errno == EAGAIN || errno == EINTR) {
            result = 0;
        }
    } else if (result == 0) {
        return -1;
    }
    return result;
}

/// 返回值 < 0 error,
ssize_t XSocketWrite(int fd, void * _Nonnull buffer, size_t size) {
    ssize_t result = write(fd, buffer, size);
    if (result < 0) {
        if (errno == EAGAIN || errno == EINTR) {
            result = 0;
        }
    }
    return result;
}

ssize_t XSocketSendFile(int socket, int fileFd, off_t offset, size_t size) {

#if __APPLE__
    off_t length = size;
    int ret = sendfile(socket, fileFd, offset, &length, NULL, 0);
    if (ret == -1) {
        if (errno == EAGAIN || errno == EINTR) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return length;
    }
#elif defined (__FreeBSD__)
    off_t length = size;
    int ret = sendfile(socket, fileFd, offset, length, NULL, &length, 0);
    if (ret == -1) {
        if (errno == EAGAIN || errno == EINTR) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return length;
    }
#elif __ANDROID__ || __linux__
    
    off_t aoffset = offset;
    ssize_t ret = sendfile(socket, fileFd, &aoffset, size);
    if (ret == -1) {
        if (errno == EAGAIN || errno == EINTR) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return ret;
    }
#else
    XAbort("");
#endif
}

//int _XConnectorPollWaitIO(XConnectorPollRef _Nonnull tp) {
//    //毫秒
//    int count = epoll_wait(poll, tp->events, XConnectorEventBufferCapacity, 0);
//    XAssert(count >= 0, "");
//    return count;
//}
//
//void _XConnectorPollMergeEvents(XConnectorPollRef _Nonnull tp, XEventPollEvent_s * _Nonnull e) {
//
//    XIOEventMask_es mask = XIOEventMaskNone;
//
//    _Bool error = false;
//    if (e->events & EPOLLIN) {
//        mask |= XIOEventMaskReadable;
//    }
//    if (e->events & EPOLLOUT) {
//        mask |= XIOEventMaskWritable
//    };
//    if (e->events & EPOLLERR) {
//        error = true;
//        mask |= (XIOEventMaskError | XIOEventMaskWritable);
//    };
//    if (e->events & EPOLLHUP) {
//        error = true;
//        mask |= XIOEventMaskReadWritable
//    };
//    if (e->events & EPOLLRDHUP) {
//        error = true;
//        mask |= XIOEventMaskReadWritable
//    };
//    if (mask != XIOEventMaskNone) {
//        XConnectorRef Event = e->data.ptr;
//        _XConnectorPollSendEvents(tp, Event, mask);
//    }
//}
//
//#endif
//
//
//
//
//#if CORE_EVENT_USE_KQUEUE
//
///*
// int pio[2] = {};
// int result = pipe(pio);
//
// if (0 != result) {
//     fprintf(stderr, "XConnectorPollCreate error %s; \n", strerror(errno));
//     fflush(stderr);
//     abort();
// }
//
// int flags = fcntl(pio[0], F_GETFL, 0);
// int fresult = fcntl(pio[0], F_SETFL, flags | O_NONBLOCK);
// assert(fresult == 0);
//
// int flags1 = fcntl(pio[1], F_GETFL, 0);
// int fresult1 = fcntl(pio[1], F_SETFL, flags1 | O_NONBLOCK);
// assert(fresult1 == 0);
// eventPoll->pread = pio[0];
// eventPoll->pwrite = pio[1];
// */
//
////ev timer https://blog.csdn.net/Namcodream521/article/details/83032615
//
//void XConnectorPollRegistConnector(XConnectorPollRef _Nonnull tp, XConnectorRef _Nonnull t) {
//    assert(tp);
//    assert(t);
//    int fd = t->id.fd;
//    XConnectorPollRef eventPoll = tp;
//    uint16_t op = EV_ADD;
//    XEventSourceIOCore_s ke;
//    EV_SET(&ke, fd, EVFILT_WRITE, op, 0, 0, NULL);
//    if (xpoll_event(eventPoll->fd, &ke, 1, NULL, 0, NULL) == -1) {
//        if (op == EV_DELETE && errno == ENOENT) {
//
//        } else {
//            XConnectorPollLogError();
//            abort();
//        }
//    }
//
//}
//
//void XConnectorPollRemoveConnector(XConnectorPollRef _Nonnull tp, XConnectorRef _Nonnull t) {
//    assert(tp);
//    assert(t);
//    int fd = t->id.fd;
//    XConnectorPollRef eventPoll = tp;
//    uint16_t op = EV_DELETE;
//    XEventSourceIOCore_s ke;
//    EV_SET(&ke, fd, EVFILT_WRITE, op, 0, 0, NULL);
//    if (xpoll_event(eventPoll->fd, &ke, 1, NULL, 0, NULL) == -1) {
//        if (op == EV_DELETE && errno == ENOENT) {
//
//        } else {
//            XConnectorPollLogError();
//            abort();
//        }
//    }
//}
//
//int _XConnectorPollWaitIO(XConnectorPollRef _Nonnull tp) {
//    struct timespec tv = {};
//    tv.tv_sec = 0;
//    tv.tv_nsec = 0;
//    int count = xpoll_event(tp->fd, NULL, 0, tp->events, XConnectorEventBufferCapacity, &tv);
//    if (count < 0) {
//        XLog("%s\n", strerror(errno));
//    }
//    XAssert(count >= 0, "");
//    return count;
//}
//
//void _XConnectorPollMergeEvents(XConnectorPollRef _Nonnull tp, XEventPollEvent_s * _Nonnull e) {
//    if (e->filter == EVFILT_READ) {
//        XConnectorRef Event = e->udata;
//        _XConnectorPollSendEvents(tp, Event, XIOEventMaskReadable);
//    } else if (e->filter == EVFILT_WRITE) {
//        XConnectorRef Event = e->udata;
//        _XConnectorPollSendEvents(tp, Event, XIOEventMaskWritable);
//    }
//}
//
//#endif

    
    
//    if (errno == EINTR) {
//        // 应该重试
//        continue;
//    } else if (errno == EINPROGRESS) {
//        // 没有可用的链接
//        
//    }
//    fd_set set;
//    FD_ZERO(&set);
//    FD_SET(socket, &set);
//    __DARWIN_FD_SETSIZE;
//    FD_SETSIZE;
//}
//
//int XConnect(int socket, const struct sockaddr * _Nonnull address, socklen_t addressLen) {
//    // 超时时间
//    struct timeval tm;
//    tm.tv_sec  = 5;
//    tm.tv_usec = 0;
//    int ret = -1;
//    bool_t old = XSocketGetNonBlock(socket);
//    if (!old) {
//        XSocketSetNonBlock(socket, true);
//    }
//  
//    // 尝试去连接服务端
//    if (-1 != connect(socket, address, addressLen)) {
//        ret = 1; // 连接成功
//    } else {
//        int fd = XPollC
//        
//        fd_set set;
//        FD_ZERO(&set);
//        FD_SET(socket, &set);
//  
//        if (select(-1, NULL, &set, NULL, &tm) <= 0) {
//            ret = -1; // 有错误(select错误或者超时)
//        } else {
//            int error = -1;
//            int optLen = sizeof(int);
//            getsockopt(sockClient, SOL_SOCKET, SO_ERROR, (char*)&error, &optLen);
//              
//            // 之所以下面的程序不写成三目运算符的形式， 是为了更直观， 便于注释
//            if (0 != error)
//            {
//                ret = -1; // 有错误
//            }
//            else
//            {
//                ret = 1;  // 无错误
//            }
//        }
//    }
//  
//  
//    // 设回为阻塞socket
//    iMode = 0;
//    ioctlsocket(sockClient, FIONBIO, (u_long FAR*)&iMode); //设置为阻塞模式
//  
//  
//    // connect状态
//    XLog("ret is %d\n", ret);
//  
//  
//    // 发送数据到服务端测试以下
//    if(1 == ret)
//    {
//        send(sockClient, "hello world", strlen("hello world") + 1, 0);
//    }
//  
//  
//    // 释放网络连接
//    closesocket(sockClient);
//    WSACleanup();
//  
//    return 0;
//}



//XOConnectorPoll _Nonnull XOConnectorPollCreate(XObjectOption option, XPtr _Nonnull owner) {
//    XAssert(owner, "owner null");
//
//    XConnectorPoll_s * poll = XAllocate(sizeof(XConnectorPoll_s));
//    XAssert(poll, "");
//    memset(poll, 0, sizeof(XConnectorPoll_s));
//
//    int pfd = xpoll_create();
//    XAssert(pfd != -1, "socket create error!");
//
//    poll->fd = pfd;
//    poll->owner = owner;
//
//    poll->source = _XOConnectorPollCreate(option, pfd, poll, _XConnectorPollDestroy, _XConnectorPollOnSourceCallback);
//
//    return poll->source;
//}
//
//void _XConnectorPollSendEvents(XConnectorPollRef _Nonnull tp, XConnectorRef _Nonnull t, XIOEventMask_es events) {
////    tp->EventType.handleEvent(tp->source, tp->owner, Event, events);
//
//    XPtr handler = t->handler;
//    XPtr context = t->context;
//    XConnectorHandleEvent_f callback = t->callback;
//    int fd = t->id.fd;
//    callback(handler, context, fd, events);
//}
//
//void _XConnectorPollMergeEvents(XConnectorPollRef _Nonnull tp, XEventPollEvent_s * _Nonnull e);
//
//XConnectorRef _Nullable _XConnectorPollGetConnector(XConnectorPollRef _Nonnull tp, const XConnectorId_s * _Nonnull id) {
//    if (id->location >= XConnectorPollCapacity) {
//        return NULL;
//    }
//    XConnectorRef result = &(tp->connectors[id->location]);
//    if (result->id.fd == id->fd && result->id.sequence == id->sequence && 1 == result->isActive) {
//        return result;
//    } else {
//        return NULL;
//    }
//}
//
//void _XConnectorPollDispatchIOEvent(XConnectorPollRef _Nonnull tp, int count) {
//    XEventPollEvent_s * events = tp->events;
//
//    for (int j=0; j<count; j++) {
//        XEventPollEvent_s * e = events + j;
//        _XConnectorPollMergeEvents(tp, e);
//    }
//}
//
//size_t _XConnectorPollDispatchTimeoutEvent(XConnectorPollRef _Nonnull tp) {
//    XConnectorRef t = NULL;
//    microsecond_t now = XDeviceUptime();
//    size_t count = 0;
//    while (NULL != (t = _XConnectorPollPopTopTimeoutConnector(tp, now))) {
//        XIOEventMask_es events = XIOEventMaskNone;
//        const microsecond_t * read = NULL;
//        const microsecond_t * write = NULL;
//
//        if (t->timeout <= now) {
//            _XConnectorPollUpdateConnectorTimeout(tp, t, XConnectorTimeMax);
//            _XConnectorPollSendEvents(tp, t, XIOEventMaskWriteTimeout);
//        }
//        count += 1;
//    }
//    return count;
//}
//
//
//microsecond_t _XOConnectorPollProgress(XConnectorPollRef _Nonnull tp) {
//    // io events
//    int count = _XConnectorPollWaitIO(tp);
//    _XConnectorPollDispatchIOEvent(tp, count);
//    while (0 != _XConnectorPollDispatchTimeoutEvent(tp)) {};
//
//    if (tp->timerCount > 0) {
//        XConnectorRef t = tp->timers[0];
//
//        // TODO:
//        return t->timeout;
//    } else {
//        return MICROSECOND_MAX;
//    }
//}

//
//#if CORE_EVENT_USE_EPOLL
//
//
//
//void XConnectorPollRegistConnector(XConnectorPollRef _Nonnull tp, XConnectorRef _Nonnull t) {
//    assert(tp);
//    XConnectorPollRef eventPoll = tp;
//    int fd = t->id.fd;
//
//    XEventPollEvent_s ee = {0}; /* avoid valgrind warning */
//    /* If the fd was already monitored for some event, we need a MOD
//     * operation. Otherwise we need an ADD operation. */
//
//    int op = EPOLL_CTL_ADD;
//    ee.events = EPOLLERR | EPOLLHUP | EPOLLRDHUP | EPOLLOUT;
//    ee.data.fd = fd;
//    if (epoll_ctl(eventPoll->fd,op,fd,&ee) < 0) {
//        XConnectorPollLogError();
//        abort();
//    };
//}
//void XConnectorPollRemoveConnector(XConnectorPollRef _Nonnull tp, XConnectorRef _Nonnull t) {
//    assert(tp);
//    XConnectorPollRef eventPoll = tp;
//    int fd = t->id.fd;
//
//    XEventPollEvent_s ee = {0}; /* avoid valgrind warning */
//    /* If the fd was already monitored for some event, we need a MOD
//     * operation. Otherwise we need an ADD operation. */
//    int op = EPOLL_CTL_DEL;
//    ee.data.fd = fd;
//    if (epoll_ctl(eventPoll->fd,op,fd,&ee) < 0) {
//        XConnectorPollLogError();
//        abort();
//    };
//}
//int _XConnectorPollWaitIO(XConnectorPollRef _Nonnull tp) {
//    //毫秒
//    int count = epoll_wait(tp->fd, tp->events, XConnectorEventBufferCapacity, 0);
//    XAssert(count >= 0, "");
//    return count;
//}
//
//void _XConnectorPollMergeEvents(XConnectorPollRef _Nonnull tp, XEventPollEvent_s * _Nonnull e) {
//
//    XIOEventMask_es mask = XIOEventMaskNone;
//
//    _Bool error = false;
//    if (e->events & EPOLLIN) {
//        mask |= XIOEventMaskReadable;
//    }
//    if (e->events & EPOLLOUT) {
//        mask |= XIOEventMaskWritable
//    };
//    if (e->events & EPOLLERR) {
//        error = true;
//        mask |= (XIOEventMaskError | XIOEventMaskWritable);
//    };
//    if (e->events & EPOLLHUP) {
//        error = true;
//        mask |= XIOEventMaskReadWritable
//    };
//    if (e->events & EPOLLRDHUP) {
//        error = true;
//        mask |= XIOEventMaskReadWritable
//    };
//    if (mask != XIOEventMaskNone) {
//        XConnectorRef Event = e->data.ptr;
//        _XConnectorPollSendEvents(tp, Event, mask);
//    }
//}
//
//#endif
//
//
//
//
//#if CORE_EVENT_USE_KQUEUE
//
///*
// int pio[2] = {};
// int result = pipe(pio);
//
// if (0 != result) {
//     fprintf(stderr, "XConnectorPollCreate error %s; \n", strerror(errno));
//     fflush(stderr);
//     abort();
// }
//
// int flags = fcntl(pio[0], F_GETFL, 0);
// int fresult = fcntl(pio[0], F_SETFL, flags | O_NONBLOCK);
// assert(fresult == 0);
//
// int flags1 = fcntl(pio[1], F_GETFL, 0);
// int fresult1 = fcntl(pio[1], F_SETFL, flags1 | O_NONBLOCK);
// assert(fresult1 == 0);
// eventPoll->pread = pio[0];
// eventPoll->pwrite = pio[1];
// */
//
////ev timer https://blog.csdn.net/Namcodream521/article/details/83032615
//
//void XConnectorPollRegistConnector(XConnectorPollRef _Nonnull tp, XConnectorRef _Nonnull t) {
//    assert(tp);
//    assert(t);
//    int fd = t->id.fd;
//    XConnectorPollRef eventPoll = tp;
//    uint16_t op = EV_ADD;
//    XEventSourceIOCore_s ke;
//    EV_SET(&ke, fd, EVFILT_WRITE, op, 0, 0, NULL);
//    if (xpoll_event(eventPoll->fd, &ke, 1, NULL, 0, NULL) == -1) {
//        if (op == EV_DELETE && errno == ENOENT) {
//
//        } else {
//            XConnectorPollLogError();
//            abort();
//        }
//    }
//
//}
//
//void XConnectorPollRemoveConnector(XConnectorPollRef _Nonnull tp, XConnectorRef _Nonnull t) {
//    assert(tp);
//    assert(t);
//    int fd = t->id.fd;
//    XConnectorPollRef eventPoll = tp;
//    uint16_t op = EV_DELETE;
//    XEventSourceIOCore_s ke;
//    EV_SET(&ke, fd, EVFILT_WRITE, op, 0, 0, NULL);
//    if (xpoll_event(eventPoll->fd, &ke, 1, NULL, 0, NULL) == -1) {
//        if (op == EV_DELETE && errno == ENOENT) {
//
//        } else {
//            XConnectorPollLogError();
//            abort();
//        }
//    }
//}
//
//int _XConnectorPollWaitIO(XConnectorPollRef _Nonnull tp) {
//    struct timespec tv = {};
//    tv.tv_sec = 0;
//    tv.tv_nsec = 0;
//    int count = xpoll_event(tp->fd, NULL, 0, tp->events, XConnectorEventBufferCapacity, &tv);
//    if (count < 0) {
//        XLog("%s\n", strerror(errno));
//    }
//    XAssert(count >= 0, "");
//    return count;
//}
//
//void _XConnectorPollMergeEvents(XConnectorPollRef _Nonnull tp, XEventPollEvent_s * _Nonnull e) {
//    if (e->filter == EVFILT_READ) {
//        XConnectorRef Event = e->udata;
//        _XConnectorPollSendEvents(tp, Event, XIOEventMaskReadable);
//    } else if (e->filter == EVFILT_WRITE) {
//        XConnectorRef Event = e->udata;
//        _XConnectorPollSendEvents(tp, Event, XIOEventMaskWritable);
//    }
//}
//
//#endif
//



static const XIPAddress_t _XIPAddressZero = {0};

void XIPAddressInit4(XIPAddress_t * _Nonnull address, const struct sockaddr_in * _Nonnull sockaddress) {
    XAssert(address, "null error");
    XAssert(sockaddress, "sockaddress null error");
    memcpy(address, &_XIPAddressZero, sizeof(XIPAddress_t));
    memcpy(address->content + 12, &(sockaddress->sin_addr.s_addr), 4);
}
void XIPAddressInit6(XIPAddress_t * _Nonnull address, const struct sockaddr_in6 * _Nonnull sockaddress) {
    XAssert(address, "null error");
    XAssert(sockaddress, "sockaddress null error");
    memcpy(address->content, sockaddress->sin6_addr.__u6_addr.__u6_addr8, 16);
}


bool_t XIPAddressIsZero(const XIPAddress_t * _Nonnull address) {
    XAssert(address, "null error");
    return memcmp(address, &_XIPAddressZero, sizeof(XIPAddress_t)) == 0;
}
bool_t XIPAddressIsEqual(const XIPAddress_t * _Nonnull lhs, const XIPAddress_t * _Nonnull rhs) {
    XAssert(lhs, "lhs error");
    XAssert(rhs, "rhs error");
    return memcmp(lhs, rhs, sizeof(XIPAddress_t)) == 0;
}
bool_t XIPAddressIsIPv6(const XIPAddress_t * _Nonnull address) {
    XAssert(address, "null error");
    return memcmp(address->content, _XIPAddressZero.content, 12) != 0;
}
