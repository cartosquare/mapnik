/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2015 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef CSV_FEATURESET_HPP
#define CSV_FEATURESET_HPP

#include <mapnik/feature.hpp>
#include <mapnik/unicode.hpp>
#include "csv_utils.hpp"
#include "csv_datasource.hpp"
#include <deque>
#include <cstdio>

class csv_featureset : public mapnik::Featureset
{
    using file_ptr = std::unique_ptr<std::FILE, int (*)(std::FILE *)>;
    using locator_type = detail::geometry_column_locator;
public:
    using array_type = std::deque<csv_datasource::item_type>;
    csv_featureset(std::string const& filename,
                   locator_type const& locator,
                   std::string const& separator,
                   std::vector<std::string> const& headers,
                   mapnik::context_ptr const& ctx,
                   array_type && index_array);
    ~csv_featureset();
    mapnik::feature_ptr next();
private:
    mapnik::feature_ptr parse_feature(char const* beg, char const* end);
    file_ptr file_;
    std::string const& separator_;
    std::vector<std::string> headers_;
    const array_type index_array_;
    array_type::const_iterator index_itr_;
    array_type::const_iterator index_end_;
    mapnik::context_ptr ctx_;
    mapnik::value_integer feature_id_ = 0;
    detail::geometry_column_locator const& locator_;
    mapnik::transcoder tr_;
};


#endif // CSV_FEATURESET_HPP