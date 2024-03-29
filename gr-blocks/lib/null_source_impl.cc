/* -*- c++ -*- */
/*
 * Copyright 2004,2010,2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "null_source_impl.h"
#include <gnuradio/io_signature.h>
#include <cstring>

namespace gr {
namespace blocks {

null_source::sptr null_source::make(size_t sizeof_stream_item)
{
    return gnuradio::make_block_sptr<null_source_impl>(sizeof_stream_item);
}

null_source_impl::null_source_impl(size_t sizeof_stream_item)
    : sync_block("null_source",
                 io_signature::make(0, 0, 0),
                 io_signature::make(1, -1, sizeof_stream_item))
{
}

null_source_impl::~null_source_impl() {}

int null_source_impl::work(int noutput_items,
                           gr_vector_const_void_star& input_items,
                           gr_vector_void_star& output_items)
{
    void* optr;
    for (size_t n = 0; n < output_items.size(); n++) {
        optr = (void*)output_items[n];
        memset(optr, 0, noutput_items * output_signature()->sizeof_stream_item(n));
    }
    return noutput_items;
}

} /* namespace blocks */
} /* namespace gr */
