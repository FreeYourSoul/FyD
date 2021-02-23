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

#include <memory>
#include <thread>

#include <fil/kv_db/kv_rocksdb.hh>

#include <data_sources/twitch.hh>
#include <data_sources/twitter.hh>
#include <data_sources/youtube.hh>

#include "free_data.hh"

namespace fyd {

// visitor helper
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

using data_source = std::variant<
    fyd::source::twitter,
    fyd::source::youtube,
    fyd::source::twitch>;

struct free_data::internal {
  explicit internal(const std::string& path_db)
      : db(fil::kv_rocksdb::initializer_type{path_db}),
        s({{sub_type::YOUTUBE, fyd::source::youtube()},
           {sub_type::TWITTER, fyd::source::twitter()},
           {sub_type::TWITCH, fyd::source::twitch()}}),
        pending_notifications() {
  }

  void add_notifications(std::vector<notification>&& notifs) {
    // todo
  }

  fil::kv_rocksdb_type db;

  std::map<sub_type, data_source> s;

  std::vector<notification> pending_notifications;
};

free_data::~free_data() = default;

free_data::free_data() : _impl(std::make_unique<free_data::internal>("")) {}

void free_data::acknowledge_notifications(const std::vector<notification>& notifs) {
}

std::vector<notification> free_data::retrieve_pending_notifications() {
  std::vector<notification> notifs = {};
  auto trans = _impl->db.make_transaction();
  trans->list(key_notifications(), [&notifs](std::string_view, std::string_view value) {
    notifs.emplace_back(deserialize_notification(value));
  });
  return notifs;
}

std::vector<subscription> free_data::retrieve_subscriptions(sub_type type) {
  std::vector<subscription> subs = {};

  auto subscribe_retriever = [&subs, trans = _impl->db.make_transaction()](auto&& s) {
    trans->list(s.key_subscription_list(), [&subs](std::string_view, std::string_view value) {
      subs.emplace_back(deserialize_subscription(value));
    });
  };

  if (type == sub_type::ALL) {
    for (auto& [k, source] : _impl->s) {
      std::visit(subscribe_retriever, source);
    }
  } else {
    std::visit(subscribe_retriever, _impl->s.at(type));
  }
  return subs;
}

void free_data::subscribe(const subscription& sub) {
}

void free_data::unsubscribe(const std::string& user) {
}

[[noreturn]] void free_data::run(std::chrono::seconds refresh_delay) {
  while (true) {

    // for each source type, trigger notifications and fill-up the pending notifications queue
    for (auto&& [_, source] : _impl->s) {
      std::visit(
          [this](auto&& source) {
            _impl->add_notifications(source.trigger_notifications());
          },
          source);
    }

    std::this_thread::sleep_until(std::chrono::system_clock::now() + refresh_delay);
  }
}

}// namespace fyd