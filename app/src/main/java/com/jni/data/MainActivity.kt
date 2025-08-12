package com.jni.data

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.jni.data.databinding.ActivityMainBinding
import com.jni.data.model.Person
import com.jni.data.model.Student

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = JniHelper.sharedLibString()
        binding.setPerson.setOnClickListener {
            val person = Person("Doe", 20)
            JniHelper.changePersonName(person)
            binding.sampleText.text = buildString {
                append(person.name)
                append("_")
                append(person.age)
            }
        }
        binding.getPerson.setOnClickListener {
            val person = JniHelper.getPerson()
            binding.sampleText.text = buildString {
                append(person.name)
                append("_")
                append(person.age)
            }
        }
        binding.setStudent.setOnClickListener {
            val student = Student("s_zhang3", 22)
            JniHelper.changeStudentName(student)
            binding.sampleText.text = buildString {
                append(student.name)
                append("_")
                append(student.age)
            }
        }
        binding.getStudent.setOnClickListener {
            val student = JniHelper.getStudent()
            binding.sampleText.text = buildString {
                append(student.name)
                append("_")
                append(student.age)
            }
        }
    }
}