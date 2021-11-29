#pragma once

#include <boost/asio.hpp>
#include <chrono>
#include <functional>
#include <map>
#include <vector>
#include "kingkong/logging.h"

namespace kingkong {
    
    namespace detail {

        class task_timer
        {
        public:
            using task_type = std::function<void()>;
            using identifier_type = size_t;

        private:
            using clock_type = std::chrono::steady_clock;
            using time_type = clock_type::time_point;

        public:
            task_timer(boost::asio::io_service& io_service):
              io_service_(io_service), deadline_timer_(io_service_)
            {
                deadline_timer_.expires_from_now(boost::posix_time::seconds(1));
                deadline_timer_.async_wait(
                  std::bind(&task_timer::tick_handler, this, std::placeholders::_1));
            }

            ~task_timer() { deadline_timer_.cancel(); }

            void cancel(identifier_type id)
            {
                tasks_.erase(id);
                KINGKONG_LOG_DEBUG << "task_timer cancelled: " << this << ' ' << id;
            }

            identifier_type schedule(const task_type& task)
            {
                tasks_.insert(
                  {++highest_id_,
                   {clock_type::now() + std::chrono::seconds(get_default_timeout()),
                    task}});
                KINGKONG_LOG_DEBUG << "task_timer scheduled: " << this << ' ' << highest_id_;
                return highest_id_;
            }

            identifier_type schedule(const task_type& task, std::uint8_t timeout)
            {
                tasks_.insert({++highest_id_,
                               {clock_type::now() + std::chrono::seconds(timeout), task}});
                KINGKONG_LOG_DEBUG << "task_timer scheduled: " << this << ' ' << highest_id_;
                return highest_id_;
            }

            void set_default_timeout(std::uint8_t timeout) { default_timeout_ = timeout; }

            std::uint8_t get_default_timeout() const { return default_timeout_; }

        private:
            void process_tasks()
            {
                time_type current_time = clock_type::now();
                std::vector<identifier_type> finished_tasks;

                for (const auto& task : tasks_)
                {
                    if (task.second.first < current_time)
                    {
                        (task.second.second)();
                        finished_tasks.push_back(task.first);
                        KINGKONG_LOG_DEBUG << "task_timer called: " << this << ' ' << task.first;
                    }
                }

                for (const auto& task : finished_tasks)
                    tasks_.erase(task);

                if (tasks_.empty()) highest_id_ = 0;
            }

            void tick_handler(const boost::system::error_code& ec)
            {
                if (ec) return;

                process_tasks();

                deadline_timer_.expires_from_now(boost::posix_time::seconds(1));
                deadline_timer_.async_wait(
                  std::bind(&task_timer::tick_handler, this, std::placeholders::_1));
            }

        private:
            std::uint8_t default_timeout_{5};
            boost::asio::io_service& io_service_;
            boost::asio::deadline_timer deadline_timer_;
            std::map<identifier_type, std::pair<time_type, task_type>> tasks_;

            identifier_type highest_id_{0};
        };
    } 
}