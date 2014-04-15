#include "ProtoPlasm.h"
#include "sample_prog01.h"

int main(int argc, char const** argv)
{
	ijg::ProtoPlasm p(1200, 900, "sample_prog0101", new sample_prog01());
	return EXIT_SUCCESS;
}