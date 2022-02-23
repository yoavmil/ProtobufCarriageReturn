#include "dummy.pb.h"
#include <google/protobuf/util/json_util.h>
#include <iostream>
#include <fstream>
using namespace std;

// https://stackoverflow.com/a/24315631/2378218
static inline void replaceAll(std::string &str, const std::string &from, const std::string &to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
}

int main(void)
{
	Dummy dummy;
	dummy.set_i(1);
	dummy.set_j(2);

	std::string jsonStr;
	google::protobuf::util::JsonPrintOptions opts;
	opts.always_print_primitive_fields = true;
	opts.add_whitespace = true;
	auto ret = google::protobuf::util::MessageToJsonString(dummy, &jsonStr, opts);
	if (!ret.ok())
		std::cerr << "cloud convert to json\n";

	ret = google::protobuf::util::JsonStringToMessage(jsonStr, &dummy);
	if (!ret.ok())
		std::cerr << "cloud parse regular json string\n";

	if (dummy.i() != 1 || dummy.j() != 2)
		std::cerr << "wrong values\n";

	replaceAll(jsonStr, "\n", "\r\n");

	{
		std::ofstream myfile("c:/temp/dummy.json", fstream::binary);		
		myfile << jsonStr;
		myfile.close();
	}

	ret = google::protobuf::util::JsonStringToMessage(jsonStr, &dummy);
	if (!ret.ok())
		std::cerr << "cloud parse altered json string\n";
	std::cout << jsonStr << "\n";
	if (dummy.i() != 1 || dummy.j() != 2)
		std::cerr << "wrong values\n";

	return 0;
}