#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <utility>

struct SHalfCacheLine {
	std::atomic<int> atomic;
	int padding[7];
};

struct SOneCacheLine {
	std::atomic<int> atomic;
	int padding[15];
};

class CTest {
	private:
		template<class AtomicType>
		static double TestInit(AtomicType& first, AtomicType& second);
		template<class AtomicType>
		static double TestStore(AtomicType& first, AtomicType& second);
		template<class AtomicType>
		static double TestLoad(AtomicType& first, AtomicType& second);
		template<class AtomicType>
		static double TestFetchAdd(AtomicType& first, AtomicType& second);
		template<class AtomicType>
		static double TestFetchSub(AtomicType& first, AtomicType& second);
		template<class AtomicType>
		static double TestFetchAnd(AtomicType& first, AtomicType& second);
		template<class AtomicType>
		static double TestFetchOr(AtomicType& first, AtomicType& second);
		template<class AtomicType>
		static double TestFetchXor(AtomicType& first, AtomicType& second);
	public:
		template<class AtomicType_1, class AtomicType_2>
		static std::vector<std::vector<double>> test(AtomicType_1& first_1, AtomicType_1& first_2,
				AtomicType_2& second_1, AtomicType_2& second_2);
};

template<class AtomicType>
double CTest::TestInit(AtomicType& first, AtomicType& second) {
	std::chrono::system_clock::time_point begin, end;
	begin = std::chrono::system_clock::now();

	std::atomic_init<int>(&first.atomic, 0);
	std::atomic_init<int>(&second.atomic, 0);

	end = std::chrono::system_clock::now();
	std::chrono::duration<double, std::nano> elapsed_nanoseconds = end - begin;
	return elapsed_nanoseconds.count();
}
template<class AtomicType>
double CTest::TestStore(AtomicType& first, AtomicType& second) {
	std::chrono::system_clock::time_point begin, end;
	begin = std::chrono::system_clock::now();

	std::atomic_store(&first.atomic, 1);
	std::atomic_store(&second.atomic, 1);

	end = std::chrono::system_clock::now();
	std::chrono::duration<double, std::nano> elapsed_nanoseconds = end - begin;
	return elapsed_nanoseconds.count();
}
template<class AtomicType>
double CTest::TestLoad(AtomicType& first, AtomicType& second) {
	std::chrono::system_clock::time_point begin, end;
	begin = std::chrono::system_clock::now();

	std::atomic_load(&first.atomic);	
	std::atomic_load(&second.atomic);

	end = std::chrono::system_clock::now();
	std::chrono::duration<double, std::nano> elapsed_nanoseconds = end - begin;
	return elapsed_nanoseconds.count();
}
template<class AtomicType>
double CTest::TestFetchAdd(AtomicType& first, AtomicType& second) {
	std::chrono::system_clock::time_point begin, end;
	begin = std::chrono::system_clock::now();

	std::atomic_fetch_add(&first.atomic, 5);	
	std::atomic_fetch_add(&second.atomic, 5);	

	end = std::chrono::system_clock::now();
	std::chrono::duration<double, std::nano> elapsed_nanoseconds = end - begin;
	return elapsed_nanoseconds.count();
}
template<class AtomicType>
double CTest::TestFetchSub(AtomicType& first, AtomicType& second) {
	std::chrono::system_clock::time_point begin, end;
	begin = std::chrono::system_clock::now();

	std::atomic_fetch_sub(&first.atomic, 2);
	std::atomic_fetch_sub(&second.atomic, 2);

	end = std::chrono::system_clock::now();
	std::chrono::duration<double, std::nano> elapsed_nanoseconds = end - begin;
	return elapsed_nanoseconds.count();
}
template<class AtomicType>
double CTest::TestFetchAnd(AtomicType& first, AtomicType& second) {
	std::chrono::system_clock::time_point begin, end;
	begin = std::chrono::system_clock::now();

	std::atomic_fetch_and(&first.atomic, 9);	
	std::atomic_fetch_and(&second.atomic, 9);	

	end = std::chrono::system_clock::now();
	std::chrono::duration<double, std::nano> elapsed_nanoseconds = end - begin;
	return elapsed_nanoseconds.count();
}
template<class AtomicType>
double CTest::TestFetchOr(AtomicType& first, AtomicType& second) {
	std::chrono::system_clock::time_point begin, end;
	begin = std::chrono::system_clock::now();

	std::atomic_fetch_or(&first.atomic, 9);	
	std::atomic_fetch_or(&second.atomic, 9);	

	end = std::chrono::system_clock::now();
	std::chrono::duration<double, std::nano> elapsed_nanoseconds = end - begin;
	return elapsed_nanoseconds.count();
}
template<class AtomicType>
double CTest::TestFetchXor(AtomicType& first, AtomicType& second) {
	std::chrono::system_clock::time_point begin, end;
	begin = std::chrono::system_clock::now();

	std::atomic_fetch_xor(&first.atomic, 9);	
	std::atomic_fetch_xor(&second.atomic, 9);	

	end = std::chrono::system_clock::now();
	std::chrono::duration<double, std::nano> elapsed_nanoseconds = end - begin;
	return elapsed_nanoseconds.count();
}
template<class AtomicType_1, class AtomicType_2>
std::vector<std::vector<double>> CTest::test(AtomicType_1& first_1, AtomicType_1& first_2, 
		AtomicType_2& second_1, AtomicType_2& second_2) {
	std::vector<std::vector<double>> result = { { 1, CTest::TestInit<AtomicType_1>(first_1, first_2), CTest::TestInit<AtomicType_2>(second_1, second_2) },
		{ 2, CTest::TestLoad<AtomicType_1>(first_1, first_2), CTest::TestLoad<AtomicType_2>(second_1, second_2) },
		{ 3, CTest::TestStore<AtomicType_1>(first_1, first_2), CTest::TestStore<AtomicType_2>(second_1, second_2) },
		{ 4, CTest::TestFetchAdd<AtomicType_1>(first_1, first_2), CTest::TestFetchAdd<AtomicType_2>(second_1, second_2) },
		{ 5, CTest::TestFetchSub<AtomicType_1>(first_1, first_2), CTest::TestFetchSub<AtomicType_2>(second_1, second_2) },
		{ 6, CTest::TestFetchAnd<AtomicType_1>(first_1, first_2), CTest::TestFetchAnd<AtomicType_2>(second_1, second_2) },
		{ 7, CTest::TestFetchOr<AtomicType_1>(first_1, first_2), CTest::TestFetchOr<AtomicType_2>(second_1, second_2) },
		{ 8, CTest::TestFetchXor<AtomicType_1>(first_1, first_2), CTest::TestFetchXor<AtomicType_2>(second_1, second_2) } };
	return result;
}
