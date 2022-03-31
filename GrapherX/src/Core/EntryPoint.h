#pragma once
#ifdef GP_PLATFORM_WINDOWS

extern Grapher::Application* Grapher::CreateApp();
int main(int argc, char** argv) 
{
	Grapher::Log::Init();
	GP_CORE_INFO("Window Created!");
	auto App = Grapher::CreateApp();
	App->Run();
	delete App;
}
#endif // GP_PLATFORM_WINDOWS
