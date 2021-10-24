package com.example.jnifirst

import android.util.Log

/**
 * JNI中创建String对象，调用String的构造函数
 * @author lhc
 * @date 2021/10/24
 */
class NewStringObject {

    fun newStringInJni() {
        Log.d(TAG, newStringNativeMethod1())
        Log.d(TAG, newStringNativeMethod2())
    }

    private external fun newStringNativeMethod1(): String
    private external fun newStringNativeMethod2(): String

    companion object {
        const val TAG = "NewStringObject"
    }
}