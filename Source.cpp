#include <iostream>
#include <thread>
#include <mutex>


using namespace std;
using namespace std::chrono;

static int arb = 1000000; //modern cpus cap at ~ 1 million simple read write on int

mutex Mutex;

int ThreadVar = 0;
int ThreadVarA = 0;
char UserInput;

void routine();
void routineA();


int main() {
	auto start = high_resolution_clock::now();

	cout << "hello world " << endl;

	thread Hello(routine);
	thread Goodbye(routine);

	Hello.join();
	Goodbye.join();//this returns the above thread process in sync with the main thread //Absoluetly neccesary 

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "We are running the threads using the lock and unlock functions and was performed in " << duration.count() / 1000000.0f << " seconds. " << endl;
	cout << "ThreadVar: " << ThreadVar << endl;

	thread HelloA(routineA);
	thread GoodbyeA(routineA);

	HelloA.join();
	GoodbyeA.join();

	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);

	cout << "ThreadVarA: " << ThreadVarA << endl;
	cout << "We are running the threads using the sleep_for function and was performed in " << duration.count() / 1000000.0f << " seconds. " << endl;

	return 0;
}

void routine()
{
	Mutex.lock();
		for (int i = 0; i < arb;i++) {
			ThreadVar++;
		}
	Mutex.unlock();
}

void routineA() {
	this_thread::sleep_for(chrono::milliseconds(1000));
	for (int i = 0; i < arb;i++) {
		ThreadVarA++;
	}

}
