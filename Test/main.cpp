#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

void thread1Function() {

}

void thread2Function() {

}

mutex mutey;

int main() {
	
	thread t1(thread1Function);
	thread t2(thread2Function);

	system("PAUSE");
	return 0;
}