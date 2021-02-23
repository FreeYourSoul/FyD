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

#ifndef FYD_SRC_FREE_DATA_HH
#define FYD_SRC_FREE_DATA_HH

#include <vector>

#include <data_types.hh>

namespace fyd {

class free_data {

  struct internal;

public:
  ~free_data();
  free_data();

  std::vector<subscription> retrieve_subscriptions(sub_type type);

  //! get notification that has not been acknowledged yet
  std::vector<notification> retrieve_pending_notifications();

  //! acknowledge notifications (removing them from the pending list)
  void acknowledge_notifications(const std::vector<notification>& notifs);

  void subscribe(const subscription& sub);
  void unsubscribe(const std::string& user);

  //! run the notification checker daemon loop
  [[noreturn]] void run(std::chrono::seconds refresh_delay);

private:
  std::unique_ptr<internal> _impl;
};

}// namespace fyd

#endif//FYD_SRC_FREE_DATA_HH
