package com.example.jnifirst

import android.util.Log

/**
 * 访问int数组
 * @author lhc
 * @date 2021/9/18
 */
class MyIntArray {

    fun sumIntArray() {
        val intArray = IntArray(10)
        for (i in 0 until 10) {
            intArray[i] = i
        }
        val sum = sumArray(intArray, 10)
        Log.d(TAG, "sum:$sum")

        //数组在sumArray中被修改了
        val sumArray2 = sumArray2(intArray)
        Log.d(TAG, "sum2:$sumArray2")
    }

    /**
     * java jni接收java的int数组后求和
     */
    private external fun sumArray(array: IntArray, size: Int): Int

    /**
     * java jni接收java的int数组后求和另一种实现
     */
    private external fun sumArray2(array: IntArray): Int

    companion object {
        const val TAG = "MyIntArray"
    }
}