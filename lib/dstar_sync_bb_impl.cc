/* -*- c++ -*- */
/* 
 * Copyright 2016 Thomas Early AC2IE.
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
#include "dstar_sync_bb_impl.h"

namespace gr {
	namespace ThumbDV {

		dstar_sync_bb::sptr dstar_sync_bb::make()
		{
			return gnuradio::get_initial_sptr (new dstar_sync_bb_impl());
		}

		/*
		* The private constructor
		*/
		dstar_sync_bb_impl::dstar_sync_bb_impl()
			: gr::block("dstar_sync_bb",
				gr::io_signature::make(1, 1, sizeof(unsigned char)),
				gr::io_signature::make(2, 2, sizeof(unsigned char)))
		{
			set_output_multiple(9);
		}

		/*
		* Our virtual destructor.
		*/
		dstar_sync_bb_impl::~dstar_sync_bb_impl()
		{
		}

		void dstar_sync_bb_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required)
		{
			ninput_items_required[0] = 96 * noutput_items / 9;
			//ninput_items_required[1] = 96 * noutput_items / 3;
		}

		int dstar_sync_bb_impl::general_work (int noutput_items, gr_vector_int &ninput_items,
			gr_vector_const_void_star &input_items, gr_vector_void_star &output_items)
		{
			const unsigned char *in = (const unsigned char *)input_items[0];
			unsigned char *voice = (unsigned char *)output_items[0];
			unsigned char *sdata = (unsigned char *)output_items[1];

			// Do <+signal processing+>
			int nslow_data = 0;
			int nvoice = 0;
			for (int i=0; i<noutput_items; i+=9) {
				int voicecount = 9;
				int thistime = demux.Process(in, voice, sdata, voicecount);
				in += 96;
				voice += voicecount;
				sdata += thistime;
				nslow_data += thistime;
				nvoice += voicecount;
			}
			// Tell runtime system how many input items we consumed on
			// each input stream.
			consume_each(96 * noutput_items / 9);

			// Tell runtime system how many output items we produced.
			produce(0, nvoice);
			produce(1, nslow_data);
			return WORK_CALLED_PRODUCE;
		}

	} /* namespace ThumbDV */
} /* namespace gr */

