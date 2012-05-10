/******************************************************************************\
 *           ___        __                                                    *
 *          /\_ \    __/\ \                                                   *
 *          \//\ \  /\_\ \ \____    ___   _____   _____      __               *
 *            \ \ \ \/\ \ \ '__`\  /'___\/\ '__`\/\ '__`\  /'__`\             *
 *             \_\ \_\ \ \ \ \L\ \/\ \__/\ \ \L\ \ \ \L\ \/\ \L\.\_           *
 *             /\____\\ \_\ \_,__/\ \____\\ \ ,__/\ \ ,__/\ \__/.\_\          *
 *             \/____/ \/_/\/___/  \/____/ \ \ \/  \ \ \/  \/__/\/_/          *
 *                                          \ \_\   \ \_\                     *
 *                                           \/_/    \/_/                     *
 *                                                                            *
 * Copyright (C) 2011, 2012                                                   *
 * Dominik Charousset <dominik.charousset@haw-hamburg.de>                     *
 *                                                                            *
 * This file is part of libcppa.                                              *
 * libcppa is free software: you can redistribute it and/or modify it under   *
 * the terms of the GNU Lesser General Public License as published by the     *
 * Free Software Foundation, either version 3 of the License                  *
 * or (at your option) any later version.                                     *
 *                                                                            *
 * libcppa is distributed in the hope that it will be useful,                 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 * See the GNU Lesser General Public License for more details.                *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public License   *
 * along with libcppa. If not, see <http://www.gnu.org/licenses/>.            *
\******************************************************************************/


#ifndef PARTIAL_FUNCTION_HPP
#define PARTIAL_FUNCTION_HPP

#include <list>
#include <vector>
#include <memory>
#include <utility>

#include "cppa/detail/invokable.hpp"
#include "cppa/intrusive/singly_linked_list.hpp"

namespace cppa {

class behavior;

/**
 * @brief A partial function implementation
 *        for {@link cppa::any_tuple any_tuples}.
 */
class partial_function {

    partial_function(partial_function const&) = delete;
    partial_function& operator=(partial_function const&) = delete;

 public:

    struct impl {
        virtual ~impl();
        virtual bool invoke(any_tuple&) = 0;
        virtual bool invoke(any_tuple const&) = 0;
        virtual bool defined_at(any_tuple const&) = 0;
    };

    typedef std::unique_ptr<impl> impl_ptr;

    partial_function() = default;
    partial_function(partial_function&&) = default;
    partial_function& operator=(partial_function&&) = default;

    partial_function(impl_ptr&& ptr);

    inline bool defined_at(any_tuple const& value) {
        return ((m_impl) && m_impl->defined_at(value));
    }

    inline bool operator()(any_tuple& value) {
        return ((m_impl) && m_impl->invoke(value));
    }

    inline bool operator()(any_tuple const& value) {
        return ((m_impl) && m_impl->invoke(value));
    }

    inline bool operator()(any_tuple&& value) {
        any_tuple cpy{std::move(value)};
        return (*this)(cpy);
    }

 private:

    impl_ptr m_impl;

};

//behavior operator,(partial_function&& lhs, behavior&& rhs);

} // namespace cppa

#endif // PARTIAL_FUNCTION_HPP
