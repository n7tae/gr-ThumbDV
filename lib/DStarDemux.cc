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

#include <stdio.h>
#include <fcntl.h>
#include <cstring>

#include "DStarDemux.h"
#include "DStarHeader.h"

CDStarDemux::CDStarDemux() :
	index(0),
	voiceframecount(0),
	readmode(nullmode),
	frame_is_ready(false),
	first_time(true)
{
}

CDStarDemux::~CDStarDemux()
{
}

int CDStarDemux::Process(const unsigned char *in, unsigned char *voice, unsigned char *data, int &outcount)
{
	if (frame_is_ready) {
		memcpy(voice, buffer, 9);
		frame_is_ready = false;
	} else {
		if (first_time) {
			outcount = 27;
			first_time = false;
		}
		memset(voice, 0x00u, outcount);
	}
	
	int ret = 0;
	for (int inp=0; inp<96; inp++) {
		unsigned char bit = in[inp];
		if (headmode == readmode) {
			buffer[index++] = bit;
			if (index >= 660) {
				CDStarHeader dsh(buffer);
				// print the header
				
				const char *h = dsh.GetHeader();
				printf("MY: %8.8s/%4.4s\n", h+27, h+35);
				printf("YOUR: %8.8s\n", h+19);
				printf("RPT1: %8.8s\n", h+11);
				printf("RPT2: %8.8s\n", h+3);
				voiceframecount = index = 0;
				readmode = datamode;
			}
			continue;
		}
		sr.Push(bit);

		if (sr.IsTermSync()) {
			printf("Got termsync flag!\n");
			index = voiceframecount = 0;
			readmode = nullmode;
		}

		if (datamode == readmode) {
			if (++index >= 96) {
				// sync register has a full voice frame now
				sr.GetDataFrame(buffer);
				frame_is_ready = true;
				int thisvoiceframe = voiceframecount++;
				bool this_frame_is_sync = sr.IsDataSync();
				if (thisvoiceframe % 21) {
					// should be a slow data voice frame
					if (this_frame_is_sync) {
						printf("Voice frame %d is an unexpected sync frame\n", thisvoiceframe);
						frame_is_ready = false;
					} else {
						memcpy(data, buffer+9, 3);
						ret += 3;
					}
				} else {
					// should be a sync voice frame
					if (! this_frame_is_sync) {
						printf("Voice frame %d should have been a sync frame\n", thisvoiceframe);
						printf("Data bytes: 0x%02x 0x%02x 0x%02x.\n", buffer[9], buffer[10], buffer[11]);
						frame_is_ready = false;
					}
				}
				if (! frame_is_ready) {
					readmode = nullmode;
					voiceframecount = 0;
				}
				index = 0;
			}
			continue;
		}

		// search for sync patterns
		if (nullmode == readmode) {
			if (sr.IsHeadSync()) {
				printf("Got headsync flag!\n");
				voiceframecount = index = 0;
				readmode = headmode;
				continue;
			}
		}

		// A voiceframe is suppose to immediately follow the 660-bit header.
		// This is here to put us back into voice mode if we missed the header or dropped a datasync flag
		if (datamode != readmode) {
			if (sr.IsDataSync()) {
				printf("Got datasync flag!\n");
				readmode = datamode;
				index = 0;
				sr.GetDataFrame(buffer);
				frame_is_ready = true;
				voiceframecount = 1;
				continue;
			}
		}
	}	// for loop over 96 input bits

	return ret;
}
