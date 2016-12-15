/* -*- c++ -*- */
/* 
 * Copyright 2016 Tom Early, AC2IE.
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


#ifndef INCLUDED_THUMBDV_ENCODE_SB_H
#define INCLUDED_THUMBDV_ENCODE_SB_H

#include <ThumbDV/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace ThumbDV {

    /*!
     * \brief Voice encoder using AMBE3000
     * \ingroup ThumbDV
     *
     */
    class THUMBDV_API Encode_sb : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<Encode_sb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ThumbDV::Encode_sb.
       *
       * To avoid accidental use of raw pointers, ThumbDV::Encode_sb's
       * constructor is in a private implementation
       * class. ThumbDV::Encode_sb::make is the public interface for
       * creating new instances.
       */
      static sptr make(char* device, int baudrate, int dvtype);
    };

  } // namespace ThumbDV
} // namespace gr

#endif /* INCLUDED_THUMBDV_ENCODE_SB_H */

