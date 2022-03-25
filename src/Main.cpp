#include "Application.h"

int main(int argc, char** argv)
{
	auto app = new Application("MeshViewer");
	app->run();

	delete app;
}