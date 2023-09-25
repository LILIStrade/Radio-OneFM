/* -*- c++ -*- */
/*
 * Copyright 2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "complex_to_arg_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/math.h>
#include <volk/volk.h>

namespace gr {
namespace blocks {

complex_to_arg::sptr complex_to_arg::make(size_t vlen)
{
    return gnuradio::make_block_sptr<complex_to_arg_impl>(vlen);
}

complex_to_arg_impl::complex_to_arg_impl(size_t vlen)
    : sync_block("complex_to_arg",
                 io_signature::make(1, 1, sizeof(gr_complex) * vlen),
                 io_signature::make(1, 1, sizeof(float) * vlen)),
      d_vlen(vlen)
{
    const int alignment_multiple = volk_get_alignment() / sizeof(float);
    set_alignment(std::max(1, alignment_multiple));
}

int complex_to_arg_impl::work(int noutput_items,
                              gr_vector_const_void_star& input_items,
                              gr_vector_void_star& output_items)
{
    const gr_complex* in = (const gr_complex*)input_items[0];
    float* out = (float*)output_items[0];
    int noi = noutput_items * d_vlen;

    // The fast_atan2f is faster than Volk
    for (int i = 0; i < noi; i++) {
        //    out[i] = std::arg (in[i]);
        out[i] = gr::fast_atan2f(in[i]);
    }

    return noutput_items;
}

} /* namespace blocks */
} /* namespace gr */
