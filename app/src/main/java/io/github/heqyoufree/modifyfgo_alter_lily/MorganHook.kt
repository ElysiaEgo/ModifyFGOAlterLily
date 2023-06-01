package io.github.heqyoufree.modifyfgo_alter_lily

import android.content.Context
import android.util.Log
import android.widget.FrameLayout
import de.robv.android.xposed.IXposedHookLoadPackage
import de.robv.android.xposed.XC_MethodHook
import de.robv.android.xposed.XposedBridge
import de.robv.android.xposed.XposedHelpers
import de.robv.android.xposed.callbacks.XC_LoadPackage
import io.github.heqyoufree.modifyfgo_alter_lily.imgui.ImGuiView
import java.util.*


class MorganHook : IXposedHookLoadPackage {
    companion object {
        const val TAG = "MorganHook"
    }

    override fun handleLoadPackage(lpparam: XC_LoadPackage.LoadPackageParam) {
        if (lpparam.processName != lpparam.packageName) return
        try {
            System.loadLibrary("Morgan")
            Log.d(TAG, "Morgan loaded for ${lpparam.packageName}")
            XposedBridge.log("Morgan loaded for ${lpparam.packageName}")
            XposedHelpers.findAndHookConstructor(
                "com.unity3d.player.UnityPlayer",
                lpparam.classLoader,
                Context::class.java,
                object : XC_MethodHook() {
                    override fun afterHookedMethod(param: MethodHookParam?) {
                        if (param != null) {
                            Log.d(TAG, "UnityPlayer init")
                            (param.thisObject as FrameLayout).addView(ImGuiView(param.args[0] as Context))
                        }
                    }
                })
        } catch (e: Throwable) {
            Log.d(TAG, "error")
            XposedBridge.log("error")
            e.message?.let {
                Log.d(TAG, "cannot find $it")
                XposedBridge.log("cannot find $it")
            }
        }
    }
}