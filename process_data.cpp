// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant
#include <thread>
#include <mutex> // MUTual EXclusion

#include "process_data.h"

namespace sdds_ws9
{

	// The following function receives array (pointer) as the first argument, number of array
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument.
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will
	//   hold average of the array elements. When they are different, avg will hold a value called
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2.
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg)
	{
		avg = 0;
		for (int i = 0; i < size; i++)
			avg += arr[i];
		avg /= divisor;
	}
	// The following function receives array (pointer) as the first argument, number of array elements
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of
	//   the array elements. When they are different, var will hold a value called as variance factor.
	//   For part 1, you will be using same value for size and double. Use of different values for size
	//   and divisor will be useful for multi-threaded implementation in part-2.
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var)
	{
		var = 0;
		for (int i = 0; i < size; i++)
			var += (arr[i] - avg) * (arr[i] - avg);
		var /= divisor;
	}
	// The following constructor of the functor receives name of the data file, opens it in
	//   binary mode for reading, reads first int data as total_items, allocate memory space
	//   to hold the data items, and reads the data items into the allocated memory space.
	//   It prints first five data items and the last three data items as data samples.
	//
	ProcessData::ProcessData(std::string filename)
	{
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.

		// int total_items{};

		std::ifstream infile("data_int.dat", std::ios::binary);
		if (!infile)
		{
			std::cerr << "Error opening file" << std::endl;
			// return;
		}

		infile.read((char*)&total_items, sizeof(total_items));

		int i{};
		data = new int[total_items];
		while (infile.read((char*)&data[i], sizeof(i)))
		{
			// data[i] =
			i++;
			// std::cout << value << std::endl;
		}

		infile.close();

		std::cout << "Item's count in file '" << filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
			<< data[total_items - 3] << ", " << data[total_items - 2] << ", "
			<< data[total_items - 1] << "]\n";
	}

	ProcessData::~ProcessData()
	{
		delete[] data;
	}
	ProcessData::operator bool() const
	{
		return total_items > 0 && data != nullptr;
	}

	// TODO You create implementation of function operator(). See workshop instructions for details .

	int ProcessData::operator()(std::string filename, double& computedAvg, double& computedVariance)
	{
		// 		You compute the average value by calling computeAvgFactor with the following parameters: data,
		//	total_items as the size of the array, and again total_items as divisor. The fourth argument is going to
		//	be a variable in which the computed average value is to be stored.
		computeAvgFactor(data, total_items, total_items, computedAvg);
		// You compute variance value by calling computeVarFactor with first, second and third arguments same as
		//	before, i.e., in the case of computeAvgFactor. The fourth argument is the average value computed by
		//	computeAvgFactor and fifth argument is the variable in which the computed variance is to be stored.
		computeVarFactor(data, total_items, total_items, computedAvg, computedVariance);

		// You open the target data file and write the data (total_items, and data) in the format of the input data
		// 	file data_int.dat.

		std::ofstream output_file("data_int_target.dat", std::ios::in | std::ios::out | std::ios::binary); // open file for writing

		if (output_file.is_open())
		{ // check if file is open

			char* ptr = reinterpret_cast<char*>(&total_items);
			// Write total_items value to the file
			//output_file << ptr << std::endl;

			output_file.write(ptr, sizeof(data[0]));
			using namespace std;
			// Write the data values to the file
			for (int i = 0; i < total_items; ++i)
			{
				//std::this_thread::sleep_for(600ms);

				//std::cout << data[i] << " ";
				ptr = reinterpret_cast<char*>(&data[i]);
				//output_file << data[i] << std::endl;
				output_file.write(ptr, sizeof(data[0]));

			}

			output_file.close(); // close the file
		}

		return 1;
	}
}