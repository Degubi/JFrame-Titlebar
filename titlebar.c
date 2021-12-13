#include "jni.h"
#include "jawt_md.h"
#include "windows.h"
#include "dwmapi.h"

#define DWMWA_USE_IMMERSIVE_DARK_MODE 20

static jboolean isFrameVisible(JNIEnv* env, jclass jFrameClass, jobject frameObject) {
    jmethodID isVisibleMethod = (*env)->GetMethodID(env, jFrameClass, "isVisible", "()Z");

    return (*env)->CallBooleanMethod(env, frameObject, isVisibleMethod);
}

static void setJFrameTheme(JNIEnv* env, jobject frameObject, BOOL isDarkMode) {
    if(frameObject != NULL) {
        jclass jFrameClass = (*env)->FindClass(env, "javax/swing/JFrame");

        if(isFrameVisible(env, jFrameClass, frameObject)) {
            JAWT awt = { .version = JAWT_VERSION_9 };
            JAWT_GetAWT(env, &awt);

            JAWT_DrawingSurface* surface = awt.GetDrawingSurface(env, frameObject);
            jint lock = surface->Lock(surface);
            JAWT_DrawingSurfaceInfo* surfaceInfo = surface->GetDrawingSurfaceInfo(surface);
            HWND nativeWindowHandle = ((JAWT_Win32DrawingSurfaceInfo*) surfaceInfo->platformInfo)->hwnd;

            DwmSetWindowAttribute(nativeWindowHandle, DWMWA_USE_IMMERSIVE_DARK_MODE, &(BOOL) { isDarkMode }, sizeof(BOOL));

            surface->Unlock(surface);
            awt.FreeDrawingSurface(surface);

            // Hack: I couldn't find a way to re-update the titlebar... not even with SetWindowPos or any other windows api functions...
            // Might worth trying some other random windows api functions... later
            jmethodID getWidthMethod = (*env)->GetMethodID(env, jFrameClass, "getWidth", "()I");
            jmethodID getHeightMethod = (*env)->GetMethodID(env, jFrameClass, "getHeight", "()I");
            jmethodID setSizeMethod = (*env)->GetMethodID(env, jFrameClass, "setSize", "(II)V");

            int frameWidth = (*env)->CallIntMethod(env, frameObject, getWidthMethod);
            int frameHeight = (*env)->CallIntMethod(env, frameObject, getHeightMethod);

            (*env)->CallVoidMethod(env, frameObject, setSizeMethod, frameWidth, frameHeight - 1);
            (*env)->CallVoidMethod(env, frameObject, setSizeMethod, frameWidth, frameHeight);
        }
    }
}

static int getJFrameTheme(JNIEnv* env, jobject frameObject) {
    if(frameObject != NULL) {
        jclass jFrameClass = (*env)->FindClass(env, "javax/swing/JFrame");

        if(isFrameVisible(env, jFrameClass, frameObject)) {
            JAWT awt = { .version = JAWT_VERSION_9 };
            JAWT_GetAWT(env, &awt);

            JAWT_DrawingSurface* surface = awt.GetDrawingSurface(env, frameObject);
            jint lock = surface->Lock(surface);
            JAWT_DrawingSurfaceInfo* surfaceInfo = surface->GetDrawingSurfaceInfo(surface);
            HWND nativeWindowHandle = ((JAWT_Win32DrawingSurfaceInfo*) surfaceInfo->platformInfo)->hwnd;

            BOOL result;
            DwmGetWindowAttribute(nativeWindowHandle, DWMWA_USE_IMMERSIVE_DARK_MODE, &result, sizeof(BOOL));

            surface->Unlock(surface);
            awt.FreeDrawingSurface(surface);

            return result;
        }

        return -1;
    }

    return -1;
}

JNIEXPORT jboolean JNICALL Java_jframetitlebar_JFrameTitlebar_isLightMode(JNIEnv* env, jclass clazz, jobject frameObject) {
    return getJFrameTheme(env, frameObject) == FALSE;
}

JNIEXPORT jboolean JNICALL Java_jframetitlebar_JFrameTitlebar_isDarkMode(JNIEnv* env, jclass clazz, jobject frameObject) {
    return getJFrameTheme(env, frameObject) == TRUE;
}

JNIEXPORT void JNICALL Java_jframetitlebar_JFrameTitlebar_setLightMode(JNIEnv* env, jclass clazz, jobject frameObject) {
    setJFrameTheme(env, frameObject, FALSE);
}

JNIEXPORT void JNICALL Java_jframetitlebar_JFrameTitlebar_setDarkMode(JNIEnv* env, jclass clazz, jobject frameObject) {
    setJFrameTheme(env, frameObject, TRUE);
}

JNIEXPORT void JNICALL Java_jframetitlebar_JFrameTitlebar_setMode(JNIEnv* env, jclass clazz, jobject frameObject, jboolean isDarkMode) {
    setJFrameTheme(env, frameObject, isDarkMode);
}