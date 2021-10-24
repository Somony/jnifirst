package com.example.jnifirst

/**
 * 访问String字符串
 *
 * @author lhc
 * @date 2021/9/22
 */
class MyString {

    fun helloFromJni(): String = stringFromJNI()

    fun getHelloFromJni(str: String): String = getLine(str)


    /**
     * jni生成字符串返回给java
     */
    private external fun stringFromJNI(): String

    /**
     * jni接收java字符串；
     * jni再生成字符串返回给java
     */
    private external fun getLine(text: String): String


}