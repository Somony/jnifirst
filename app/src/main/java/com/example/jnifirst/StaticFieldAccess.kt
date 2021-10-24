package com.example.jnifirst

import android.util.Log

/**
 *
 * 访问java中的静态变量
 * @author lhc
 * @date 2021/10/21
 */
class StaticFieldAccess {

    fun accessStaticFieldInJni() {
        accessStaticField()
        Log.d(TAG, "in java:si=$si")
    }

    private external fun accessStaticField();


    companion object {
        const val TAG = "StaticFieldAccess"
        var si: Int = 0
    }
}