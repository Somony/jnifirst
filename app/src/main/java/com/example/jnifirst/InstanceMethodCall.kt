package com.example.jnifirst

import android.util.Log

/**
 * jni中调用java方法
 * @author lhc
 * @date 2021/10/22
 */
class InstanceMethodCall {

    fun callJavaMethodInJni(){
        nativeMethod()
    }


    private fun callByJni(){
        Log.d(TAG,"call in jni---")
    }

    private external fun nativeMethod()

    companion object{
        const val TAG = "InstanceMethodCall"
    }
}