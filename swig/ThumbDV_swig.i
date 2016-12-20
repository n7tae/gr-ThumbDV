/* -*- c++ -*- */

#define THUMBDV_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ThumbDV_swig_doc.i"

%{
#include "ThumbDV/Encode_sb.h"
#include "ThumbDV/Decode_bs.h"
#include "ThumbDV/dstar_sync_bb.h"
#include "ThumbDV/dstar_data_sink_b.h"
%}


%include "ThumbDV/Encode_sb.h"
GR_SWIG_BLOCK_MAGIC2(ThumbDV, Encode_sb);
%include "ThumbDV/Decode_bs.h"
GR_SWIG_BLOCK_MAGIC2(ThumbDV, Decode_bs);
%include "ThumbDV/dstar_sync_bb.h"
GR_SWIG_BLOCK_MAGIC2(ThumbDV, dstar_sync_bb);
%include "ThumbDV/dstar_data_sink_b.h"
GR_SWIG_BLOCK_MAGIC2(ThumbDV, dstar_data_sink_b);
