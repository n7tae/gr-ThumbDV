/* -*- c++ -*- */
/* 
 * Copyright 2016 Tom Early, N7TAE.
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
#include "Decode_bs_impl.h"

namespace gr {
	namespace ThumbDV {

		Decode_bs::sptr Decode_bs::make(char *device, int baudrate, int dvtype)
		{
			return gnuradio::get_initial_sptr (new Decode_bs_impl(device, baudrate, dvtype));
		}

		/*
		* The private constructor
		*/
		Decode_bs_impl::Decode_bs_impl(char *device, int baudrate, int dvtype)
			: gr::block("Decode_bs",
				gr::io_signature::make(1, 1, sizeof(unsigned char)),
				gr::io_signature::make(1, 1, sizeof(short int)))
		{
			device_is_closed = dv3000u.OpenDevice(device, baudrate, dvtype);
			set_output_multiple(160);
		}

		/*
		* Our virtual destructor.
		*/
		Decode_bs_impl::~Decode_bs_impl()
		{
			dv3000u.CloseDevice();
		}

		void Decode_bs_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required)
		{
			ninput_items_required[0] = 9 * noutput_items / 160;
		}

		int Decode_bs_impl::general_work(int noutput_items, gr_vector_int &ninput_items,
			gr_vector_const_void_star &input_items, gr_vector_void_star &output_items)
		{
			const unsigned char *in = (const unsigned char *) input_items[0];
			short int *out = (short int *) output_items[0];

			if (device_is_closed)
				return WORK_DONE;	// DV3000 didn't open

			// Do <+signal processing+>
			for (int i=0; i<noutput_items; i+=160) {
				bool zeros = true;
				for (int j=0; j<9; j++) {
					if (in[j]) {
						zeros = false;
						break;
					}
				}
				if (zeros) {
					memset(out, 0, 160*sizeof(short int));
				} else {
					if (dv3000u.DecodeData(in, out))
						return WORK_DONE;	// there was a problem
				}
				in += 9;
				out += 160;
			}
			// Tell runtime system how many input items we consumed on
			// each input stream.
			consume_each(9 * noutput_items / 160);

			// Tell runtime system how many output items we produced.
			return noutput_items;
		}

	} /* namespace ThumbDV */
} /* namespace gr */

