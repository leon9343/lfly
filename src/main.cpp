#include <App/App.h>
#include <Utilities/Logger.h>

int main(void) {
  try {
    Util::LoggerManager::GetInstance().Start();

    App::Application app("Flight Simulator", 800, 600);
    app.Run();

    Util::LoggerManager::GetInstance().Stop();
  } catch (const std::exception& e) {
    Util::LoggerManager::GetInstance().Stop();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
