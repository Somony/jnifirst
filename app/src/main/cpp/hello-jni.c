//
// Created by hc l on 2021/9/18.
//
#include <jni.h>
#include <string.h>
#include <stdio.h>
#include "include/log.h"
#include "include/exception-util.h"

JNIEXPORT jstring JNICALL
Java_com_example_jnifirst_MyString_stringFromJNI(JNIEnv *env, jobject thiz) {
    char *str = "hello world from jni";
    return (*env)->NewStringUTF(env, str);
}


JNIEXPORT jstring JNICALL
Java_com_example_jnifirst_MyString_getLine(JNIEnv *env, jobject thiz, jstring text) {
    //将jni字符串转成c字符串,最后一个参数传NULL，让JVM指定是赋值还是直接返回原始数据，但是不管如何，都必须调用release
    const char *str = (*env)->GetStringUTFChars(env, text, NULL);
    if (str == NULL) {
        //为新的字符串分配内存，若因内存不足会分配失败会返回NULL,并抛出OutOfMemory错误，但是不会改变程序的执行流
        return NULL;
    }
    LOGD("%s", str);
    //使用完毕后需要释字符串占用的内存
    (*env)->ReleaseStringUTFChars(env, text, str);
    //返回新创建的一个字符串
    char *hello = "hello world from getLine";
    //将c字符串转成jni字符串返回
    return (*env)->NewStringUTF(env, hello);
}

JNIEXPORT jint JNICALL
Java_com_example_jnifirst_MyIntArray_sumArray(JNIEnv *env, jobject thiz, jintArray array,
                                              jint size) {
    //修改数组中的元素
    jint mo_buf[] = {10};
    //                                  开始的位置 修改的长度 源数组
    (*env)->SetIntArrayRegion(env, array, 0, 1, mo_buf);

    //将jni int数组转成c的数组
    jint buf[size];
    jint sum = 0;
    //将int数组中的所有元素赋值到一个C缓冲区中
    (*env)->GetIntArrayRegion(env, array, 0, size, buf);

    for (int i = 0; i < size; ++i) {
        sum += buf[i];
    }
    return sum;
}

JNIEXPORT jint JNICALL
Java_com_example_jnifirst_MyIntArray_sumArray2(JNIEnv *env, jobject thiz, jintArray array) {
    //获取数组的长度
    jint length = (*env)->GetArrayLength(env, array);

    //将原始数组进行复制后，返回指向复制后的数组的指针
    jint *carr = (*env)->GetIntArrayElements(env, array, NULL);
    //分配内存，可能会失败，并抛出异常
    if (carr == NULL) {
        return 0;
    }

    jint sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += carr[i];
    }

    //释放内存
    (*env)->ReleaseIntArrayElements(env, array, carr, 0);
    return sum;
}

JNIEXPORT jobjectArray JNICALL
Java_com_example_jnifirst_MyObjectArray_init2DArray(JNIEnv *env, jobject thiz, jint size) {
    //findClass获取一个int二维数组引用
    jclass intArrCls = (*env)->FindClass(env, "[I");
    //类加载失败，会返回NULL，并抛出异常
    if (intArrCls == NULL) {
        return NULL;
    }

    //创建int二维数组对象，此时的对象是一个一位数组，二维数组就是数组的数组，那么一位数组的每个item都是一个数组
    jobjectArray result = (*env)->NewObjectArray(env, size, intArrCls, NULL);
    //创建失败
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        jint tmp[256];
        //为二维数组每个item都设置一个数组

        //1. 生成int数组
        jintArray iarr = (*env)->NewIntArray(env, size);
        if (iarr == NULL) {
            return NULL;
        }
        for (int j = 0; j < size; ++j) {
            tmp[j] = i + j;
        }
        //2.使用tmp给iarr数组item赋值
        (*env)->SetIntArrayRegion(env, iarr, 0, size, tmp);
        //3.将iarr设置给result
        (*env)->SetObjectArrayElement(env, result, i, iarr);
        //4.删除局部变量
        (*env)->DeleteLocalRef(env, iarr);
    }
    return result;

}

JNIEXPORT void JNICALL
Java_com_example_jnifirst_InstanceFieldAccess_accessField(JNIEnv *env, jobject thiz) {
    //访问java中的成员变量

    //1.获取类引用（thiz是对象引用）
    jclass jcls = (*env)->GetObjectClass(env, thiz);
    LOGD("in C:\n");
    //2. 获取成员字段id
    jfieldID fid = (*env)->GetFieldID(env, jcls, "s", "Ljava/lang/String;");
    if (fid == NULL) {
        //获取id失败
        return;
    }
    //3. 获取字段的值
    jobject jstr = (*env)->GetObjectField(env, thiz, fid);
    char *str = (*env)->GetStringUTFChars(env, jstr, NULL);
    if (str == NULL) {
        //out of memory
        return;
    }
    LOGD("c.s = %s\n", str);
    (*env)->ReleaseStringUTFChars(env, jstr, str);
    //4.修改字段的值
    jstring newStr = (*env)->NewStringUTF(env, "123");
    if (newStr == NULL) {
        //创建失败
        return;
    }
    //成员变量，要使用对象引用
    (*env)->SetObjectField(env, thiz, fid, newStr);
}

JNIEXPORT void JNICALL
Java_com_example_jnifirst_StaticFieldAccess_accessStaticField(JNIEnv *env, jobject thiz) {
    //访问java中的静态成员变量

    //1.获取类引用
    jclass jcls = (*env)->GetObjectClass(env, thiz);
    LOGD("in C\n");
    //2.获取静态成员变量字段id
    jfieldID sfid = (*env)->GetStaticFieldID(env, jcls, "si", "I");
    if (sfid == NULL) {
        return;
    }
    //3.获取静态字段的值，静态变量，需要使用类引用
    jint intSi = (*env)->GetStaticIntField(env, jcls, sfid);
    LOGD("c.si = %d", intSi);
    //4.修改静态字段的值
    (*env)->SetStaticIntField(env, jcls, sfid, 200);
}

JNIEXPORT void JNICALL
Java_com_example_jnifirst_InstanceMethodCall_nativeMethod(JNIEnv *env, jobject thiz) {
    //调用java中的方法

    //1.获取类引用
    jclass jcls = (*env)->GetObjectClass(env, thiz);
    LOGD("in C\n");
    //2.获取方法id
    jmethodID mid = (*env)->GetMethodID(env, jcls, "callByJni", "()V");
    if (mid == NULL) {
        return;
    }
    //3.调用方法，要使用对象引用,Void指方法的返回值
    (*env)->CallVoidMethod(env, thiz, mid);
}

JNIEXPORT void JNICALL
Java_com_example_jnifirst_StaticMethodCall_staticNativeMethod(JNIEnv *env, jobject thiz) {
    //调用java中的静态方法

    //1. 获取类引用
    jclass jcls = (*env)->GetObjectClass(env, thiz);
    LOGD("in C:\n");
    //2. 获取静态方法id
    jmethodID smid = (*env)->GetStaticMethodID(env, jcls, "callback", "(I)Ljava/lang/String;");
    if (smid == NULL) {
        return;
    }
    //3. 低啊用静态方法，静态方法需要使用类引用；Object指返回值
    jint i = 100;
    jobject jReturnValue = (*env)->CallStaticObjectMethod(env, jcls, smid, i);
    const char *str = (*env)->GetStringUTFChars(env, jReturnValue, NULL);
    LOGD("str from java method return :%s", str);
}

/**
 * 第一种实现:
 * 实现JNI函数NewString相同的功能:把储存在C缓冲区内的Unicode编码的字符序列，创建成一个java.lang.String对象
 * 既然可以使用JNI函数实现相同的功能，为什么JNI还需要提供NewString这样的内置函数呢？原因是内置函数的效率远高于在本地代码里调用构造函数的API
 *
 * 与第二种的区别：
 * 1. 指定了编码，防止乱码
 * 2. 使用NewObject创建并调用构造函数
 * @return
 */
jstring MyNewString1(JNIEnv *env, jchar *chars, jint len) {
    //1. 找到一个String类
    jclass stringClass = (*env)->FindClass(env, "java/lang/String");
    if (stringClass == NULL) {
        return NULL;
    }
    //2. 找到String的构造函数id：String(byte[],String charset),指定编码，防止乱码（和MyNewString2对比即可看出），构造函数是<init>
    jmethodID cid = (*env)->GetMethodID(env, stringClass, "<init>", "([BLjava/lang/String;)V");
    if (cid == NULL) {
        return NULL;
    }
    //3. 创建char[]数组，并填充数组
    jbyteArray eleArr = (*env)->NewByteArray(env, len);
    if (eleArr == NULL) {
        return NULL;
    }
    (*env)->SetByteArrayRegion(env, eleArr, 0, len, (const jbyte *) chars);
    //4. 创建String对象，调用构造方法
    jstring charset = (*env)->NewStringUTF(env, "utf-8");
    jobject result = (*env)->NewObject(env, stringClass, cid, eleArr, charset);
    //5. 释放本地资源
    (*env)->DeleteLocalRef(env, stringClass);
    (*env)->DeleteLocalRef(env, eleArr);
    return result;
}

/**
 * 第二种实现方式：
 * 首先使用AllocObject创建一个未初始化的对象，再使用<code>CallNonvirtualVoidMethod</code>来调用构造函数
 * 构造函数最多只能调用一次
 * @return
 */
jstring MyNewString2(JNIEnv *env, jchar *chars, jint len) {
    //1. 找到一个String类
    jclass stringClass = (*env)->FindClass(env, "java/lang/String");
    if (stringClass == NULL) {
        return NULL;
    }
    //2. 找到String的构造函数id：String(char[]) ,构造函数是<init>
    jmethodID cid = (*env)->GetMethodID(env, stringClass, "<init>", "([C)V");
    if (cid == NULL) {
        return NULL;
    }
    //3. 创建char[]数组，并填充数组
    jcharArray eleArr = (*env)->NewCharArray(env, len);
    if (eleArr == NULL) {
        return NULL;
    }
    (*env)->SetCharArrayRegion(env, eleArr, 0, len, chars);
    //4. 创建String对象，调用构造方法;使用CallNonvirtualVoidMethod
    //4.1首先使用AllocObject创建一个未初始化的对象
    jobject result = (*env)->AllocObject(env, stringClass);
    //4.2再使用使用CallNonvirtualVoidMethod调用构造函数
    if (result) {
        (*env)->CallNonvirtualVoidMethod(env, result, stringClass, cid, eleArr);
        //检查异常
        if ((*env)->ExceptionCheck(env)) {
            (*env)->DeleteLocalRef(env, result);
            return NULL;
        }
    }
    //5. 释放本地资源
    (*env)->DeleteLocalRef(env, stringClass);
    (*env)->DeleteLocalRef(env, eleArr);
    return result;
}

JNIEXPORT jstring JNICALL
Java_com_example_jnifirst_NewStringObject_newStringNativeMethod1(JNIEnv *env, jobject thiz) {
    char *chars = "new String object from native method1";
    return MyNewString1(env, (jchar *) chars, strlen(chars));
}

JNIEXPORT jstring JNICALL
Java_com_example_jnifirst_NewStringObject_newStringNativeMethod2(JNIEnv *env, jobject thiz) {
    char *chars = "new String object from native method2";
    return MyNewString2(env, (jchar *) chars, strlen(chars));
}

//缓存的全局变量：callback方法的id
jmethodID MID_CacheFieldMethodId_callback;

JNIEXPORT void JNICALL
Java_com_example_jnifirst_CacheFieldMethodId_initIds(JNIEnv *env, jclass clazz) {
    //将方法参数缓存在变量中
    MID_CacheFieldMethodId_callback = (*env)->GetMethodID(env, clazz, "callback", "()V");
}

JNIEXPORT void JNICALL
Java_com_example_jnifirst_CacheFieldMethodId_cacheFieldIdNative(JNIEnv *env, jobject thiz) {
    //调用java中的方法
    (*env)->CallVoidMethod(env, thiz, MID_CacheFieldMethodId_callback);

    static jfieldID sFieldId = NULL;
    //获取java中的成员变量，并缓存

    //1. 获取类
    jclass jcls = (*env)->GetObjectClass(env, thiz);
    LOGD("in C\n");
    //2. 获取成员变量id
    if (sFieldId == NULL) {
        sFieldId = (*env)->GetFieldID(env, jcls, "sField", "I");
        if (sFieldId == NULL) {
            return;
        }
    }
    //3.给获取成员赋值
    jint sFieldValue = (*env)->GetIntField(env, thiz, sFieldId);
    LOGD("sField value from java:%d", sFieldValue);
    (*env)->SetIntField(env, thiz, sFieldId, 100);
}

JNIEXPORT jstring JNICALL
Java_com_example_jnifirst_ObjectReference_localRefNative(JNIEnv *env, jobject thiz) {
    //局部引用在方法结束后会回收，使用static缓存局部变量是无效的（变量id，方法id哪些不属于局部对象引用）
    //第一种： DeleteLocalRef可以手动释放局部引用
    jclass jStrClass = (*env)->FindClass(env, "java/lang/String");
    (*env)->DeleteLocalRef(env, jStrClass);

    //第二种：EnsureLocalCapacity,PushLocalFrame,PopLocalFrame管理局部引用------没有了解清除，听说基本不会使用这种方式
    if ((*env)->EnsureLocalCapacity(env, 10) < 0) {
        //在当前线程中，通过传入一个容量capacity，限制局部引用创建的数量。
        // 成功则返回0，否则返回一个负数，并抛出一个OutOfMemoryError。VM会自动确保至少可以创建16个局部引用。

        //OOM
        return NULL;
    }

    //在for循环中可以使用的最大局部引用数量
    jint N_REFS = 10;
    for (int i = 0; i < 10; ++i) {
        if ((*env)->PushLocalFrame(env, N_REFS) < 0) {
            //OOM
        }
        //create local object
        //....

        //销毁局部变量
        (*env)->PopLocalFrame(env, NULL);
    }

    //返回局部引用，使用NewLocalRef
    jstring jstr = MyNewString1(env, "hahha", strlen("hahha"));
    return (*env)->NewLocalRef(env, jstr);
}

JNIEXPORT void JNICALL
Java_com_example_jnifirst_ObjectReference_globalRefNative(JNIEnv *env, jobject thiz) {
    static jstring stringClass;

    //创建全局引用过程
    if (stringClass == NULL) {
        //1. 创建局部引用
        jclass jstrLocalRef = (*env)->FindClass(env, "java/lang/String");
        if (jstrLocalRef == NULL) {
            return;
        }
        //2. 将局部引用保存在全局引用中
        stringClass = (*env)->NewGlobalRef(env, jstrLocalRef);
        //3. 局部引用不再使用，可以销毁
        (*env)->DeleteLocalRef(env, jstrLocalRef);
        //4. 判断全局引用是否创建成功
        if (stringClass == NULL) {
            return;
        }
    }
    //......
}

JNIEXPORT void JNICALL
Java_com_example_jnifirst_ObjectReference_globalWeakRefNative(JNIEnv *env, jobject thiz) {
    static jstring stringClass;

    //创建全局弱引用过程，判断弱引用是否被回收；使用obj == NULL或者IsSameObject(env,obj1,NULL)==JNI_TRUE均可
    //若是判断对象相等，需要使用IsSameObject(env,obj1,obj2)
    if (stringClass == NULL) {
        //1. 创建局部引用
        jclass jstrLocalRef = (*env)->FindClass(env, "java/lang/String");
        if (jstrLocalRef == NULL) {
            return;
        }
        //2. 将局部引用保存在全局弱引用中
        stringClass = (*env)->NewWeakGlobalRef(env, jstrLocalRef);
        //3. 局部引用不再使用，可以销毁
        (*env)->DeleteLocalRef(env, jstrLocalRef);
        //4. 判断全局弱引用是否创建成功
        if (stringClass == NULL) {
            return;
        }
    }
    //....
}

JNIEXPORT void JNICALL
Java_com_example_jnifirst_CatchThrow_throwInJni(JNIEnv *env, jobject thiz) {
    //jni中检查java方法中的异常；并抛出新的异常，处理异常

    //调用java方法，并检查异常
    jclass cls = (*env)->GetObjectClass(env, thiz);
    jmethodID mid = (*env)->GetMethodID(env, cls, "callbackThrow", "()V");
    if (mid == NULL) {
        return;
    }
    (*env)->CallVoidMethod(env, thiz, mid);
    //检查异常,ExceptionOccurred获取异常的指针
    jthrowable exc = (*env)->ExceptionOccurred(env);
    if (exc) {
        //发生异常，打印异常信息，clear异常,这样相当于异常被抓住
        (*env)->ExceptionDescribe(env);
        (*env)->ExceptionClear(env);

        //抛出新的异常,出现异常后若不做clear,就做资源回收操作，不应该继续进行后续操作
        //jclass illegalExceptionCls = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
        //(*env)->ThrowNew(env, illegalExceptionCls, "throw exception from C");

        //使用异常工具函数
        JUN_ThrowByName(env, "java/lang/IllegalArgumentException", "throw exception from C util");
    }
}


void nativeFoo(JNIEnv *env, jobject thiz) {
    LOGD("method register from JNI_OnLoad");
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    //获取env
    JNIEnv *env;
    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    char *className = "com/example/jnifirst/JniOnLoad";
    jclass c = (*env)->FindClass(env, className);
    if (c == NULL) {
        return JNI_ERR;
    }
    //注册本地方法
    static const JNINativeMethod method[] = {
            {"nativeFoo", "()V", (void *) nativeFoo}
    };
    int rc = (*env)->RegisterNatives(env, c, method, sizeof(method) / sizeof(method[0]));
    if (rc != JNI_OK) {
        return rc;
    }
    return JNI_VERSION_1_6;
}