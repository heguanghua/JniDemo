package com.jni.data

import com.jni.data.model.Person
import com.jni.data.model.Student

class JniHelper {
    companion object {
        // Used to load the 'data' library on application startup.
        init {
            System.loadLibrary("data")
        }

        @JvmStatic
        external fun stringFromJNI(): String

        @JvmStatic
        external fun intFromJNI(): Int

        @JvmStatic
        external fun sharedLibString(): String

        @JvmStatic
        external fun setPerson(person: Person)

        @JvmStatic
        external fun getPerson(): Person

        @JvmStatic
        external fun changeStudentName(student: Student)

        @JvmStatic
        external fun getStudent(): Student
    }
}