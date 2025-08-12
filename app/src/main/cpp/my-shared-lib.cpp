#include <jni.h>
#include <string>

jstring sharedLibString(JNIEnv* env, jclass /* this */) {
    std::string hello = "Hello from shared lib";
    return env->NewStringUTF(hello.c_str());
}

void setPerson(JNIEnv *env, jclass clazz, jobject person) {
    // 获取 person 的 class 对象
    jclass pJclass = env->GetObjectClass(person);

    // --- Name 相关处理 ---
    jmethodID getNameMethod = env->GetMethodID(pJclass, "getName", "()Ljava/lang/String;");
    auto originalName = (jstring)env->CallObjectMethod(person, getNameMethod);
    const char *c_name = env->GetStringUTFChars(originalName, nullptr);
    jstring str = env->NewStringUTF(c_name);
    jmethodID setNameMethod = env->GetMethodID(pJclass, "setName", "(Ljava/lang/String;)V");
    env->CallVoidMethod(person, setNameMethod, str);
    env->ReleaseStringUTFChars(originalName, c_name);

    // --- Age 相关处理 ---
    jmethodID getAgeMethod = env->GetMethodID(pJclass, "getAge", "()I");
    jint age = env->CallIntMethod(person, getAgeMethod);
    jmethodID setAgeMethod = env->GetMethodID(pJclass, "setAge", "(I)V");
    env->CallVoidMethod(person, setAgeMethod, age);
}

//返回java层对象
jobject getPerson(JNIEnv *env, jclass clazz) {
    //获取 person 的 class对象
    jclass pJclass = env->FindClass("com/jni/data/model/Person");
    //获取到构造函数的methodId
    jmethodID jmethodID1 = env->GetMethodID(pJclass, "<init>", "(Ljava/lang/String;I)V");
    char *back_name = "wangmeimei";
    jint age = 23;
    jstring str = env->NewStringUTF(back_name);
    //NewObject，根据class对象返回一个实例对象
    jobject perosn = env->NewObject(pJclass, jmethodID1, str, age);
    return perosn;
}

void setStudent(JNIEnv *env, jclass clazz, jobject student) {
    //获取person的class对象
    jclass sJclass = env->GetObjectClass(student);
    // --- Name 相关处理 ---
    jmethodID getNameMethod = env->GetMethodID(sJclass, "getName", "()Ljava/lang/String;");
    auto originalName = (jstring)env->CallObjectMethod(student, getNameMethod);
    const char *c_name = env->GetStringUTFChars(originalName, nullptr);
    jstring name = env->NewStringUTF(c_name);
    jmethodID setNameMethod = env->GetMethodID(sJclass, "setName", "(Ljava/lang/String;)V");
    env->CallVoidMethod(student, setNameMethod, name);
    env->ReleaseStringUTFChars(originalName, c_name);

    // --- Age 相关处理 ---
    jmethodID getAgeMethod = env->GetMethodID(sJclass, "getAge", "()I");
    jint age = env->CallIntMethod(student, getAgeMethod);
    jmethodID setAgeMethod = env->GetMethodID(sJclass, "setAge", "(I)V");
    env->CallVoidMethod(student, setAgeMethod, age);
}

jobject getStudent(JNIEnv *env, jclass clazz) {
    jclass jclass1 = env->FindClass("com/jni/data/model/Student");
    // 数据类主构造函数签名需要与Kotlin定义完全一致
    // 假设Student定义为: data class Student(val age: Int, val name: String)
    // jmethodID jmethodID1 = env->GetMethodID(jclass1, "<init>", "(ILjava/lang/String;)V");

    // 如果参数顺序不同(如name在前)，需要调整签名和传参顺序:
     jmethodID jmethodID1 = env->GetMethodID(jclass1, "<init>", "(Ljava/lang/String;I)V");

    jint age = 26;
    jstring str = env->NewStringUTF("xiaoming");
    jobject student = env->NewObject(jclass1, jmethodID1, str, age);
    return student;
}

jint registerMethod(JNIEnv* env) {
    jclass clz = env->FindClass("com/jni/data/JniHelper");
    JNINativeMethod jniNativeMethod[] = {
            {"sharedLibString", "()Ljava/lang/String;", (void*) sharedLibString},
                { "setPerson", "(Lcom/jni/data/model/Person;)V", (void *) setPerson} ,
            {"getPerson", "()Lcom/jni/data/model/Person;", (void *) getPerson},
            {"changeStudentName", "(Lcom/jni/data/model/Student;)V", (void *) setStudent},
            {"getStudent", "()Lcom/jni/data/model/Student;", (void *) getStudent},
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