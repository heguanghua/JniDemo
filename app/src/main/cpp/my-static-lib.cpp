#include<JNI.h>

extern "C" JNIEXPORT jint JNICALL
Java_com_jni_data_JniHelper_intFromJNI(JNIEnv* env, jclass ) {
    int number = 2;
    return static_cast<jint>(number);
}