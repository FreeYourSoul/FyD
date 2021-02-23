// MIT License
//
// Copyright (c) 2021 Quentin Balland
// Repository : https://github.com/FreeYourSoul/FyD
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

#ifndef FYD_INCLUDE_DATA_TYPES_HH
#define FYD_INCLUDE_DATA_TYPES_HH

#include <string>
#include <variant>
#include <vector>

namespace fyd {

template<typename T>
concept retrieve_data_source = requires(T a) {
  {a.trigger_notifications()};

  { a.key_notification_list() }
  ->std::same_as<std::string>;

  { a.key_subscription_list() }
  ->std::same_as<std::string>;

  { a.key_subscription_user(std::string()) }
  ->std::same_as<std::string>;
};

/**
 * Checker in order to ensure the data source object are following the proper requirements thanks to concept
 */
template<retrieve_data_source T>
struct check_requirement {
  static const bool CORRECT = true;
};

enum sub_type {
  YOUTUBE,
  TWITTER,
  TWITCH,
  ALL
};

struct subscription {
  std::string user;

  sub_type type;
  std::string uri_feed;

  //! possibility to filter the subscription to not receive notifications from certain type of input
  std::vector<std::string> notif_filter_regex;
};

struct notification {
  std::string name;
  std::string uri_image;
  std::string uri_hyperlink;

  sub_type type;
};

[[nodiscard]] subscription deserialize_subscription(std::string_view content);
[[nodiscard]] notification deserialize_notification(std::string_view content);

[[nodiscard]] std::string serialize(const subscription& subscription);
[[nodiscard]] std::string serialize(const notification& notification);

[[nodiscard]] std::string key_subscriptions();
[[nodiscard]] std::string key_notifications();

}// namespace fyd

#endif//FYD_INCLUDE_DATA_TYPES_HH
