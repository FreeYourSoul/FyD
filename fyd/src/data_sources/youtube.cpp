// MIT License
//
// Copyright (c) 2021 Quentin Balland
// Repository : https://github.com/FreeYourSoul/FyS
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
//         of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//         to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//         copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//         copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//         AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <chrono>
#include <memory>

#include <fmt/format.h>

#include <data_types.hh>
#include <data_sources/youtube.hh>

constexpr auto YOUTUBE_URI = "https://socialblade.com/youtube";
constexpr auto USER_NAME_POSTFIX = "user/{}/videos";

constexpr auto REFRESH_NOTIF_RATE = std::chrono::seconds(10);

namespace fyd::source {

namespace {
std::chrono::system_clock convert_to_clock(const std::string& str) {
  return {};
}
}


youtube::~youtube() = default;

youtube::youtube() {
}

std::vector<notification> youtube::trigger_notifications() {
  return {};
}

std::string youtube::key_subscription_list() const {
  return fmt::format(FMT_STRING("{}#youtube"), key_subscriptions());
}

std::string youtube::key_subscription_user(const std::string& user) const {
  return fmt::format(FMT_STRING("{}#{}"), key_subscription_list(), user);
}

}