#pragma once

namespace Logging {
enum class Level { VERBOSE = 0, INFO, WARNING, ERROR };
enum class Type { String, Number };
// Don't log at levels below this one
constexpr auto kMinLogLevel = Level::VERBOSE;
} // namespace Logging