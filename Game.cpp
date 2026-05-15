#include "Application.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Camera2D.h"

#define VIEW_W 1280
#define VIEW_H 720

class PongGame : public GameEngine::Core::Application
{
public:
    PongGame()
        : Application(GameEngine::Core::WindowProps("Pong Game", VIEW_W, VIEW_H))
        , Camera(-640.0f, 640.0f, -360.0f, 360.0f)
    {
        GameEngine::Renderer::Renderer2D::Init();
    }

    ~PongGame() override
    {
        GameEngine::Renderer::Renderer2D::Shutdown();
    }

    using Renderer2D = GameEngine::Renderer::Renderer2D;
    using Camera2D = GameEngine::Renderer::Camera2D;

protected:
    void BeginPlay() override
    {
        //Application::BeginPlay();
    }

    void Tick(float DeltaTime) override
    {

    }

    void Render() override
    {
        // Beginning Scene.
        Renderer2D::BeginScene(Camera);

        // Dashed Line.
        Renderer2D::DrawDashedLine({0.0f, -360.0f}, {0.0f, 360.0f}, {1, 1, 1, 0.3f}, 5.0f);

        // Paddles
        Renderer2D::DrawQuad({-600.0f, 0.0f}, {20.0f, 120.0f}, {1, 1, 1, 1});
        Renderer2D::DrawQuad({600.0f, 0.0f}, {20.0f, 120.0f}, {1, 1, 1, 1});

        // Square Ball
        Renderer2D::DrawQuad({0.0f, 0.0f}, {20.0f, 20.0f}, {1, 1, 1, 1});

        // Circle Ball.
        //Renderer2D::DrawCircle({0.0f, 0.0f}, 10.0f, {1, 1, 1, 1});

        // Ending Scene.
        Renderer2D::EndScene();
    }

private:
    Camera2D Camera;
};

int main()
{
    PongGame Game;
    Game.Run();
    return 0;
}
