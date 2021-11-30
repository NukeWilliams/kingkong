#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include "kingkong/utils.h"

namespace kingkong {
    
    enum class HTTPMethod : char
    {
#ifndef DELETE
        DELETE = 0,
        GET,
        HEAD,
        POST,
        PUT,
        CONNECT,
        OPTIONS,
        TRACE,
        PATCH,
        PURGE,
#endif

        Delete = 0,
        Get,
        Head,
        Post,
        Put,
        Connect,
        Options,
        Trace,
        Patch,
        Purge,


        InternalMethodCount,
    };

    enum status
    {
        CONTINUE                      = 100,
        SWITCHING_PROTOCOLS           = 101,

        OK                            = 200,
        CREATED                       = 201,
        ACCEPTED                      = 202,
        NON_AUTHORITATIVE_INFORMATION = 203,
        NO_CONTENT                    = 204,
        RESET_CONTENT                 = 205,
        PARTIAL_CONTENT               = 206,

        MULTIPLE_CHOICES              = 300,
        MOVED_PERMANENTLY             = 301,
        FOUND                         = 302,
        SEE_OTHER                     = 303,
        NOT_MODIFIED                  = 304,
        TEMPORARY_REDIRECT            = 307,
        PERMANENT_REDIRECT            = 308,

        BAD_REQUEST                   = 400,
        UNAUTHORIZED                  = 401,
        FORBIDDEN                     = 403,
        NOT_FOUND                     = 404,
        METHOD_NOT_ALLOWED            = 405,
        PROXY_AUTHENTICATION_REQUIRED = 407,
        CONFLICT                      = 409,
        GONE                          = 410,
        PAYLOAD_TOO_LARGE             = 413,
        UNSUPPORTED_MEDIA_TYPE        = 415,
        RANGE_NOT_SATISFIABLE         = 416,
        EXPECTATION_FAILED            = 417,
        PRECONDITION_REQUIRED         = 428,
        TOO_MANY_REQUESTS             = 429,
        UNAVAILABLE_FOR_LEGAL_REASONS = 451,

        INTERNAL_SERVER_ERROR         = 500,
        NOT_IMPLEMENTED               = 501,
        BAD_GATEWAY                   = 502,
        SERVICE_UNAVAILABLE           = 503,
        VARIANT_ALSO_NEGOTIATES       = 506
    };

    inline std::string method_name(HTTPMethod method)
    {
        switch(method)
        {
            case HTTPMethod::Delete: return "DELETE";
            case HTTPMethod::Get: return "GET";
            case HTTPMethod::Head: return "HEAD";
            case HTTPMethod::Post: return "POST";
            case HTTPMethod::Put: return "PUT";
            case HTTPMethod::Connect: return "CONNECT";
            case HTTPMethod::Options: return "OPTIONS";
            case HTTPMethod::Trace: return "TRACE";
            case HTTPMethod::Patch: return "PATCH";
            case HTTPMethod::Purge: return "PURGE";
            default: return "invalid";
        }
        return "invalid";
    }

    enum class ParamType : char
    {
        INT,
        UINT,
        DOUBLE,
        STRING,
        PATH,
        MAX
    };

    struct routing_params
    {
        std::vector<int64_t> int_params;
    };

    template<>
    inline std::string routing_params::get<std::string>(unsigned index) const
    {
        return string_parms[index];
    }

}