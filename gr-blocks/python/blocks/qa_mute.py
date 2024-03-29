#!/usr/bin/env python
#
# Copyright 2004,2005,2007,2010,2013 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
#


from gnuradio import gr, gr_unittest, blocks


class test_mute(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def help_ii(self, src_data, exp_data, op):
        for s in zip(list(range(len(src_data))), src_data):
            src = blocks.vector_source_i(s[1])
            self.tb.connect(src, (op, s[0]))
        dst = blocks.vector_sink_i()
        self.tb.connect(op, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertEqual(exp_data, result_data)

    def help_ff(self, src_data, exp_data, op):
        for s in zip(list(range(len(src_data))), src_data):
            src = blocks.vector_source_f(s[1])
            self.tb.connect(src, (op, s[0]))
        dst = blocks.vector_sink_f()
        self.tb.connect(op, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertEqual(exp_data, result_data)

    def help_cc(self, src_data, exp_data, op):
        for s in zip(list(range(len(src_data))), src_data):
            src = blocks.vector_source_c(s[1])
            self.tb.connect(src, (op, s[0]))
        dst = blocks.vector_sink_c()
        self.tb.connect(op, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertEqual(exp_data, result_data)

    def test_unmute_ii(self):
        src_data = [1, 2, 3, 4, 5]
        expected_result = [1, 2, 3, 4, 5]
        op = blocks.mute_ii(False)
        self.help_ii((src_data,), expected_result, op)

    def test_mute_ii(self):
        src_data = [1, 2, 3, 4, 5]
        expected_result = [0, 0, 0, 0, 0]
        op = blocks.mute_ii(True)
        self.help_ii((src_data,), expected_result, op)

    def test_unmute_cc(self):
        src_data = [1 + 5j, 2 + 5j, 3 + 5j, 4 + 5j, 5 + 5j]
        expected_result = [1 + 5j, 2 + 5j, 3 + 5j, 4 + 5j, 5 + 5j]
        op = blocks.mute_cc(False)
        self.help_cc((src_data,), expected_result, op)

    def test_mute_cc(self):
        src_data = [1 + 5j, 2 + 5j, 3 + 5j, 4 + 5j, 5 + 5j]
        expected_result = [0 + 0j, 0 + 0j, 0 + 0j, 0 + 0j, 0 + 0j]
        op = blocks.mute_cc(True)
        self.help_cc((src_data,), expected_result, op)


if __name__ == '__main__':
    gr_unittest.run(test_mute)
