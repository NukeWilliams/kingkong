#pragma once

/* includes */
#include <boost/asio.hpp>
#include "kingkong/ak.h"
#include "kingkong/map.h"
#include "kingkong/query_string.h"

/**
 * @brief http request namespace
 * 
 */
namespace kingkong {
    template<typename T>
    inline const std::string& get_header_value(const T& headers, const std::string& key)
    {
        if (headers.count(key))
        {
            return headers.find(key)->second;
        }
        static std::string empty;
        return empty;
    }

    struct DetachHelper;

    struct request
    {
        HTTPMethod method;
        std::string raw_url;     
        std::string url;        
        query_string url_params;
        ci_map headers;
        std::string body;
        std::string remote_ip_address; 

        void* middleware_context{};
        boost::asio::io_service* io_service{};

        request():
          method(HTTPMethod::Get)
        {}

        request(HTTPMethod method, std::string raw_url, std::string url, query_string url_params, ci_map headers, std::string body):
          method(method), raw_url(std::move(raw_url)), url(std::move(url)), url_params(std::move(url_params)), headers(std::move(headers)), body(std::move(body))
        {}

        void add_header(std::string key, std::string value)
        {
            headers.emplace(std::move(key), std::move(value));
        }

        const std::string& get_header_value(const std::string& key) const
        {
            return kingkong::get_header_value(headers, key);
        }

        template<typename CompletionHandler>
        void post(CompletionHandler handler)
        {
            io_service->post(handler);
        }

        template<typename CompletionHandler>
        void dispatch(CompletionHandler handler)
        {
            io_service->dispatch(handler);
        }
    };
}