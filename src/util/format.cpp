//  Copyright (c) 2017 Agustin Berge
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/util/format.hpp>

#include <boost/utility/string_ref.hpp>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

namespace hpx { namespace util { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    static unsigned long long format_atoi(
        boost::string_ref str, std::size_t* pos = nullptr) noexcept
    {
        // copy input to a null terminated buffer
        static constexpr std::size_t digits10 =
            std::numeric_limits<unsigned long long>::digits10 + 1;
        char buffer[digits10 + 1] = {};
        std::copy_n(str.data(), (std::min)(str.size(), digits10), buffer);

        char const* first = buffer;
        char* last = buffer;
        unsigned long long r = std::strtoull(first, &last, 10);
        if (pos != nullptr)
            *pos = last - first;
        return r;
    }

    static std::size_t format_find(
        boost::string_ref str, char c) noexcept
    {
        std::size_t r = 0;
        std::size_t const size = str.size();
        while (r < size && str[r] != c) ++r;
        return r;
    }

    static boost::string_ref format_substr(
        boost::string_ref str,
        std::size_t start, std::size_t end = boost::string_ref::npos) noexcept
    {
        return start < end && start < str.size()
            ? str.substr(start, end - start) : boost::string_ref{};
    }

    ///////////////////////////////////////////////////////////////////////////
    // replacement-field ::=  '{' [arg-id] [':' format-spec] '}'
    struct format_field
    {
        std::size_t arg_id;
        boost::string_ref spec;
    };

    static format_field parse_field(boost::string_ref field) noexcept
    {
        std::size_t const sep = format_find(field, ':');
        boost::string_ref const arg_id = format_substr(field, 0, sep);
        boost::string_ref const spec = format_substr(field, sep + 1);

        std::size_t const id = format_atoi(arg_id) - 1;
        return format_field{id, spec};
    }

    void format_to(
        std::ostream& os,
        boost::string_ref format_str,
        format_arg const* args, std::size_t count)
    {
        std::size_t index = 0;
        while (!format_str.empty())
        {
            if (format_str[0] == '{')
            {
                assert(!format_str.empty());
                if (format_str[1] == '{')
                {
                    os << '{';
                } else {
                    std::size_t const end = format_find(format_str, '}');
                    boost::string_ref field_str = format_substr(format_str, 1, end);
                    format_field const field = parse_field(field_str);
                    format_str.remove_prefix(end - 1);

                    std::size_t const id =
                        field.arg_id == std::size_t(-1) ? index : field.arg_id;
                    args[id](os, field.spec);
                    ++index;
                }
                format_str.remove_prefix(2);
            } else {
                std::size_t const next = format_find(format_str, '{');

                os << format_str.substr(0, next);
                format_str.remove_prefix(next);
            }
        }
    }

    std::string format(
        boost::string_ref format_str,
        format_arg const* args, std::size_t count)
    {
        std::ostringstream os;
        detail::format_to(os, format_str, args, count);
        return os.str();
    }
}}}
