/*
 * Copyright (c) 2015 Parag Salasakar (Parag.Salasakar@imgtec.com)
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "h264dsp_mips.h"

#if HAVE_MSA
static av_cold void h264dsp_init_msa(H264DSPContext *c,
                                     const int bit_depth,
                                     const int chroma_format_idc)
{
    if (8 == bit_depth) {
        c->h264_v_loop_filter_luma = ff_h264_v_lpf_luma_inter_msa;
        c->h264_h_loop_filter_luma = ff_h264_h_lpf_luma_inter_msa;
        c->h264_h_loop_filter_luma_mbaff =
            ff_h264_h_loop_filter_luma_mbaff_msa;
        c->h264_v_loop_filter_luma_intra = ff_h264_v_lpf_luma_intra_msa;
        c->h264_h_loop_filter_luma_intra = ff_h264_h_lpf_luma_intra_msa;
        c->h264_h_loop_filter_luma_mbaff_intra =
            ff_h264_h_loop_filter_luma_mbaff_intra_msa;
        c->h264_v_loop_filter_chroma = ff_h264_v_lpf_chroma_inter_msa;

        if (chroma_format_idc <= 1)
            c->h264_h_loop_filter_chroma = ff_h264_h_lpf_chroma_inter_msa;
        else
            c->h264_h_loop_filter_chroma =
                ff_h264_h_loop_filter_chroma422_msa;

        if (chroma_format_idc > 1)
            c->h264_h_loop_filter_chroma_mbaff =
                ff_h264_h_loop_filter_chroma422_mbaff_msa;

        c->h264_v_loop_filter_chroma_intra =
            ff_h264_v_lpf_chroma_intra_msa;

        if (chroma_format_idc <= 1)
            c->h264_h_loop_filter_chroma_intra =
                ff_h264_h_lpf_chroma_intra_msa;

        /* Weighted MC */
        c->weight_h264_pixels_tab[0] = ff_weight_h264_pixels16_8_msa;
        c->weight_h264_pixels_tab[1] = ff_weight_h264_pixels8_8_msa;
        c->weight_h264_pixels_tab[2] = ff_weight_h264_pixels4_8_msa;

        c->biweight_h264_pixels_tab[0] = ff_biweight_h264_pixels16_8_msa;
        c->biweight_h264_pixels_tab[1] = ff_biweight_h264_pixels8_8_msa;
        c->biweight_h264_pixels_tab[2] = ff_biweight_h264_pixels4_8_msa;
    }  // if (8 == bit_depth)
}
#endif  // #if HAVE_MSA

av_cold void ff_h264dsp_init_mips(H264DSPContext *c, const int bit_depth,
                                  const int chroma_format_idc)
{
#if HAVE_MSA
    h264dsp_init_msa(c, bit_depth, chroma_format_idc);
#endif  // #if HAVE_MSA
}
