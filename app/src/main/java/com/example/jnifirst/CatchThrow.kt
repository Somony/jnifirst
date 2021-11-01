package com.example.jnifirst

/**
 * jni异常处理：包括检查异常，抓异常，抛异常
 * @author lhc
 * @date 2021/10/30
 */
class CatchThrow {
    fun catchTrowInJni() {
        try {
            throwInJni()
        } catch (e: IllegalArgumentException) {
            e.printStackTrace()
        }
    }

    //在java中抛出异常，jni中调用java方法
    private fun callbackThrow() {
        throw NullPointerException("java throw exception")
    }

    /**
     *
     * @throws IllegalArgumentException
     */
    private external fun throwInJni()

    companion object {
        const val TAG = "CatchThrow"
    }
}