#include <Eis.h>
#include <Eis/Core/EntryPoint.h>

#include "CarDot.h"

class App : public Eis::Application
{
public:
	App()
	{
		PushLayer(new CarDot());
	}

	~App() = default;
};

Eis::Application* Eis::CreateApplication()
{
	return new App();
}