package com.example.jnifirst

import android.util.Log

/**
 *
 * 在JNI中缓存java中字段的id或者方法的id
 * 1. 使用时缓存id
 * 2. 类的初始化中缓存id
 * @author lhc
 * @date 2021/10/24
 */
class CacheFieldMethodId {

    //在jni中调用时缓存id,并会被修改数据
    private var sField: Int = 0

    fun cacheFiledAndMethodInInJni() {
        cacheFieldIdNative()
        Log.d(TAG, "println in java,sField:$sField")
    }

    private fun callback() {
        Log.d(TAG, "call in jni cached method id")
    }

    private external fun cacheFieldIdNative()

    companion object {
        const val TAG = "CacheFieldMethodId"

        //类初始化时缓存id
        @JvmStatic
        private external fun initIds()

        init {
            //类初始化时缓存id
            initIds()
        }
    }
}