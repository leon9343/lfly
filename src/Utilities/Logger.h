#pragma once

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

namespace Util {

  /**
   * @brief Defines the severity level of log messages
   */
  enum class LogLevel {
    TRACE,    ///< Detailed information, used for debugging or diagnosing issues
    INFO,     ///< Used to confirm that things are working as expected
    WARNING,  ///< Indicates an unexpected event or a possible, recoverable problem
    ERROR     ///< Unrecoverable problem which causes malfunction
  };

  /**
   * @brief Represents a single message with some associated metadata
   */
  struct LogMessage {
    LogLevel level;         ///< The severity of the log message
    std::string mod;        ///< The name of the module generating the message
    std::string message;    ///< The content of the log message
    std::string timestamp;  ///< The timestamp of when the log message was created
  };

  /**
   * @brief The Logger class provides an interface to log messages from different modules
   *
   * Each instance of a Logger is associated with a different module, and can show messages of
   * different severity levels. This class interfaces with LoggerManager to provide async logging
   */
  class Logger {
  public:
    /**
     * @brief Constructs a Logger for a module
     * @param module_name The name of the module associated with this Logger instance
     */
    explicit Logger(const std::string& module_name);

    /**
     * @brief Logs a message with the specified severity level
     * @param level   The severity level of the log message
     * @param message The content of the log message
     */
    void Log(LogLevel level, const std::string& message);

  private:
    std::string mod_name; ///< Name of the module associated with the logger
  };


  /**
   * @brief Manages the asynchronous logging system, handling the message queue and the various Logger instances
   *
   * The LoggerManager is implemented as a singleton to ensure only one instance handles the logging process.
   * It enqueues logs and processes them asynchronously in a separate thread to not impact performance for the 
   * main application
   */
  class LoggerManager {
  public:
    /**
     * @brief Retrieves singleton instance of LoggerManager
     * @return Reference to LoggerManager instance
     */
    static LoggerManager& GetInstance();

    /**
     * @brief Enqueues log message for asynchronous processing
     * @param msg The LogMessage to enqueue
     */
    void EnqueueMessage(const LogMessage& msg);

    /**
     * @brief Starts the worker thread if not yet running
     */
    void Start();

    /**
     * @brief Signals the worker thread to stop
     */
    void Stop();

  private:
    LoggerManager();  ///< Constructor for singleton pattern
    ~LoggerManager(); ///< Destructor to ensure proper shutdown

    /**
     * @brief The worker thread to process log messages
     *
     * This method runs in a separate thread to continually process messages
     * from the queue 
     */
    void ProcessMessages();

    /**
     * @brief Processes a single log message
     * @param msg The LogMessage to process
     */
    void ProcessMessage(const LogMessage& msg);

    std::queue<LogMessage> message_queue; ///< Thread-safe queue of logs
    std::mutex queue_mutex;               ///< Mutex to synchronize queue access
    std::condition_variable condition;    ///< Condition variable to manage thread synchronization
    std::thread worker_thread;            ///< The thread which processes logs
    std::atomic<bool> is_running;         ///< Flag indicating whether the thread should continue running
  };

}
