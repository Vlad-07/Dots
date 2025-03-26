#include <Eis.h>
#include <Eis/Core/EntryPoint.h>

#include "AICar.h"

class App : public Eis::Application
{
public:
	App()
	{
		PushLayer(new AICar());
	}

	~App() = default;
};

Eis::Application* Eis::CreateApplication()
{
	return new App();
}