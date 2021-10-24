package com.example.jnifirst

import android.util.Log

/**
 *
 * jni访问java成员变量
 * @author lhc
 * @date 2021/10/21
 */
class InstanceFieldAccess {
    private lateinit var s: String

    fun accessInstanceInJni() {
        s = "abc"
        accessField()
        Log.d(TAG, "in java:s = $s")
    }

    private external fun accessField()

    companion object {
        val TAG = "InstanceFieldAccess"
    }
}