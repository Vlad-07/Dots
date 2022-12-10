#include <Eis.h>
#include <Eis/Core/EntryPoint.h>

#include "Dots2.h"

class App : public Eis::Application
{
public:
	App()
	{
		PushLayer(new Dots2());
	}

	~App() = default;
};

Eis::Application* Eis::CreateApplication()
{
	return new App();
}