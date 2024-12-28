#pragma once

#ifdef NMLS_PLATFORM_WINDOWS

extern Nameless::Application* Nameless::CreateApplication();

int main(int argc, char** argv)
{
	Nameless::Log::Init();
	NMLS_CORE_WARN("Log test");
	NMLS_INFO("Hello");

	auto app = Nameless::CreateApplication();
	app->Run();
	delete app;
}

#endif