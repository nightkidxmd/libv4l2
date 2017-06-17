//
// Created by XMD on 2017/5/15.
//

#ifndef AWESOMERECORDER_V4L2_H
#define AWESOMERECORDER_V4L2_H

#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>              /* low-level i/o */
#include <linux/videodev2.h>
#include <sys/mman.h>
#include <map>
#include <assert.h>
using namespace std;

#define LOG_TAG "V4L2"

#include "log.h"
#include "com_tuyou_tsd_common_v4l2_V4L2.h"

#define CLEAR(x) memset (&(x), 0, sizeof (x))
#define ERROR_LOCAL -1
#define SUCCESS_LOCAL 0

static v4l2_buf_type V4L2_BUF_TYPES[] = {
        V4L2_BUF_TYPE_VIDEO_CAPTURE,
        V4L2_BUF_TYPE_VIDEO_OUTPUT,
        V4L2_BUF_TYPE_VIDEO_OVERLAY,
        V4L2_BUF_TYPE_VBI_CAPTURE,
        V4L2_BUF_TYPE_VBI_OUTPUT,
        V4L2_BUF_TYPE_SLICED_VBI_CAPTURE,
        V4L2_BUF_TYPE_SLICED_VBI_OUTPUT,
        V4L2_BUF_TYPE_PRIVATE,
};

static v4l2_field V4L2_FIELD[] = {
        V4L2_FIELD_ANY,
        V4L2_FIELD_NONE,
        V4L2_FIELD_TOP,
        V4L2_FIELD_BOTTOM,
        V4L2_FIELD_INTERLACED,
        V4L2_FIELD_SEQ_TB,
        V4L2_FIELD_SEQ_BT,
        V4L2_FIELD_ALTERNATE,
};

static v4l2_memory V4L2_MEMORY[] = {
        V4L2_MEMORY_MMAP,
        V4L2_MEMORY_USERPTR,
        V4L2_MEMORY_OVERLAY
};


struct buffer {
    void * start;
    size_t length;
    __u32 index;
};

static map<int,buffer*> bufferMaps;

inline bool isValidFd(int fd) {
    return fd > 0;
}


/*
 * 显示错误ID和详细错误描述
 */
inline int errnoexit(const char *s) {
    ALOGE("%s error %d, %s", s, errno, strerror(errno));
    return ERROR_LOCAL;
}

/*
 * r: -1操作失败   0成功
 */
inline int xioctl(int fd, int request, void *arg) {
    int r;
    do
        r = ioctl(fd, request, arg);
    while (-1 == r && EINTR == errno);  // EINTR未取到任何数据

    return r;
}

inline buffer * findBuffer(int fd){
    map<int, buffer*>::iterator iterator = bufferMaps.find(fd);
    buffer* _buffers = NULL;
    if( iterator != bufferMaps.end()){
        _buffers = bufferMaps.at(fd);
    }
    return _buffers;
}

#endif //AWESOMERECORDER_V4L2_H
