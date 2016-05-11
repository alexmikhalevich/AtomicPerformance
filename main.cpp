#include "ctest.hpp"
#include "gnuplot-iostream/gnuplot-iostream.h"

int main() {
	Gnuplot gp;
	SHalfCacheLine hcl_1, hcl_2;
	SOneCacheLine ocl_1, ocl_2, ocl_3;
	SPartiallyInCacheLine pcl;
	
	std::vector<std::vector<double>> investigation_2 = CTest::test<SOneCacheLine, SPartiallyInCacheLine>(&ocl_3, NULL, &pcl, NULL);
	gp << "set title 'Second case'" << std::endl;
	gp << "set key invert reverse Left outside" << std::endl;
	gp << "set style data histogram" << std::endl;
	gp << "set style histogram clustered" << std::endl;
	gp << "set style fill solid border -1" << std::endl;
	gp << "unset xtics" << std::endl;
	gp << "set xtics ('init()' 0, 'load()' 1, 'store()' 2, 'fetch_add()' 3, 'fetch_sub()' 4, 'fetch_and()' 5, 'fetch_or()' 6, 'fetch_xor()' 7)" 
		<< "nomirror rotate by -45" << std::endl;
	gp << "set grid y" << std::endl;
	gp << "set ylabel 'Time for one operation, nanoseconds'" << std::endl;
	gp << "plot" << gp.file1d(investigation_2) << "using 2 title 'Partially', '' using 3 title 'Entirely'"  << std::endl;

/*	std::vector<std::vector<double>> investigation_3 = CTest::test<SHalfCacheLine, SOneCacheLine>(&hcl_1, &hcl_2, &ocl_1, &ocl_2);
	gp << "set title 'Two atomic variables are in the same or in different cache lines'" << std::endl;
	gp << "set key invert reverse Left outside" << std::endl;
	gp << "set style data histogram" << std::endl;
	gp << "set style histogram clustered" << std::endl;
	gp << "set style fill solid border -1" << std::endl;
	gp << "unset xtics" << std::endl;
	gp << "set xtics ('init()' 0, 'load()' 1, 'store()' 2, 'fetch_add()' 3, 'fetch_sub()' 4, 'fetch_and()' 5, 'fetch_or()' 6, 'fetch_xor()' 7)" 
		<< "nomirror rotate by -45" << std::endl;
	gp << "set grid y" << std::endl;
	gp << "set ylabel 'Time for one operation, nanoseconds'" << std::endl;
	gp << "plot" << gp.file1d(investigation_3) << "using 2 title 'The same cache line', '' using 3 title 'Different cache lines'"  << std::endl;
*/
	return 0;
}
