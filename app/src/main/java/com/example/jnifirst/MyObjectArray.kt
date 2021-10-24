package com.example.jnifirst

import android.util.Log

/**
 * jni访问对象数组
 * @author lhc
 * @date 2021/9/22
 */
class MyObjectArray {

    fun print2DArray() {
        val size = 3
        val i2arr = init2DArray(size)
        for (i in 0 until size) {
            for (j in 0 until size) {
                Log.d(TAG, "" + i2arr[i][j])
            }
            Log.d(TAG, "---------")
        }
    }

    /**
     * jni生成一个二维数组返回给java
     */
    private external fun init2DArray(size: Int): Array<IntArray>

    companion object {
        val TAG = "MyObjectArray"
    }
}