#pragma once
#ifdef GP_PLATFORM_WINDOWS

extern Grapher::Application* Grapher::CreateApp();
int main(int argc, char** argv) 
{
	Grapher::Log::Init();
	GP_CORE_WARN("Initialized Log!");
	Grapher::Application* App = new Grapher::Application;
	App->Run();
	delete App;
}
#endif // GP_PLATFORM_WINDOWS
