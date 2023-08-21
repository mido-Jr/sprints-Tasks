#include "Logger.h"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;

Logger::Logger() {
    // Set default log level to Info
    setLogLevel(LogLevel::Info);
}

void Logger::initialize(const std::string& logFileName) {
    // Add common attributes
    logging::add_common_attributes();

    // Define log format
    formatter = expr::stream
            << "[" << logging::trivial::severity << "] "
            << "[" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S") << "] "
            << expr::smessage;

    // Add file sink
    logging::add_file_log(
            keywords::file_name = logFileName,
            keywords::format = formatter
    );

    // Add console sink
    logging::add_console_log(std::cout, keywords::format = formatter);
}

void Logger::setLogLevel(LogLevel level) {
    // Set the log level based on the input LogLevel
    logging::core::get()->set_filter(logging::trivial::severity >= static_cast<logging::trivial::severity_level>(level));
}

// Define the global logger
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", LogLevel)
BOOST_LOG_GLOBAL_LOGGER_INIT(global_logger, src::severity_logger_mt<LogLevel>) {
src::severity_logger_mt<LogLevel> logger;
logger.add_attribute("Severity", severity);
return logger;
}

// Explicit template instantiation
template void Logger::log(LogLevel level, const char* format, ...);
