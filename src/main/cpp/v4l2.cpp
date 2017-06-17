//
// Created by XMD on 2017/5/15.
//
#include "v4l2.h"
JNIEXPORT jint JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_openDevice
        (JNIEnv *, jobject, jint i){
    struct stat st;
    char dev_name[16];
    sprintf(dev_name, "/dev/video%d", i);
    ALOGE("opendevice() enter dev_name=%s", dev_name);

    // 通过文件名dev_name获取文件信息，并保存在st所指的结构体stat中
    if (-1 == stat(dev_name, &st)) {
        ALOGE("opendevice() Cannot identify '%s': %d, %s", dev_name, errno, strerror(errno));
        return ERROR_LOCAL;
    }

    // 判断该文件是否为字符装置文件
    if (!S_ISCHR(st.st_mode)) {
        ALOGE("opendevice() %s is no device", dev_name);
        return ERROR_LOCAL;
    };

    int fd = open(dev_name, O_RDWR);
    if (-1 == fd) {
        ALOGE("opendevice() Cannot open '%s': %d, %s", dev_name, errno, strerror(errno));
        return ERROR_LOCAL;
    }

    ALOGI("opendevice() open '%s' success!!!", dev_name);
    return fd;
}

JNIEXPORT jint JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_closeDevice
        (JNIEnv *, jobject, jint fd){
    if(!isValidFd(fd)){
        ALOGE("closeDevice() %d is no V4L2 device", fd);
        return NULL;
    }
    return close(fd);
}

JNIEXPORT jobject JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_queryCapability
        (JNIEnv *env, jobject, jint fd){
    if(!isValidFd(fd)){
        ALOGE("queryCapability() %d is no V4L2 device", fd);
        return NULL;
    }

    struct v4l2_capability cap; // 存储v4l2设备支持的操作等基本设备信息
    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)) {
        if (EINVAL == errno) {
            ALOGE("queryCapability() %d is no V4L2 device", fd);
            return NULL;
        } else {
            ALOGE("queryCapability() %d error:%d", fd,errnoexit("VIDIOC_QUERYCAP"));
            return NULL;
        }
    }

    char driver[16];
    char card[32];
    char bus_info[32];

    sprintf(driver,"%s",cap.driver);
    sprintf(card,"%s",cap.card);
    sprintf(bus_info,"%s",cap.bus_info);

    jintArray reserved = env->NewIntArray(4);
    jint rawReserved[4];
    memcpy(rawReserved,cap.reserved,4);
    env->SetIntArrayRegion(reserved,0,4,rawReserved);
    jclass v4l2capabilityClazz = env->FindClass("com/tuyou/tsd/common/v4l2/V4L2Capability");
    jmethodID v4l2capabilityInitMethodId = env->GetMethodID(v4l2capabilityClazz,
                                                           "<init>",
                                                           "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;II[I)V");

    jobject v4l2capability = env->NewObject(v4l2capabilityClazz,v4l2capabilityInitMethodId,
                                            env->NewStringUTF(driver),
                                            env->NewStringUTF(card),
                                            env->NewStringUTF(bus_info),
                                            cap.version,
                                            cap.capabilities,
                                            reserved
    );
    return v4l2capability;
}

JNIEXPORT jobject JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_queryCropCapability
        (JNIEnv *env, jobject, jint fd,jint type){
    if(!isValidFd(fd)){
        ALOGE("queryCropCapability() %d is no V4L2 device", fd);
        return NULL;
    }
    struct v4l2_cropcap cropcap; // 设置摄像头的捕捉能力，在捕捉视频时应先设置
    CLEAR(cropcap);
    // 指定buf的类型为capture, 用于视频捕捉模式
    cropcap.type = V4L2_BUF_TYPES[type];
    if(0 != xioctl(fd, VIDIOC_CROPCAP, &cropcap)){
        if (EINVAL == errno) {
            ALOGE("queryCropCapability() %d is no V4L2 device", fd);
            return NULL;
        } else {
            ALOGE("queryCropCapability() %d error:%d", fd,errnoexit("VIDIOC_CROPCAP"));
            return NULL;
        }
    }

    jclass rectClazz = env->FindClass("android/graphics/Rect");
    jmethodID rectInitMethodId = env->GetMethodID(rectClazz,"<init>","(IIII)V");
    jobject bounds = env->NewObject(rectClazz,rectInitMethodId,
                                    cropcap.bounds.left,
                                    cropcap.bounds.top,
                                    cropcap.bounds.left+cropcap.bounds.width,
                                    cropcap.bounds.top+cropcap.bounds.height
    );
    jobject defrect = env->NewObject(rectClazz,rectInitMethodId,
                                     cropcap.defrect.left,
                                     cropcap.defrect.top,
                                     cropcap.defrect.left+cropcap.defrect.width,
                                     cropcap.defrect.top+cropcap.defrect.height
    );

    jclass fractClazz = env->FindClass("com/tuyou/tsd/common/v4l2/V4L2Fract");

    jmethodID fractInitMethodId = env->GetMethodID(fractClazz,"<init>",
                                                     "(II)V"
    );
    jobject fract = env->NewObject(fractClazz,fractInitMethodId,
                                   cropcap.pixelaspect.numerator,
                                   cropcap.pixelaspect.denominator
    );

    jclass v4l2CropCapClazz = env->FindClass("com/tuyou/tsd/common/v4l2/V4L2CropCap");

    jmethodID v4l2CropCapInitMethodId = env->GetMethodID(v4l2CropCapClazz,"<init>",
                                                          "(Landroid/graphics/Rect;Landroid/graphics/Rect;Lcom/tuyou/tsd/common/v4l2/V4L2Fract;)V"
    );

    jobject v4l2CropCap = env->NewObject(v4l2CropCapClazz,v4l2CropCapInitMethodId,
                                         bounds,
                                         defrect,
                                         fract
    );
    return v4l2CropCap;
}



JNIEXPORT jint JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_setCrop
        (JNIEnv * env, jobject, jint fd,jint type,jobject rect){
    if(!isValidFd(fd)){
        ALOGE("setCrop() %d is no V4L2 device", fd);
        return ERROR_LOCAL;
    }
    jclass rectClazz = env->FindClass("android/graphics/Rect");
    jfieldID leftid = env->GetFieldID(rectClazz,"left","I");
    jfieldID topid = env->GetFieldID(rectClazz,"top","I");
    jfieldID rightid = env->GetFieldID(rectClazz,"right","I");
    jfieldID bottomid = env->GetFieldID(rectClazz,"bottom","I");
    struct v4l2_rect c;
    jint left;
    jint top;
    c.left = left = env->GetIntField(rect,leftid);
    c.top = top = env->GetIntField(rect,topid);
    c.width = env->GetIntField(rect,rightid) - left;
    c.height = env->GetIntField(rect,bottomid) - top;
    struct v4l2_crop crop; // 设置视频采集窗口的类型和大小
    crop.type = V4L2_BUF_TYPES[type];
    crop.c = c;
    if (0 != xioctl(fd, VIDIOC_S_CROP, &crop)) {
        if (EINVAL == errno) {
            ALOGE("setCrop() %d is no V4L2 device", fd);
            return ERROR_LOCAL;
        } else {
            ALOGE("setCrop() %d error:%d", fd,errnoexit("VIDIOC_S_CROP"));
            return ERROR_LOCAL;
        }
    }
    return SUCCESS_LOCAL;
}



JNIEXPORT jobject JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_getCrop
        (JNIEnv *env, jobject, jint fd){
    if(!isValidFd(fd)){
        ALOGE("getCrop() %d is no V4L2 device", fd);
        return NULL;
    }
    struct v4l2_crop crop;
    if (0 != xioctl(fd, VIDIOC_G_CROP, &crop)) {
        if (EINVAL == errno) {
            ALOGE("getCrop() %d is no V4L2 device", fd);
            return NULL;
        } else {
            ALOGE("getCrop() %d error:%d", fd,errnoexit("VIDIOC_G_CROP"));
            return NULL;
        }
    }
    jclass rectClazz = env->FindClass("android/graphics/Rect");
    jmethodID rectInitMethodId = env->GetMethodID(rectClazz,"<init>","(IIII)V");
    jobject rect = env->NewObject(rectClazz,rectInitMethodId,
                                  crop.c.left,
                                  crop.c.top,
                                  crop.c.left+crop.c.width,
                                  crop.c.top+crop.c.height
    );
    return rect;
}

JNIEXPORT jobjectArray JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_queryFormat
        (JNIEnv * env, jobject, jint fd,jint type){

    if(!isValidFd(fd)){
        ALOGE("queryFormat() %d is no V4L2 device", fd);
        return NULL;
    }

    struct v4l2_fmtdesc* fmtdesc[16];
    memset(fmtdesc,0,sizeof(fmtdesc));
    __u32 index = 0;
    fmtdesc[index] = (v4l2_fmtdesc *)malloc(sizeof(v4l2_fmtdesc));
    memset(fmtdesc[index],0,sizeof(v4l2_fmtdesc));
    fmtdesc[index]->index = index;
    fmtdesc[index]->type = V4L2_BUF_TYPES[type];

    while (xioctl(fd, VIDIOC_ENUM_FMT, fmtdesc[index]) == 0) {
        index++;
        fmtdesc[index] = (v4l2_fmtdesc *)malloc(sizeof(v4l2_fmtdesc));
        memset(fmtdesc[index],0,sizeof(v4l2_fmtdesc));
        fmtdesc[index]->index = index;
        fmtdesc[index]->type = V4L2_BUF_TYPES[type];

    }

    if(index == 0){
        ALOGE("queryFormat() %d error", fd);
        return NULL;
    }

    jclass v4l2formatdescClazz = env->FindClass("com/tuyou/tsd/common/v4l2/V4L2FormatDesc");
    jmethodID v4l2formatdescInitMethodId = env->GetMethodID(v4l2formatdescClazz,"<init>",
                                                            "(IILjava/lang/String;I[I)V"
    );
    jobjectArray ret = env->NewObjectArray(index,v4l2formatdescClazz,NULL);

    for(int i=0;i<index;i++){
        char description[32];
        sprintf(description,"%s",fmtdesc[i]->description);
        jintArray reserved = env->NewIntArray(4);
        jint rawReserved[4];
        memcpy(rawReserved,fmtdesc[i]->reserved,4);
        env->SetIntArrayRegion(reserved,0,4,rawReserved);
        jobject v4l2formatdesc = env->NewObject(v4l2formatdescClazz,v4l2formatdescInitMethodId,
                                                fmtdesc[i]->index,
                                                fmtdesc[i]->flags,
                                                env->NewStringUTF(description),
                                                fmtdesc[i]->pixelformat,
                                                reserved
        );
        env->SetObjectArrayElement(ret,i,v4l2formatdesc);
        free(fmtdesc[i]);
    }

    return ret;
}

JNIEXPORT jint JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_setFormat
        (JNIEnv *, jobject, jint fd,jint type,jint width,jint height,jint pixelformat,jint field){
    if(!isValidFd(fd)){
        ALOGE("setFormat() %d is no V4L2 device", fd);
        return ERROR_LOCAL;
    }

    struct v4l2_format fmt; // 设置摄像头的视频制式、帧格式
    CLEAR(fmt);
    fmt.type = V4L2_BUF_TYPES[type];
    fmt.fmt.pix.width  = (__u32)width;
    fmt.fmt.pix.height =  (__u32)height;
    fmt.fmt.pix.pixelformat = (__u32)pixelformat; // 设置视频存储类型
    fmt.fmt.pix.field = V4L2_FIELD[field];
    if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
        return errnoexit("VIDIOC_S_FMT");

    return SUCCESS_LOCAL;
}

JNIEXPORT jint JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_initmmap
        (JNIEnv *, jobject, jint fd,jint count,jint type,jint memory){
    if(!isValidFd(fd)){
        ALOGE("initmmap() %d is no V4L2 device", fd);
        return ERROR_LOCAL;
    }


    struct v4l2_requestbuffers req;

    ALOGI("initmmap() enter\n");

    CLEAR(req);

    // 缓存队列里保存4张照片
    req.count = (__u32)count;
    // 数据流必须是V4L2_BUF_TYPE_VIDEO_CAPTURE
    req.type = V4L2_BUF_TYPES[type];
    req.memory = V4L2_MEMORY[memory];

    // 向驱动提出申请内存的请求
    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            ALOGE("initmmap() %d does not support memory mapping", fd);
            return ERROR_LOCAL;
        } else {
            return errnoexit("VIDIOC_REQBUFS");
        }
    }

    if (req.count < 2) {
        ALOGE("initmmap() Insufficient buffer memory on %d", fd);
        return ERROR_LOCAL;
    }

    map<int, buffer*>::iterator i = bufferMaps.find(fd);
    buffer* _buffers = NULL;
    if( i != bufferMaps.end()){
        _buffers = bufferMaps.at(fd);
    }else{
        _buffers =  (buffer*)calloc(req.count, sizeof(*_buffers));
        bufferMaps.insert(pair<int,buffer*>(fd,_buffers));
    }

    if (!_buffers) {
        ALOGE("initmmap() Out of memory");
        return ERROR_LOCAL;
    }

    for (_buffers->index = 0; _buffers->index < req.count; ++_buffers->index) {
        struct v4l2_buffer buf;
        CLEAR(buf);
        buf.type = V4L2_BUF_TYPES[type];
        buf.memory = V4L2_MEMORY[memory];
        buf.index = _buffers->index;

        // 通过调用VIDIOC_QUERYBUF来获取内核空间的视频缓存区信息，然后调用函数mmap把内核空间地址映射到用户空间，
        // 这样应用程序才能够访问位于内核空间的视频缓存区
        if (-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
            return errnoexit("VIDIOC_QUERYBUF");

        _buffers[_buffers->index].length = buf.length;
        _buffers[_buffers->index].start = mmap(NULL, buf.length,
                                        PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);

        if (MAP_FAILED == _buffers[_buffers->index].start)
            return errnoexit("mmap");
    }

    ALOGI("initmmap() end");

    return SUCCESS_LOCAL;
}

JNIEXPORT jint JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_uninitmmap
        (JNIEnv *, jobject, jint fd){
    if(!isValidFd(fd)){
        ALOGE("uninitmmap() %d is no V4L2 device", fd);
        return ERROR_LOCAL;
    }

    buffer* _buffers = findBuffer(fd);

    if(!_buffers){
        ALOGW("uninitmmap() already freed %d.",fd);
        return SUCCESS_LOCAL;
    }
    unsigned int i;
    for (i = 0; i < _buffers->index; ++i)
        if (-1 == munmap(_buffers[i].start, _buffers[i].length))
            return errnoexit("munmap");
    free(_buffers);
    bufferMaps.erase(fd);

    return SUCCESS_LOCAL;
}

JNIEXPORT jint JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_streamon
        (JNIEnv *, jobject, jint fd,jint type,jint memory){
    if(!isValidFd(fd)){
        ALOGE("streamon() %d is no V4L2 device", fd);
        return ERROR_LOCAL;
    }

    buffer* _buffers = findBuffer(fd);
    if(!_buffers){
        ALOGE("streamon error:%d not initmmap yet.",fd);
        return ERROR_LOCAL;
    }

    ALOGI("streamon() start");


    for (unsigned int i = 0; i < _buffers->index; ++i) {
        struct v4l2_buffer buf;
        CLEAR(buf);
        buf.type = V4L2_BUF_TYPES[type];
        buf.memory = V4L2_MEMORY[memory];
        buf.index = i;

        // 把缓存帧放入缓存队列中
        if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
            return errnoexit("VIDIOC_QBUF");
    }

    enum v4l2_buf_type v4l2BufType;

    v4l2BufType = V4L2_BUF_TYPES[type];

    // 打开数据流
    if (-1 == xioctl(fd, VIDIOC_STREAMON, &v4l2BufType))
        return errnoexit("VIDIOC_STREAMON");

    ALOGI("streamon() end");
    return SUCCESS_LOCAL;

}

JNIEXPORT jint JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_streamoff
        (JNIEnv *, jobject, jint fd,jint type){
    if(!isValidFd(fd)){
        ALOGE("streamoff() %d is no V4L2 device", fd);
        return ERROR_LOCAL;
    }

    enum v4l2_buf_type buf_type;
    buf_type =  V4L2_BUF_TYPES[type];
    if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &buf_type))
        return errnoexit("VIDIOC_STREAMOFF");
    return SUCCESS_LOCAL;
}

JNIEXPORT jint JNICALL Java_com_tuyou_tsd_common_v4l2_V4L2_readFrame
        (JNIEnv * env, jobject, jint fd,jint type,jint memory,jbyteArray out){
    buffer* _buffer = findBuffer(fd);
    if(!_buffer){
        ALOGW("readFrame() not initmmap %d.",fd);
        return ERROR_LOCAL;
    }
    int buffer_index = -1;
    for (;;) {
        // fd_set是一组文件描述字(fd)的集合，它用一位来表示一个fd
        fd_set fds;
        // 用于描述一段时间长度，如果在这个时间内，需要监视的描述符没有事件发生则函数返回，返回值为0
        struct timeval tv;
        int r;
        // 将指定的文件描述符集清空，在对文件描述符集合进行设置前，必须对其进行初始化，
        // 如果不清空，由于在系统分配内存空间后，通常并不作清空处理，所以结果是不可知的
        FD_ZERO(&fds);
        // 用于在文件描述符集合中增加一个新的文件描述符
        FD_SET(fd, &fds);
        tv.tv_sec = 2;
        tv.tv_usec = 0;
        r = select(fd + 1, &fds, NULL, NULL, &tv);
        if (-1 == r) {
            if (EINTR == errno)
                continue;
            return errnoexit("select");
        }
        if (0 == r) {
            ALOGE("readFrame() select timeout");
            return ERROR_LOCAL;
        }

        struct v4l2_buffer buf;
        CLEAR(buf);
        buf.type = V4L2_BUF_TYPES[type];
        buf.memory = V4L2_MEMORY[memory];
        // 从视频缓存区中取出一个缓存帧
        if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
            switch (errno) {
                case EAGAIN:
                    ALOGE("readFrame() EAGAIN!!!");
                    return -2;
                case EIO:
                default:
                    return errnoexit("VIDIOC_DQBUF");
            }
        }

        assert(buf.index < _buffer->index);
        // 将取出的缓存帧空间重新放回缓存区
        buffer_index = buf.index;
        if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
            return errnoexit("VIDIOC_QBUF");
        break;
    }

    jboolean isCopy = 0;
    jbyte* jbytes = env->GetByteArrayElements(out,&isCopy);
    memcpy(jbytes,_buffer[buffer_index].start,_buffer[buffer_index].length);
    env->ReleaseByteArrayElements(out,jbytes, JNI_ABORT);

    return SUCCESS_LOCAL;
}