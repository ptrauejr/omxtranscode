/* 
 * File:   demux.h
 * Author: lorddoskias
 *
 * Created on June 16, 2013, 3:21 PM
 */

#ifndef DEMUX_H
#define	DEMUX_H

#include "avcodec.h"

#ifdef	__cplusplus
extern "C" {
#endif

    struct audio_config_t { 
        enum CodecID codec_id;
        int sample_rate;
        int channels;
        uint64_t channels_layout; 
        int bit_rate;
        enum AVSampleFormat sample_fmt;
    };
    
    struct transcoder_ctx_t {
        //global stuff
        char *input_filename;
        struct packet_queue_t *input_video_queue;
        struct packet_queue_t *processed_audio_queue;
        
        //Transcoder related stuff
        struct omx_pipeline_t pipeline;
        AVFormatContext *input_context;
        char *output_filename; //output files will be written here
        struct audio_config_t audio_codec;
        int first_packet;
        //FIXME: used to synchronise the encoded component move it to per-component
        pthread_mutex_t is_running_mutex;
        pthread_cond_t is_running_cv;
    };

void *demux_thread(void *ctx);

#ifdef	__cplusplus
}
#endif

#endif	/* DEMUX_H */

