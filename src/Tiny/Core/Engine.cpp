#include "Tiny/Core/Engine.h"
#include "Tiny/Core/Service.h"
#include "Tiny/Core/Time/Time.h"
#include "Tiny/Application.h"
#include "Tiny/Graphics/Scene/Scene.h"
#include "Tiny/Graphics/Mesh/Model.h"

#include <chrono>
#include <thread>

namespace Tiny{
    Engine::Engine()
    :_app(nullptr)
    ,_running(false)
    ,_input(){

    }

    void Engine::Init(Application *app){
        _app = app;

		auto time = std::make_unique<Time>();
		Service::SetTime(std::move(time));

		auto fm = std::make_unique<FrameManager>();
		Service::SetFrameManager(std::move(fm));

		Service::Time().Init();
    }

    /*
    @brief  main loop
    @caution:
    游戏主循环采用fixed-stamp模式，逻辑帧以固定间隔更新， 渲染帧以最大帧率更新。
    render world落后logical world一帧， render world采用logical world插值后的结果进行渲染。

    |______|_________|_________|         <-Render frame.
    R1    R2        R3        R4
    |____|____|____|____|____|____|____|      <-Logical frame.
    L1   L2   L3   L4   L5   L6   L7   L8
    渲染时，
    t = (Time(Current Render Frame) - Time(next logical frame)) / Time(logical frame delta)
    Status(Render)  = lerp(Status(last logical frame), Status(current logical frame),  t)
    以Status(Render)的结果进行渲染。(如位置，缩放，角度，透明度等等一切属性)

    Reference :
    1. https://gafferongames.com/post/fix_your_timestep/
    2. http://lspiroengine.com/?p=378
    3. http://www.kinematicsoup.com/news/2016/8/9/rrypp5tkubynjwxhxjzd42s3o034o8
    */
#ifdef TINY_DEBUG
    constexpr double DebugFrameDelta = 500;
#endif
    /*
        TODO:
            1. high resolution timer?
    */
    void Engine::StartUp(){
        if(!_app){
            Service::Log().E("Engine Initialized failed, crash!");

			_app->GetAppPath(); //cause crash
        }

		//debug test
		Tiny::Graphics::Scene::Instance().CreateMainCamera();
		_input.RegisterMouseBtn(Tiny::Graphics::CameraRotate);
		_input.RegisterKeyboard(Tiny::Graphics::ProcessKeyBoard);


		std::string vpath = "E:\\MyProject\\Bootstrap\\Tiny\\content\\Shader\\default.vshader";
		std::string fpath = "E:\\MyProject\\Bootstrap\\Tiny\\content\\Shader\\default.fshader";
		std::string modelPath = "E:\\MyProject\\Bootstrap\\Tiny\\content\\Models\\nanosuit\\nanosuit.obj";

		std::shared_ptr<Tiny::Graphics::Shader> shader = Tiny::ResourceLoader::Instance().LoadShader(vpath, fpath);
		static Tiny::Graphics::Model* TestModel = Tiny::Graphics::Model::New("TestModel", modelPath, shader);
		TestModel->Load();
		Tiny::Graphics::Object* model = Tiny::Graphics::Scene::Instance().FindObject("TestModel");
		model->Transform().setPosition({ 30.f,-10.f,10.f });
		model->Transform().setEulerAngles({ 0.f, 180.f,0.f });
		model->Transform().setScale({ 5.f, 5.f, 5.f });

		std::string vSpath = "E:\\MyProject\\Bootstrap\\Tiny\\content\\Shader\\skinedmesh.vshader";
		std::string fSpath = "E:\\MyProject\\Bootstrap\\Tiny\\content\\Shader\\default.fshader";
		std::string modelSPath = "C:\\Users\\Administrator\\Desktop\\extern\\ogldev-source\\Content\\boblampclean.md5mesh";

		std::shared_ptr<Tiny::Graphics::Shader> shaderS = Tiny::ResourceLoader::Instance().LoadShader(vSpath, fSpath);
		static Tiny::Graphics::Model* SkinedModel = Tiny::Graphics::Model::New("SkinedModel", modelSPath, shaderS);
		SkinedModel->Load();
		Tiny::Graphics::Object* modelS = Tiny::Graphics::Scene::Instance().FindObject("SkinedModel");
		modelS->Transform().setPosition({ 0.f,-10.f,10.f });
		modelS->Transform().setEulerAngles({ 90.f, 0.f,180.f });
		modelS->PlayAnim(0, Tiny::Graphics::comSkinedMesh::AnimMode::LOOP);
		std::string exepath = Tiny::FileSystem::GetExePath();
		//debug test

        double logicalDelta = Service::FrameManager().GetLogicalFrameDelta() * 1000;
        double targetDelta = Service::FrameManager().GetTargetFrameDelta() * 1000;

        LogicalUpdate();

		double lastTime = Service::Time().GetTime(TimePrecision::MICROSEC) / 1000.0;
        double logicalAccumulator = 0.0;

        //test code for total frame rate control
        double sleepCalibrating = 0.0;
        _running = true;

        while(true){
            if(!_running)
                break;

            double currentTime = Service::Time().GetTime(TimePrecision::MICROSEC) / 1000.0;
            double delta = currentTime - lastTime;
            lastTime = currentTime;

#ifdef TINY_DEBUG
            double breakpointCorrection = 0.0;
            if(delta > DebugFrameDelta){ //当Debug模式开启 且 一帧时间大于DebugFrameDelta时, 认为断点影响了游戏逻辑执行， 在此进行时间修正，以防止断点后逻辑帧在一帧里执行过多次
                breakpointCorrection = delta - targetDelta;
                delta = targetDelta;
            }
#endif
			Service::FrameManager().OnFrameBegin(currentTime, delta);

            //test code for total frame rate control
            sleepCalibrating += targetDelta - delta;
            if(sleepCalibrating > 0){
                double beforeSleep = Service::Time().GetTime(TimePrecision::MICROSEC) / 1000.0;
                std::this_thread::sleep_for(std::chrono::milliseconds((int)(sleepCalibrating )));
                sleepCalibrating -= Service::Time().GetTime(TimePrecision::MICROSEC) / 1000.0 - beforeSleep;
            }

			_input.Poll();
            logicalAccumulator += delta;
            //Service::Log().W("MainLoop: logicalAccumulator {}f, delta {}f", logicalAccumulator, delta);
            while(logicalAccumulator >= logicalDelta){
                LogicalUpdate();
                logicalAccumulator -= logicalDelta;
            }

            RenderUpdate();

            _app->OnFrameDone();
        }
    }

    /*
    @brief  update logical world.
    */
    void Engine::LogicalUpdate(){
        Service::FrameManager().OnLogicalFrameBegin();
        //input should be processed befor all logic start.
		_input.Update();

        //TODO

        //time system should be update after all logic end.
		Service::Time().Update();
    }

    /*
    @brief  update render world.
    */
    void Engine::RenderUpdate(){

        _app->OnRenderFrameDone();
    }

    void Engine::ShutDown(){
        _running = false;
    }
}
