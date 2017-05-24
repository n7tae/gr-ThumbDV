/* -*- c++ -*- */
/* 
 * Copyright 2016 Thomas Early N7TAE.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "dstar_data_sink_b_impl.h"

namespace gr {
	namespace ThumbDV {

		dstar_data_sink_b::sptr dstar_data_sink_b::make()
		{
			return gnuradio::get_initial_sptr (new dstar_data_sink_b_impl());
		}

		/*
		* The private constructor
		*/
		dstar_data_sink_b_impl::dstar_data_sink_b_impl()
			: gr::sync_block("dstar_data_sink_b",
				gr::io_signature::make(1, 1, sizeof(unsigned char)),
				gr::io_signature::make(0, 0, 0))
		{
			buffercount = 0;
		}

		/*
		* Our virtual destructor.
		*/
		dstar_data_sink_b_impl::~dstar_data_sink_b_impl()
		{
		}

		int dstar_data_sink_b_impl::work(int noutput_items, gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
		{
			const unsigned char *in = (const unsigned char *) input_items[0];

			// Do <+signal processing+>
			if (noutput_items > 6-buffercount) {
				printf("work() called with %d noutput_items and buffercount=%d!\n", noutput_items, buffercount);
			} else {
				memcpy(slowdatabuf+buffercount, in, noutput_items);
				buffercount += noutput_items;
				if (6 == buffercount) {
					slowdata.Add(slowdatabuf);
					buffercount = 0;
				}
			}
			
			// Tell runtime system how many output items we produced.
			return noutput_items;
		}

	} /* namespace ThumbDV */
} /* namespace gr */

