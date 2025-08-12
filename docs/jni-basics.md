
## 1. native/external关键字

### Java/Kotlin 中声明本地方法

*   Java：

        public native String getStringFromNative();

*   Kotlin：

        external fun getStringFromNative(): String

编译时不会有函数体，函数实现在 C/C++ 中通过 JNI 绑定。

## 2.参数含义

| 参数        | 含义                         |
| --------- | -------------------------- |
| `JNIEnv*` | JNI 接口指针，提供访问 Java 方法的 API |
| `jobject` | 调用这个 native 方法的 Java 实例    |
| `jclass`  | 如果是 `static` 方法，则为类对象      |

## 3.JNI 类型映射（Java ↔ C/C++）

| Java 类型   | JNI 类型                     | C/C++ 类型          |
| --------- | -------------------------- | ----------------- |
| `int`     | `jint`                     | `int`             |
| `boolean` | `jboolean`                 | `uint8_t`         |
| `byte`    | `jbyte`                    | `char`            |
| `char`    | `jchar`                    | `uint16_t`        |
| `short`   | `jshort`                   | `short`           |
| `long`    | `jlong`                    | `long long`       |
| `float`   | `jfloat`                   | `float`           |
| `double`  | `jdouble`                  | `double`          |
| `String`  | `jstring`                  | `const char*`     |
| `Object`  | `jobject`                  | `...`             |
| `Array`   | `jintArray`、`jobjectArray` | `int*`、`jobject*` |

## 4.JNI 签名格式（方法签名）

**格式**：(参数列表)返回值

基本类型签名对照表

| Java 类型   | JNI 签名 |
| --------- | ------ |
| `boolean` | `Z`    |
| `byte`    | `B`    |
| `char`    | `C`    |
| `short`   | `S`    |
| `int`     | `I`    |
| `long`    | `J`    |
| `float`   | `F`    |
| `double`  | `D`    |
| `void`    | `V`    |

引用类型（对象类型）：

    php-template
    CopyEdit
    L<完整类名>;

将包名中的 `.` 替换为 `/`

| Java 类型               | JNI 签名                  |
| --------------------- | ----------------------- |
| `java.lang.String`    | `Ljava/lang/String;`    |
| `java.util.List`      | `Ljava/util/List;`      |
| `com.example.MyClass` | `Lcom/example/MyClass;` |

数组类型签名

在类型前加 `[` 表示数组：

| Java 类型       | JNI 签名                |
| ------------- | --------------------- |
| `int[]`       | `[I`                  |
| `String[]`    | `[Ljava/lang/String;` |
| `boolean[][]` | `[[Z`                 |

举个栗子：

Kotlin代码为

    external fun sharedLibString(): String

则C/C++ 签名为

    ()Ljava/lang/String;
