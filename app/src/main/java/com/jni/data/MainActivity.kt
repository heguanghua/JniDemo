package com.jni.data

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
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
            if (binding.inputPersonName.text.isEmpty()) {
                Toast.makeText(this, "name is empty", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            if (binding.inputPersonAge.text.isEmpty() ) {
                Toast.makeText(this, "age is empty", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            val person = Person(binding.inputPersonName.text.toString(), binding.inputPersonAge.text.toString().toInt())
            JniHelper.updatePerson(person)
            binding.sampleText.text = buildString {
                append("P name: ")
                append(person.name)
                append(" | ")
                append("age: ")
                append(person.age)
            }
        }
        binding.getPerson.setOnClickListener {
            val person = JniHelper.getPerson()
            binding.sampleText.text = buildString {
                append("P name: ")
                append(person.name)
                append(" | ")
                append("age: ")
                append(person.age)
            }
        }
        binding.setStudent.setOnClickListener {
            if (binding.inputStudentName.text.isEmpty()) {
                Toast.makeText(this, "name is empty", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            if (binding.inputStudentAge.text.isEmpty() ) {
                Toast.makeText(this, "age is empty", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            val student = Student(binding.inputStudentName.text.toString(), binding.inputStudentAge.text.toString().toInt())
            JniHelper.updateStudent(student)
            binding.sampleText.text = buildString {
                append("S name: ")
                append(student.name)
                append(" | ")
                append("age: ")
                append(student.age)
            }
        }
        binding.getStudent.setOnClickListener {
            val student = JniHelper.getStudent()
            binding.sampleText.text = buildString {
                append("S name: ")
                append(student.name)
                append(" | ")
                append("age: ")
                append(student.age)
            }
        }
    }
}