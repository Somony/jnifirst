package com.example.jnifirst

/**
 * jni的onload方法加载函数表
 * @author lhc
 * @date 2021/10/31
 */
class JniOnLoad {
    fun jniOnLoad(){
        nativeFoo()
    }

    private external fun nativeFoo()

    companion object{
        const val TAG = "JniOnLoad"
    }
}