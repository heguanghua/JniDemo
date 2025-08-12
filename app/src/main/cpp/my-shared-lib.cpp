#include <jni.h>
#include <string>

jstring sharedLibString(JNIEnv* env, jclass /* this */) {
    std::string hello = "Hello from shared lib";
    return env->NewStringUTF(hello.c_str());
}

void changePersonName(JNIEnv *env, jclass clazz, jobject person) {
    //获取person的class对象
    jclass student = env->GetObjectClass(person);
    //获取setName方法的id
    jmethodID setNameMethond = env->GetMethodID(student, "setName", "(Ljava/lang/String;)V");
    char *c_new_name = "p_xiaoming";
    jstring str = env->NewStringUTF(c_new_name);
    //调用方法，因为返回值是void，所以是CallVoidMethod，再把改变后的str传进去
    env->CallVoidMethod(person, setNameMethond, str);
}

//返回java层对象
jobject returnPerson(JNIEnv *env, jclass clazz) {
    //获取到person class对象
    jclass jclass1 = env->FindClass("com/jni/data/model/Person");
    //获取到构造函数的methodId
    jmethodID jmethodID1 = env->GetMethodID(jclass1, "<init>", "(Ljava/lang/String;I)V");
    char *back_name = "p_wangmeimei";
    jint age = 233;
    jstring str = env->NewStringUTF(back_name);
    //NewObject，根据class对象返回一个实例对象
    jobject perosn = env->NewObject(jclass1, jmethodID1, str, age);
    return perosn;
}

void changeStudentName(JNIEnv *env, jclass clazz, jobject person) {
    //获取person的class对象
    jclass student = env->GetObjectClass(person);
    //获取setName方法的id
    jmethodID setNameMethond = env->GetMethodID(student, "setName", "(Ljava/lang/String;)V");
    char *c_new_name = "s_wang5";
    jstring str = env->NewStringUTF(c_new_name);
    //调用方法，因为返回值是void，所以是CallVoidMethod，再把改变后的str传进去
    env->CallVoidMethod(person, setNameMethond, str);
}

jobject returnStudent(JNIEnv *env, jclass clazz) {
    jclass jclass1 = env->FindClass("com/jni/data/model/Student");
    // 数据类主构造函数签名需要与Kotlin定义完全一致
    // 假设Student定义为: data class Student(val age: Int, val name: String)
    // jmethodID jmethodID1 = env->GetMethodID(jclass1, "<init>", "(ILjava/lang/String;)V");

    // 如果参数顺序不同(如name在前)，需要调整签名和传参顺序:
     jmethodID jmethodID1 = env->GetMethodID(jclass1, "<init>", "(Ljava/lang/String;I)V");

    jint age = 26;
    jstring str = env->NewStringUTF("s_ma6");
    jobject student = env->NewObject(jclass1, jmethodID1, str, age);
    return student;
}

jint registerMethod(JNIEnv* env) {
    jclass clz = env->FindClass("com/jni/data/JniHelper");
    JNINativeMethod jniNativeMethod[] = {
            {"sharedLibString", "()Ljava/lang/String;", (void*) sharedLibString},
                { "changePersonName", "(Lcom/jni/data/model/Person;)V", (void *) changePersonName} ,
            {"getPerson", "()Lcom/jni/data/model/Person;", (void*) returnPerson},
            {"changeStudentName", "(Lcom/jni/data/model/Student;)V", (void *) changeStudentName},
            {"getStudent", "()Lcom/jni/data/model/Student;", (void*) returnStudent},
    };

    return env->RegisterNatives(clz, jniNativeMethod, sizeof(jniNativeMethod) / sizeof(jniNativeMethod[0]));
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;
    if (vm->GetEnv((void**)&env,JNI_VERSION_1_6)!=JNI_OK){
        return JNI_ERR;
    }
    jint result = registerMethod(env);
    return JNI_VERSION_1_6;
}