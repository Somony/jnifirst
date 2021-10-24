package com.example.jnifirst

import android.util.Log

/**
 * jni中调用java中的静态方法
 * @author lhc
 * @date 2021/10/22
 */
class StaticMethodCall {

    fun callStaticMethodInJni() {
        staticNativeMethod()
    }

    private external fun staticNativeMethod()

    companion object {
        const val TAG = "StaticMethodCall"

        @JvmStatic
        fun callback(i: Int): String {
            Log.d(TAG, "call in jni i:$i")
            return "method in java"
        }
    }
}