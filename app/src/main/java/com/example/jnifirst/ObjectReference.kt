package com.example.jnifirst

import android.util.Log

/**
 * jni中的对象引用
 * @author lhc
 * @date 2021/10/28
 */
class ObjectReference {

    fun objectRefInJni() {
        val localRefStr = localRefNative()
        Log.d(TAG, "localRefStr:$localRefStr")
        globalRefNative()
        globalWeakRefNative()
    }

    private external fun localRefNative(): String

    private external fun globalRefNative()

    private external fun globalWeakRefNative()

    companion object {
        const val TAG = "ObjectReference"
    }
}