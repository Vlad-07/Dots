#include <Eis.h>
#include <Eis/Core/EntryPoint.h>

#include "Dots3.h"

class App : public Eis::Application
{
public:
	App()
	{
		PushLayer(new Dots3());
	}

	~App() = default;
};

Eis::Application* Eis::CreateApplication()
{
	return new App();
}