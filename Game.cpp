#include "Application.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Camera2D.h"

class PongGame : public GameEngine::Application
{
public:
    PongGame()
        : Application(GameEngine::WindowProps("Pong Game", 1280, 720))
        , Camera(-640.0f, 640.0f, -360.0f, 360.0f)
    {
        GameEngine::Renderer::Renderer2D::Init();
    }

    ~PongGame()
    {
        GameEngine::Renderer::Renderer2D::Shutdown();
    }

protected:
    void Tick(float DeltaTime) override
    {

    }

    void Render() override
    {
        GameEngine::Renderer::Renderer2D::BeginScene(Camera);

        // Left Paddle.
        GameEngine::Renderer::Renderer2D::DrawQuad({-600.0f, 0.0f}, {20.0f, 120.0f}, {1, 1, 1, 1});

        // Right Paddle.
        GameEngine::Renderer::Renderer2D::DrawQuad({600.0f, 0.0f}, {20.0f, 120.0f}, {1, 1, 1, 1});

        // Ball.
        GameEngine::Renderer::Renderer2D::DrawQuad({0.0f, 0.0f}, {20.0f, 20.0f}, {1, 1, 1, 1});

        GameEngine::Renderer::Renderer2D::EndScene();
    }

private:
    GameEngine::Renderer::Camera2D Camera;
};

int main()
{
    PongGame Game;
    Game.Run();
    return 0;
}
