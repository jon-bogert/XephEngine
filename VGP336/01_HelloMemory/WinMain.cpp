#include <XephEngine/include/XephEngine.h>

using namespace xe;
using namespace xe::Core;

class Student
{
	std::string m_name;
	int m_mark = 0;
public:
	Student() = default;
	Student(const std::string& name)
		: m_name(name)
		, m_mark(0) {}

	void SetMark(int mark)
	{
		m_mark = mark;
	}
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 200);

	Student* a = studentPool.New("Jon");
	Student* b = studentPool.New("Winter");

	std::vector<Student*> students;
	int count = 100;
	for (int i = 0; i < 100; ++i)
	{
		std::string name = "Student" + std::to_string(i);
		students.push_back(studentPool.New(name));
	}
	for (int i = 0; i < 20; ++i)
	{
		Student* student = students.back();
		students.pop_back();
		studentPool.Delete(student);
	}
	for (int i = 0; i < 50; ++i)
	{
		std::string name = "Student" + std::to_string(i);
		students.push_back(studentPool.New(name));
	}
	for (Student* student : students)
	{
		studentPool.Delete(student);
	}

	studentPool.Delete(a);
	studentPool.Delete(b);
	return 0;
}