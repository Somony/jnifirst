package com.example.jnifirst

import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.example.jnifirst.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        //访问String
        val myString = MyString()
        binding.sampleText.apply {
            text = myString.helloFromJni()
            val line = myString.getHelloFromJni(text.toString())
            Log.d(TAG, line)
        }

        //访问基本类型数组
        val myIntArray = MyIntArray()
        myIntArray.sumIntArray()

        //访问对象数组
        val myObjectArray = MyObjectArray()
        myObjectArray.print2DArray()

        //访问java成员变量
        val instanceFieldAccess = InstanceFieldAccess()
        instanceFieldAccess.accessInstanceInJni()

        //访问java静态成员变量
        val staticFieldAccess = StaticFieldAccess()
        staticFieldAccess.accessStaticFieldInJni()

        //调用java方法
        val instanceMethodCall = InstanceMethodCall()
        instanceMethodCall.callJavaMethodInJni();

        //调用java静态方法
        val staticMethodCall = StaticMethodCall()
        staticMethodCall.callStaticMethodInJni()

        //调用构造方法
        val newStringObject = NewStringObject()
        newStringObject.newStringInJni()

        //缓存字段或者方法id
        val cacheFieldMethodId = CacheFieldMethodId()
        cacheFieldMethodId.cacheFiledAndMethodInInJni()

        //异常
        val catchThrow = CatchThrow()
        catchThrow.catchTrowInJni()

        //jni_onload
        val jniOnLoad = JniOnLoad()
        jniOnLoad.jniOnLoad()
    }

    companion object {
        const val TAG = "MainActivity"

        // Used to load the 'jnifirst' library on application startup.
        init {
            System.loadLibrary("jnifirst")
        }
    }
}