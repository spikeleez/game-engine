#include "Application.h"

class PongGame : public GameEngine::Application
{
public:
    PongGame()
        : Application(GameEngine::WindowProps("Pong Game", 1280, 720))
    {}

protected:
    void Tick(float DeltaTime) override {}
    void Render() override {}
};

int main()
{
    PongGame Game;
    Game.Run();
    return 0;
}
