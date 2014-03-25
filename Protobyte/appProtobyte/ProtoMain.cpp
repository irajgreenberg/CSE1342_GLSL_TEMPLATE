#include "ProtoPlasm.h"
#include "MyProg01.h"

int main(int argc, char const** argv)
{
	ijg::ProtoPlasm p(1500, 820, "MyProg01", new MyProg01());
	return EXIT_SUCCESS;

}