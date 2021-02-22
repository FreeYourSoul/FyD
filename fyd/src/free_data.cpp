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

#include <memory>

#include <fil/kv_db/kv_rocksdb.hh>

#include <data_sources/twitch.hh>
#include <data_sources/twitter.hh>
#include <data_sources/youtube.hh>

#include "free_data.hh"

namespace fyd {

using data_source = std::variant<
	fyd::source::twitter,
	fyd::source::youtube,
	fyd::source::twitch>;

struct free_data::internal {
  explicit internal(const std::string &path_db)
	  : db(fil::kv_rocksdb::initializer_type{path_db}),
		s({fyd::source::youtube(),
		   fyd::source::twitter(),
		   fyd::source::twitch()}) {
  }

  fil::kv_rocksdb_type db;

  std::vector<data_source> s;
};

free_data::~free_data() = default;

free_data::free_data() : _impl(std::make_unique<free_data::internal>("")) {}

void free_data::acknowledge_notifications(const std::vector<notification> &notifs) {
}

notification free_data::retrieve_notifications() {
  return notification();
}

subscription free_data::retrieve_subscriptions() {
  return subscription();
}

void free_data::subscribe(const subscription &sub) {
}

void free_data::unsubscribe(const std::string &user) {
}

}// namespace fyd