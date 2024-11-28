#include "Logger.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>

namespace Colors {
  constexpr const char* WHITE  = "\033[37m";
  constexpr const char* GREEN  = "\033[32m";
  constexpr const char* YELLOW = "\033[33m";
  constexpr const char* RED    = "\033[31m";
  constexpr const char* RESET  = "\033[0m";
}

namespace Util {
  Logger::Logger(const std::string& module_name) : mod_name(module_name) {
    LoggerManager::GetInstance().Start();
  }

  void Logger::Log(LogLevel level, const std::string& message) {
    LogMessage msg;
    msg.level = level;
    msg.mod = mod_name;
    msg.message = message;

    // Get current timestamp
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);

    std::tm tm_now;
    localtime_r(&time_t_now, &tm_now);

    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%H:%M:%S");
    msg.timestamp = timestamp_stream.str();

    LoggerManager::GetInstance().EnqueueMessage(msg);
  }

  LoggerManager& LoggerManager::GetInstance() {
    static LoggerManager instance;
    return instance;
  }

  LoggerManager::LoggerManager() : is_running(false) {}

  LoggerManager::~LoggerManager() {
    Stop();
  }

  void LoggerManager::Start() {
    if (!is_running.exchange(true)) {
      worker_thread = std::thread(&LoggerManager::ProcessMessages, this);
    }
  }

  void LoggerManager::Stop() {
    if (is_running.exchange(false)) {
      condition.notify_all();
      if (worker_thread.joinable()) 
        worker_thread.join();
    }
  }

  void LoggerManager::EnqueueMessage(const LogMessage& msg) {
    {
      std::lock_guard<std::mutex> lock(queue_mutex);
      message_queue.push(msg);
    }
    condition.notify_one();
  }

  void LoggerManager::ProcessMessages() {
    while (is_running) {
      // Check condition
      std::unique_lock<std::mutex> lock(queue_mutex);
      condition.wait(lock, [this] {
        return !message_queue.empty() || !is_running;
      });

      // Queue management
      while (!message_queue.empty()) {
        LogMessage msg = message_queue.front();
        message_queue.pop();
        lock.unlock();

        // Process the current message
        ProcessMessage(msg);
        
        lock.lock();
      }
    }

    // After is_running is set to false, handle the enqueued messages
    std::unique_lock<std::mutex> lock(queue_mutex);
    while (!message_queue.empty()) {
        LogMessage msg = message_queue.front();
        message_queue.pop();
        lock.unlock();

        ProcessMessage(msg);
        
        lock.lock();
    }

  }

  void LoggerManager::ProcessMessage(const LogMessage& msg) {
    std::string level_str;
    std::string color_code;

    switch (msg.level) {
      case LogLevel::TRACE:
        level_str = "TRACE";
        color_code = Colors::WHITE;
        break;

      case LogLevel::INFO:
        level_str = "INFO";
        color_code = Colors::GREEN;
        break;

      case LogLevel::WARNING:
        level_str = "WARNING";
        color_code = Colors::YELLOW;
        break;

      case LogLevel::ERROR:
        level_str = "ERROR";
        color_code = Colors::RED;
        break;

      default:
        level_str = "???";
        color_code = Colors::RESET;
        break;
    }

    std::cout << color_code
      << "[" << msg.timestamp << "] "
      << "[" << msg.mod << "] "
      << "[" << level_str << "] "
      << msg.message
      << Colors::RESET << std::endl;
  }

}
