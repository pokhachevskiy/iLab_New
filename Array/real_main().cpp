#include <cassert>
#include <iostream>
#include <vector>
#include "Array.hpp"
#include <cstdlib>
#include <thread>
#include <mutex>
#include <algorithm>
#define TPL template<typename T>

using std::cout;
using std::endl;
using std::thread;

////////////////
TPL
struct RuntimeLess
{
	/// Ответ будет зависеть от флага, выставляемого в момент исполнения программы
	bool inverse = false;

	bool operator()(const T& a, const T& b) const
	{
		//std::cout << std::endl<< "I'm predicate left = "<<a<<", b = "<<b <<std::endl;
		return inverse ? (a < b) : (a > b);
	}
};

template <typename typeIterator, typename TPredicate>
void customSort(typeIterator first, typeIterator last, TPredicate predicate)
{
	for (auto i = first; i != (last - 1); ++i)
		for (auto j = i + 1; j != (last); ++j)
			if (predicate(*i, *j))
				std::swap(*i, *j);
}




template <typename typeIterator, typename TPredicate>
void merge(const typeIterator begin, const typeIterator mid, const typeIterator end, TPredicate predicate)
{
	Array<typename typeIterator::value_type> buffer(distance(begin, end));
	buffer.clear();
	typeIterator it_l(begin), it_r(mid);
	const typeIterator it_mid(mid), it_end(end);

	while (it_l != it_mid && it_r != it_end)
	{
		buffer.push_back(predicate(*it_l, *it_r) ? *(it_l++) : *(it_r++));
	}

	buffer.insert(buffer.end(), it_l, it_mid);
	buffer.insert(buffer.end(), it_r, it_end);
	it_l = begin;

	for (auto iter = buffer.begin(); iter != buffer.end(); ++iter, ++it_l)
		*it_l = *iter;
}
template <typename typeIterator, typename TPredicate>
void Merge_Sort_without_threads(typeIterator first, typeIterator last, TPredicate predicate)
{
	auto size = distance(first, last);
	if (size < 2)
		return;
	auto mid = first + size / 2;

	Merge_Sort_without_threads(first, mid, predicate);
	Merge_Sort_without_threads(mid, last, predicate);

	merge(first, mid, last, predicate);
}



template <typename typeIterator, typename TPredicate>
void MergeSort(typeIterator first, typeIterator last, TPredicate predicate)
{
	static int flag = 0;

	auto size = distance(first, last);
	if (size < 2)
		return;
	auto mid = first + size / 2;
	if (flag < thread::hardware_concurrency())
	{
		flag += 2;
		thread t1(MergeSort<typeIterator, TPredicate>, first, mid, predicate);
		thread t2(MergeSort<typeIterator, TPredicate>, mid, last, predicate);

		t1.join();
		t2.join();
		merge(first, mid, last, predicate);
	}
	else
	{
		MergeSort(first, mid, predicate);
		MergeSort(mid, last, predicate);

		merge(first, mid, last, predicate);
	}



}



/*void threadFunction(A& a, const int threadNumber) {
std::cout << "thread #" << threadNumber
<< ": a.counter() before == " << a.counter() << std::endl;
a.increaseCounterWithLockGuard();
std::cout << "thread #" << threadNumber
<< ": a.counter() after == " << a.counter() << std::endl;
}*/





using std::vector;




int main()
{
	unsigned concurentThreadsSupported = thread::hardware_concurrency();
	cout << endl << concurentThreadsSupported << endl;


	const size_t N = 15000000;
	Array<int> a(N);
	Array<int> b(N);
	vector<int> c(N);
	//std::vector<int> a(N);
	for (auto& i : c)
		i = rand() % N;
	b.clear();
	a.clear();
	b.insert(b.begin(), c.begin(), c.end());
	a.insert(a.begin(), c.begin(), c.end());
	// for (auto i:a)
	//     cout<<i << " ";
	cout << endl;
	RuntimeLess<int> runtimeless;
	runtimeless.inverse = 1;


	auto t1 = std::chrono::high_resolution_clock::now();
	MergeSort(a.begin(), a.end(), [](int& a, int& b) { return a < b; });
	//customSort(a.begin(), a.end(), [](int& a, int& b) { return a < b;});


	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "Merge with current_support threads, seconds = " <<
		std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1e+6 << std::endl;



	t1 = std::chrono::high_resolution_clock::now();
	Merge_Sort_without_threads(b.begin(), b.end(), [](int& a, int& b) { return a < b; });


	t2 = std::chrono::high_resolution_clock::now();
	std::cout << " Merge (without threads), seconds = " <<
		std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1e+6 << std::endl;


	t1 = std::chrono::high_resolution_clock::now();
	std::sort(c.begin(), c.end(), runtimeless);

	t2 = std::chrono::high_resolution_clock::now();
	std::cout << "std::sort (without threads), seconds = " <<
		std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1e+6 << std::endl;
	
	// for (auto i:a)
	//     cout<< i << " ";
	//cout << endl;
	//for (auto i : b)
	//	cout << i << " ";


	system("pause");
	return 0;
}
