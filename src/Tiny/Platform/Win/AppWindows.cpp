#include "gl3w/GL/gl3w.h"
#include "GLFW/glfw3.h"
#include <string>

#include "Tiny/Core/Engine.h"
#include "Tiny/Core/Service.h"
#include "Tiny/Input/Module/KeyboardMouseModule.h"
#include "Tiny/Input/Module/JoypadModule.h"
#include "Tiny/Platform/Win/GLFWKeyMap.h"
#include "Tiny/Application.h"

const int DEFAULT_WIDTH = 640;
const int DEFAULT_HEIGHT = 480;
const char DEFAULT_TITLE[] = "GL";

using namespace Tiny;

class AppWin :public Application{
public:
    AppWin(){
        std::fill(std::begin(_mouseBtnPress), std::end(_mouseBtnPress), false);
    }

    ~AppWin() = default;

    void OnCreate() {
        _title = DEFAULT_TITLE;
        _resolution.X() = DEFAULT_WIDTH;
        _resolution.Y() = DEFAULT_HEIGHT;

        InitFileSystem();
        InitLogger();
        InitGraphics();
        InitInput();

        _engine.Init(this);
        _engine.StartUp();
    }

    void GetHardwareInfo(){
        //TODO:
    }

    void LoadDebugOption(){
        //TODO:
    }

    void OnQuit() {
        if(_engine.Running())
            _engine.ShutDown();

        if (_window)
            glfwDestroyWindow(_window);
        glfwTerminate();
    }

    //TODO:  大小变了以后 引擎部分应该如何响应？ 比如camera？
    void SetResolution(int x, int y) override{
        int lastWidth, lastHeight;
        glfwGetWindowSize(_window, &lastWidth, &lastHeight);
        OnResolutionChanged(lastWidth, lastHeight);
        _resolution.X() = x;
        _resolution.Y() = y;
    }

    Math::Vector2i GetResolution() override{
        return _resolution;
    }

	const std::string& GetAppPath() const override {
		return _appPath;
	}

private:
    void OnResolutionChanged(int lastX, int lastY) override{

    }

    void OnRenderFrameDone() override{
        glfwSwapBuffers(_window);
    }

    void OnFrameDone() override{
        if (glfwWindowShouldClose(_window))
            _engine.ShutDown();
    }

private:
    void InitFileSystem(){

    }

    void InitLogger(){
		std::list<std::unique_ptr<IronBranch::Utility::Output>> list;
		std::unique_ptr<IronBranch::Utility::Output> output(new IronBranch::Utility::ConsoleOutput());
		list.push_back(std::move(output));
		std::unique_ptr <IronBranch::Utility::Payload> p(new IronBranch::Utility::DefaultPayload());
		auto logger = std::make_unique<IronBranch::Utility::Logger>(list, std::move(p), IronBranch::Utility::LogLevel::VERBOSE);
		Service::SetLogger(std::move(logger));
    }

    void InitGraphics(){
        if (!glfwInit()) {
            Service::Log().E("GLFW Init Failed!");
            return ;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

        _window = glfwCreateWindow(_resolution.X(), _resolution.Y(), _title.c_str(), NULL, NULL);
        if (!_window) {
            Service::Log().E("glfwCreatwWindow failed!\n");
            return ;
        }


        glfwSetErrorCallback([](int error, const char* description) -> void {
            Service::Log().E("GLFW Graphics error:{} , desc:{} \n", error, description);
        });

        glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        });

		glfwMakeContextCurrent(_window);

        if (gl3wInit()) {
            Service::Log().E("gl3w Init Failed!\n");
            return;
        }

        if (!gl3wIsSupported(4, 5)) {
            Service::Log().E("OpenGL 4.5 is not supported!\n");
            return;
        }

        LogGLInfo();
    }

    void LogGLInfo(){
        Service::Log().I("OpenGL Info:\n");
        Service::Log().I("\tVersion: {}\n", glGetString(GL_VERSION));

        Service::Log().I("OpenGL Info Done.\n\n");

        Service::Log().I("GLSL Info:\n");
        Service::Log().I("\tVerion: {}\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

        int nVertexAttribs;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nVertexAttribs);
        Service::Log().I("\tMax num of Vertex attributes supported:{}\n", nVertexAttribs);

        GLint units;
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &units);
        Service::Log().I("\tMax num of Textue Units supported:{}\n", units);

        Service::Log().I("GLSL Info Done.\n\n");
    }

    void InitInput(){
        _kmModule.SetPollTrigger([this]()-> void{
            std::fill(std::begin(this->_mouseBtnEventProcess), std::end(this->_mouseBtnEventProcess), false);

            glfwPollEvents();

            /*
                由于glfwSetMouseButtonCallback只有在鼠标按钮状态变化（按下/抬起）时才会被触发
                当处于按下状态时， KeyboardMouseModule需要在每一次poll时都都获得按下的数据。
                所以在每次poll结束时， 根据当前按钮的按下/抬起状态以及本次poll过程中是否发送过数据，决定是否要补发一次mousebtndata
            */
            double x, y;
            glfwGetCursorPos(_window, &x, &y);

            for(int i = 0 ; i < 3 ; i++){
                if(this->_mouseBtnPress[i] && !this->_mouseBtnEventProcess[i]){
                    Tiny::Input::MOUSEBTN tinyKey = GLFWMouse2TinyMouse(GLFW_MOUSE_BUTTON_LEFT + i);

                    Tiny::Input::KeyboardMouseModule::MouseBtnData data;
					data.btn = tinyKey;
                    data.pressed = true;
                    data.holding = true;
                    data.pos = Math::Vector2f((float)x, _resolution.Y() - (float)y);

					_kmModule.ReceiveMouseBtn(data);
                }
            }
        });

        _engine.GetInputSystem().AddInputModule(&_kmModule);
        _engine.GetInputSystem().AddInputModule(&_jpModule, false);

        glfwSetWindowUserPointer(_window, this);

        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        //glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xPos, double yPos) -> void {
            AppWin *app = (static_cast<AppWin*>(glfwGetWindowUserPointer(window)));
            app->_kmModule.ReceiveMousePos(Math::Vector2f((float)xPos, app->_resolution.Y() - (float)yPos)); //transfer from glfw screen coordinate to tiny screen coordinate
        });

        glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mode) {
            AppWin *app = (static_cast<AppWin*>(glfwGetWindowUserPointer(window)));

            Tiny::Input::MOUSEBTN tinyBtn = GLFWMouse2TinyMouse(button);
            if(tinyBtn == Tiny::Input::MOUSEBTN::INVALID)
                return;

            app->_SetMoustBtn(tinyBtn, action == GLFW_PRESS);
        });

        glfwSetScrollCallback(_window, [](GLFWwindow* window, double xoffset, double yoffset){
            AppWin *app = (static_cast<AppWin*>(glfwGetWindowUserPointer(window)));
            Tiny::Input::MOUSEBTN scrollBtn = yoffset > 0 ? Tiny::Input::MOUSEBTN::MOUSE_MIDDLE_BTN_SCROLL_UP : Tiny::Input::MOUSEBTN::MOUSE_MIDDLE_BTN_SCROLL_DOWN;

            Tiny::Input::KeyboardMouseModule::MouseBtnData data;
            data.btn = scrollBtn;
            app->_kmModule.ReceiveMouseBtn(data);
        });

        glfwSetKeyCallback(_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) -> void {
            AppWin *app = (static_cast<AppWin*>(glfwGetWindowUserPointer(window)));
            Tiny::Input::KeyboardMouseModule::KeyboardData k;
            k.key = GLFWKey2TinyKey(key);
            k.pressed = action != GLFW_RELEASE;
            k.holding = action == GLFW_REPEAT;
            app->_kmModule.ReceiveKeyboard(k);
        });
    }


    void _SetMoustBtn(Tiny::Input::MOUSEBTN btn, bool press){
        double x, y;
        glfwGetCursorPos(_window, &x, &y);
        int localIndex = -1;
		switch (btn) {
		case Tiny::Input::MOUSEBTN::MOUSE_LEFT_BTN:
			localIndex = 0;
			break;
		case Tiny::Input::MOUSEBTN::MOUSE_RIGHT_BTN:
			localIndex = 1;
			break;
		case Tiny::Input::MOUSEBTN::MOUSE_MIDDLE_BTN:
			localIndex = 2;
			break;
		}
        if(localIndex == -1){
			Service::Log().E("AppWindows: Invalid Tiny::Input::MOUSEBTN");
            return;
        }

        Tiny::Input::KeyboardMouseModule::MouseBtnData data;
        data.btn = btn;
        data.pressed = press;
        data.holding = false;
        data.pos = Math::Vector2f((float)x, _resolution.Y() - (float)y);
		_kmModule.ReceiveMouseBtn(data);

        _mouseBtnPress[localIndex] = press;
		_mouseBtnEventProcess[localIndex] = true;
    }

private:
    GLFWwindow* _window{nullptr};

    std::string _title;
	std::string _appPath;

    Math::Vector2i _resolution;

    Tiny::Input::KeyboardMouseModule    _kmModule;
    Tiny::Input::JoypadModule           _jpModule;

    bool    _mouseBtnPress[3]; //0代表左键，1代表右键，2代表中键
    bool    _mouseBtnEventProcess[3];
};

/*
    TODO:
    1.parse arg
*/
void main(int argc, char **argv){
    AppWin app;

    app.OnCreate();
    app.OnQuit();
}
