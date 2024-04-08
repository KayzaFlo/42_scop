#include "Objimp.hpp"

Camera	camera(Vector3(0.0f, 1.8f, 6.0f));


int main(int argc, char const *argv[])
{
	if (argc != 2)
		return 1;
	Objimp obj(argv[1]);
	return 0;
}
